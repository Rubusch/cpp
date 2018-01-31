/*
 * Copyright (c) 2007, IRTrans GmbH
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of IRTrans GmbH nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY IRTrans GmbH ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL IRTrans GmbH BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */



#ifdef WIN32

#include <winsock2.h>
#include <windows.h>

#else

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <errno.h>
#include <netdb.h>
#include <signal.h>
#include <stdlib.h>
#define closesocket close
#include <string.h>
#endif


#include <stdio.h>
#include "remote.h"
#include "network.h"
#include "errcode.h"
#include "flash.h"
#include "functioncodes.h"


int		InitClientSocket (char host[],SOCKET *sock,unsigned long id);
void	PrintStatError (NETWORKSTATUS *stat);

void	ReceiveIR (int mode,char cmd[]);
char	*trim (char st[],int i);
int		MainMenu (void);
void	BuildMainMenu ();
void	BuildSendMenu ();
void	BuildLearnMenu ();
int		SendRemoteCommandSequence (char rem[],char *coms[],int num);
int		SendRemoteCommand (char rem[],char com[],char mask[],char bus[],char led[]);
int		SendCommand (NETWORKCOMMAND *com,NETWORKSTATUS *stat);
int		NetworkCommand (int netcommand,char remote[],char command[],word timeout,int adr,NETWORKSTATUS *stat);
int		ShutdownServer (void);
int		ReloadServer (void);
int		SetSwitch (char sw[],char value[]);
int		SendSerial (char data[]);
int		SetLED (char mode[],char value[]);
int		SendUDP (char ip[],char cmdstr[]);
int		RcvUDP (void);
int		FlashIRDB (int bus,char action[],char data[]);
int		LoadIRDB (int bus,char filename[]);
int		ListRemotes (void);
int		ListCommands (char rem[]);
int		ConvertBinary (char hexdata[]);

#define TIMEOUT 30000

SOCKET serv;

char send_remote[100];
char learn_remote[100];

#define VERSION "6.01.10 patch 0xAF"


main (int argc,char *argv[])
{
	int res;
//	unsigned char st[256];
//	NETWORKSTATUS stat;

#ifndef SILENT
	printf ("\nIRTrans ASCII Client Version %s\n\n",VERSION);
#endif
	if (argc == 1) {
#ifdef SILENT
		printf ("\nIRTrans ASCII Client Version %s\n\n",VERSION);
#endif
 		fprintf(stderr, "usage         : %s <ip>\n", argv[0]);
		fprintf(stderr, "send          : %s <ip> <remote> <command>\n",argv[0]);
		fprintf(stderr, "send          : %s <ip> <remote> <command> <sendmask> <bus>\n",argv[0]);
		fprintf(stderr, "send          : %s <ip> <remote> <command> <sendmask> <bus> <led>\n",argv[0]);
		fprintf(stderr, "send sequence : %s <ip> -sequence <remote> <command 1> ... <command n> \n",argv[0]);
 		fprintf(stderr, "shutdown      : %s <ip> -shutdown\n", argv[0]);
 		fprintf(stderr, "reload IRDB   : %s <ip> -reload\n", argv[0]);
 		fprintf(stderr, "Flash IRDB    : %s <ip> -flashirdb <bus number> <actionstring> <remotelist>\n", argv[0]);
 		fprintf(stderr, "Load IRDB     : %s <ip> -loadirdb <bus number> <filename>\n", argv[0]);
 		fprintf(stderr, "receive       : %s <ip> -receive\n", argv[0]);
 		fprintf(stderr, "Send RS232    : %s <ip> -rs232send <data>\n", argv[0]);
 		fprintf(stderr, "switch        : %s <ip> -switch <switch> <value>\n", argv[0]);
 		fprintf(stderr, "LED           : %s <ip> -led <mode> <value>\n", argv[0]);
 		fprintf(stderr, "List Remotes  : %s <ip> -remotelist\n", argv[0]);
 		fprintf(stderr, "List Commands : %s <ip> -commandlist <remote>\n", argv[0]);
		exit (-1);
	}

	if (argc == 4 && !strcmp (argv[2],"-udp")) return (SendUDP (argv[1],argv[3]));

	if (argc == 2 && !strcmp (argv[1],"-receiveudp")) return (RcvUDP());

	res = InitClientSocket (argv[1],&serv,0);
	if (res) {
		fprintf (stderr,"Error connecting to host %s\n",argv[1]);
		exit (res);
	}

	if (argc == 6 && !strcmp (argv[2],"-flashirdb")) return (FlashIRDB (atoi (argv[3]),argv[4],argv[5]));
	if (argc == 5 && !strcmp (argv[2],"-loadirdb")) return (LoadIRDB (atoi (argv[3]),argv[4]));


	if (argc == 3 && !strcmp (argv[2],"-remotelist")) return (ListRemotes ());
	if (argc == 4 && !strcmp (argv[2],"-commandlist")) return (ListCommands (argv[3]));
	if (argc == 3 && !strcmp (argv[2],"-shutdown")) return (ShutdownServer ());
	if (argc == 3 && !strcmp (argv[2],"-reload")) return (ReloadServer ());
	if (argc == 3 && !strcmp (argv[2],"-receive")) ReceiveIR (1,NULL);
	if (argc == 4 && !strcmp (argv[2],"-rs232send")) return (SendSerial (argv[3]));
	if (argc == 5 && !strcmp (argv[2],"-switch")) return (SetSwitch (argv[3],argv[4]));
	if (argc == 5 && !strcmp (argv[2],"-led")) return (SetLED (argv[3],argv[4]));
	if (argc >= 5 && !strcmp (argv[2],"-sequence")) return (SendRemoteCommandSequence(argv[3],&argv[4],argc-4));
	if (argc == 4) return (SendRemoteCommand (argv[2],argv[3],NULL,NULL,NULL));
	if (argc == 5) return (SendRemoteCommand (argv[2],argv[3],argv[4],NULL,NULL));
	if (argc == 6) return (SendRemoteCommand (argv[2],argv[3],argv[4],argv[5],NULL));
	if (argc == 7) return (SendRemoteCommand (argv[2],argv[3],argv[4],argv[5],argv[6]));

	while (MainMenu ());

	return (0);
}

int ListRemotes (void)
{
	int i,res,offset = 0;
	REMOTEBUFFER rem;

	do {
		res = NetworkCommand (COMMAND_GETREMOTES,"",0,0,offset,(NETWORKSTATUS *)&rem);

		if (rem.statustype != STATUS_REMOTELIST) {
			fprintf (stderr,"Error reading Remotelist\n");
			return (-1);
		}

		if (!offset) printf ("*** %3d Remotes\n",rem.count_total);
		for (i=0;i < rem.count_buffer;i++) printf ("%s\n",trim (rem.remotes[i].name,80));

		offset += rem.count_buffer;

	} while (rem.count_remaining);


	return (0);

}

int ListCommands (char rem[])
{
	int i,res,offset = 0;
	COMMANDBUFFER cmd;

	do {
		res = NetworkCommand (COMMAND_GETCOMMANDS,rem,0,0,offset,(NETWORKSTATUS *)&cmd);

		if (cmd.statustype != STATUS_COMMANDLIST) {
			fprintf (stderr,"Error reading Commandlist\n");
			return (-1);
		}

		if (!offset) printf ("*** %3d Commands\n",cmd.count_total);
		for (i=0;i < cmd.count_buffer;i++) printf ("%s\n",trim (cmd.commands[i],20));

		offset += cmd.count_buffer;

	} while (cmd.count_remaining);


	return (0);

}

int WriteTimer ()
{
	TIMERCOMMAND tim;
	NETWORKSTATUS stat;

	memset (&tim,0,sizeof (tim));

	tim.netcommand = COMMAND_STORETIMER;
	tim.adress = 0;
	tim.num = 0;
	tim.tim_mode = 2;
	tim.status = 0;
	tim.year = 0xff;
	tim.month = 0xff;
	tim.day = 0xff;
	tim.hour = 3;
	tim.min = 40;
	tim.weekday = 0xff;
	tim.targetmask = 0xffff;
	tim.ledselect = 3;
	strcpy (tim.remote,"irtrans");
	strcpy (tim.ircommand,"1");

	SendCommand ((NETWORKCOMMAND *)&tim,&stat);

	return (0);
}


int RcvUDP ()
{
	char mem[100];
	int res;
	int irtlan_socket;
	struct sockaddr_in serv_addr;

#ifdef WIN32
	int err;
    WORD	wVersionRequired;
    WSADATA	wsaData;
    wVersionRequired = MAKEWORD(2,2);
    err = WSAStartup(wVersionRequired, &wsaData);
    if (err != 0) exit(1);
#endif



	irtlan_socket = socket (PF_INET,SOCK_DGRAM,0);
	if (irtlan_socket < 0) return (ERR_OPENSOCKET);

	memset (&serv_addr,0,sizeof (serv_addr));
	serv_addr.sin_family = AF_INET;

	serv_addr.sin_addr.s_addr = htonl (INADDR_ANY);
	serv_addr.sin_port = htons (21001);

	if (bind (irtlan_socket,(struct sockaddr *)&serv_addr,sizeof (serv_addr)) < 0) {
		printf ("Error Bind\n");
		return (ERR_BINDSOCKET);
	}

	while (1) {
		memset (mem,0,100);
		res = recv (irtlan_socket,mem,100,0);

		printf ("RECV: %s\n",mem);
	}


	return (0);
}


int SendUDP (char ip[],char cmdstr[])
{
	char stat[1024];
	int res,len;
	struct hostent *he;
	int irtlan_outbound;
	struct sockaddr_in iadr;

#ifdef WIN32
	int err;
    WORD	wVersionRequired;
    WSADATA	wsaData;
    wVersionRequired = MAKEWORD(2,2);
    err = WSAStartup(wVersionRequired, &wsaData);
    if (err != 0) exit(1);
#endif

	irtlan_outbound = socket (PF_INET,SOCK_DGRAM,0);
	if (irtlan_outbound < 0) return (ERR_OPENSOCKET);

//	irtlan_in = socket (PF_INET,SOCK_DGRAM,0);
//	memset (&serv_addr,0,sizeof (serv_addr));
//	serv_addr.sin_family = AF_INET;

//	serv_addr.sin_addr.s_addr = htonl (INADDR_ANY);
//	serv_addr.sin_port = htons (IRTRANS_PORT);
//	serv_addr.sin_port = htons (50000);

//	rcv = bind (irtlan_in,(struct sockaddr *)&serv_addr,sizeof (serv_addr));

	memset (&iadr,0,sizeof (struct sockaddr));
	iadr.sin_family = AF_INET;

	res = 1;
	setsockopt (irtlan_outbound,SOL_SOCKET,SO_BROADCAST,(char *)&res,sizeof (int));


	iadr.sin_addr.s_addr = inet_addr(ip);
	if (iadr.sin_addr.s_addr == INADDR_NONE) {
		he = (struct hostent *)gethostbyname (ip);
		if (he == NULL) return (ERR_BINDSOCKET);

		memcpy(&iadr.sin_addr.s_addr, he->h_addr_list[0], 4);
	}

	iadr.sin_port = htons ((word)IRTRANS_PORT);
/*
	if (connect (irtlan_outbound,(struct sockaddr *)&iadr,sizeof (struct sockaddr_in)) < 0) {
		printf ("Error Connect\n");
		return (ERR_BINDSOCKET);
	}
*/

	if (!memcmp (cmdstr,"bsndccf",7)) {

		len = ConvertBinary (cmdstr + 8) + 7;
		res = sendto (irtlan_outbound,cmdstr + 1,len,0,(struct sockaddr *)&iadr,sizeof (struct sockaddr_in));
	}

	else {
		len = strlen (cmdstr);
		res = sendto (irtlan_outbound,cmdstr,strlen (cmdstr),0,(struct sockaddr *)&iadr,sizeof (struct sockaddr_in));
	}

	if (res != len) {
#ifdef WIN32
		printf ("Error Sending: %d\n",WSAGetLastError ());
#else
		printf ("Error Sending\n");
#endif
		return (ERR_BINDSOCKET);
	}


	memset (stat,0,1024);
	recv (irtlan_outbound,stat,1024,0);
	printf ("RCV STAT: %s\n",stat);

	return (0);
}

int ConvertBinary (char hexdata[])
{
	int val;
	int rpos,wpos;

	rpos = wpos = 0;

	while (hexdata[rpos]) {
		if (hexdata[rpos] >= 'a') val = (hexdata[rpos] + 10 - 'a') * 16;
		else if (hexdata[rpos] >= 'A') val = (hexdata[rpos] + 10 - 'A') * 16;
		else val = (hexdata[rpos] - '0') * 16;
		rpos++;
		if (hexdata[rpos] >= 'a') val += (hexdata[rpos] + 10 - 'a');
		else if (hexdata[rpos] >= 'A') val += (hexdata[rpos] + 10 - 'A');
		else val += (hexdata[rpos] - '0');
		rpos++;
		hexdata[wpos++] = val;


		while (hexdata[rpos] == ' ') rpos++;
	}

	return (wpos);

}

int SendSerial (char data[])
{
	NETWORKSTATUS stat;

	NetworkCommand (COMMAND_RS232_SEND,data,0,0,'L',&stat);

	return (0);
}


int SetSwitch (char sw[],char value[])
{
	char st[10];
	NETWORKSTATUS stat;

	st[0] = atoi (sw);
	st[1] = atoi (value);
	NetworkCommand (COMMAND_SETSWITCH,st,st+1,0,'L',&stat);

	return (0);
}

int SetLED (char mode[],char value[])
{
	char st[10];
	NETWORKSTATUS stat;

	st[0] = atoi (mode);
	st[1] = atoi (value);
	NetworkCommand (COMMAND_LED,st,st+1,0,'L',&stat);

	return (0);
}

void ReceiveIR (int mode,char cmd[])
{
	int res;
	STATUSBUFFER stat;
	NETWORKRECV *rcv;

	if (mode) printf ("Waiting for IR commands ...\n");
	rcv = (NETWORKRECV *)&stat;
	memset (&stat,0,sizeof (STATUSBUFFER));

	for (;;) {
		res = recv (serv,(char *)&stat,8,0);
		if (stat.statuslen > 8) {
			res = recv (serv,((char *)&stat) + 8,stat.statuslen-8,0);
			if (stat.statustype == STATUS_RECEIVE) {
				if (mode) printf ("RCV: %s.%s - %d [%d: %s]\n",trim (rcv->remote,80),trim (rcv->command,20),rcv->adress,rcv->clientid,trim (rcv->data,200));
				else {
					memcpy (cmd,rcv->data,200);
					return;
				}
			}
		}
	}
}


char *trim (char st[],int i)
{
	int j;
	i--;
	j = i;
	while (i && st[i] == ' ') i--;
	if (i < j) st[i+1] = 0;
	return (st);
}

int SendRemoteCommandSequence (char rem[],char *coms[],int num)
{
	int i;
	int ret;
	NETWORKSTATUS stat;
	for (i=0;i<num;++i)
	{
		ret = NetworkCommand (COMMAND_SEND,rem,coms[i],0,0,&stat);
		if (ret!=0) return ret; /* will never happen, because in the current implementation the NetworkCommand will terminate the program when an error occured */
	}
	return 0;
}

int SendRemoteCommand (char rem[],char com[],char mask[],char bus[],char led[])
{
	int adr = 0,res,wait = 0,ibus = 0,iled = 0;
	NETWORKSTATUS stat;
#ifdef WIN32

	if (!strcmp (rem,"wait") || !strcmp (rem,"Wait") || !strcmp (rem,"WAIT")) {
		adr = atoi (com);
		Sleep (adr);
		return (0);
	}

#endif
	if (mask) {
		if (!strcmp (mask,"wait") || !strcmp (mask,"Wait") || !strcmp (mask,"WAIT")) wait = atoi (mask+4);
		else if (!strcmp (mask,"int") || !strcmp (mask,"Int") || !strcmp (mask,"INT")) adr |= 1 << 17;
		else if (!strcmp (mask,"ext") || !strcmp (mask,"Ext") || !strcmp (mask,"EXT")) adr |= 2 << 17;
		else if (!strcmp (mask,"all") || !strcmp (mask,"All") || !strcmp (mask,"ALL")) adr |= 3 << 17;
		else {
			if (mask[0] == '0' && mask[1] == 'x') sscanf (mask,"%x",&adr);
			else sscanf (mask,"%d",&adr);
			if (adr) adr = (adr & 0xffff) | 0x10000;
		}
	}
	if (bus) {
		ibus = atoi (bus);
		if (ibus == 255) adr |= 0x40000000;
		else {
			ibus = abs (ibus) & (MAX_IR_DEVICES - 1);
			adr |= ibus << 19;
		}
	}
	if (led) {
		if (led[0] >= '0' && led[0] <= '9') {
			iled = atoi (led);
				if (iled > 3)
				{
					iled -= 4;
					adr |= (unsigned int)((iled & 7) << 27) | 0x80000000;
					adr |= (unsigned int)((iled / 8) & 3) << 17;
				}
				else adr |= (unsigned int)(iled & 3) << 17;
		}
		else {
			if (!strcmp (led,"int") || !strcmp (led,"Int") || !strcmp (led,"INT") || !strcmp (led,"I") || !strcmp (led,"i")) adr |= 1 << 17;
			else if (!strcmp (led,"ext") || !strcmp (led,"Ext") || !strcmp (led,"EXT") || !strcmp (led,"E") || !strcmp (led,"e")) adr |= 2 << 17;
			else if (!strcmp (led,"all") || !strcmp (led,"All") || !strcmp (led,"ALL") || !strcmp (led,"A") || !strcmp (led,"a")) adr |= 3 << 17;
			else if (led[0] == 'l' || led[0] == 'L') {
				iled = atoi (led + 1) - 1;
				adr |= (unsigned int)((iled & 7) << 27) | 0x80000000;
				adr |= (unsigned int)((iled / 8) & 3) << 17;
			}
		}
	}
	res = NetworkCommand (COMMAND_SEND,rem,com,0,adr,&stat);
#ifdef WIN32
	Sleep (wait);
#endif
	return (res);
}


int ShutdownServer (void)
{
	NETWORKCOMMAND com;
	NETWORKSTATUS stat;

	com.netcommand = COMMAND_SHUTDOWN;
	strcpy (com.remote,"XXXshutdownXXX");

	SendCommand (&com,&stat);

#ifdef WIN32
	Sleep (8000);
#endif

	return (0);
}

int ReloadServer (void)
{
	NETWORKCOMMAND com;
	NETWORKSTATUS stat;

	com.netcommand = COMMAND_RELOAD;

	SendCommand (&com,&stat);

	return (0);
}

int SendMenu (void)
{
	char st[255],l2[255];
	int choice = 0;
	int sw,md;
	NETWORKSTATUS stat;

	BuildSendMenu ();
	scanf ("%s",st);
	getchar ();
	choice = atoi (st);

	switch (choice) {
		case 1:
			printf ("\nEnter Remote Name: ");
			fflush (stdout);
			scanf ("%s",send_remote);
			getchar ();
			break;
		case 2:
			printf ("\nCommand Name: ");
			fflush (stdout);
			scanf ("%s",st);
			getchar ();
			NetworkCommand (COMMAND_SEND,send_remote,st,0,0,&stat);
			break;
		case 3:
			printf ("\nLCD Text: ");
			fflush (stdout);
			fgets (st,sizeof (st),stdin);
			NetworkCommand (COMMAND_LCD,st,0,LCD_TEXT | LCD_BACKLIGHT,'L',&stat);
			break;
		case 4:
			printf ("\nLCD Init Text Line 1: ");
			fflush (stdout);
			fgets (st,sizeof (st),stdin);
			printf ("\nLCD Init Text Line 2: ");
			fflush (stdout);
			fgets (l2,sizeof (l2),stdin);
			strcat (st,l2);
			NetworkCommand (COMMAND_LCDINIT,st,0,LCD_TEXT,'L',&stat);
			break;
		case 5:
			printf ("\nSwitch Number: ");
			fflush (stdout);
			scanf ("%d",&sw);
			getchar ();
			printf ("\nSwitch Value: ");
			fflush (stdout);
			scanf ("%d",&md);
			getchar ();
			st[0] = sw;
			st[1] = md;
			NetworkCommand (COMMAND_SETSWITCH,st,st+1,0,'L',&stat);
			break;
		case 99:
			return (0);
			break;
	}

	return (1);
}

int LearnMenu (void)
{
	char st[255];
	int choice = 0;
	NETWORKSTATUS stat;

	BuildLearnMenu ();
	scanf ("%s",st);
	getchar ();
	choice = atoi (st);

	switch (choice) {
		case 1:
			if (*learn_remote) NetworkCommand (COMMAND_CLOSE,learn_remote,st,0,'L',&stat);
			printf ("\nEnter Remote Name: ");
			fflush (stdout);
			scanf ("%s",learn_remote);
			getchar ();
			NetworkCommand (COMMAND_LRNREM,learn_remote,st,0,'L',&stat);
			break;
		case 2:
			printf ("\nPress Remote Button to record timing ....");
			fflush (stdout);
			NetworkCommand (COMMAND_LRNTIM,learn_remote,st,TIMEOUT,'*',&stat);
			printf ("OK\n");
			fflush (stdout);
			break;
		case 3:
			printf ("\nCommand Name: ");
			fflush (stdout);
			scanf ("%s",st);
			getchar ();
			printf ("\nPress Remote Button to learn ....");
			fflush (stdout);
			NetworkCommand (COMMAND_LRNCOM,learn_remote,st,TIMEOUT,'*',&stat);
			printf ("OK\n");
			fflush (stdout);
			break;
		case 4:
			printf ("\nCommand Name: ");
			fflush (stdout);
			scanf ("%s",st);
			getchar ();
			printf ("\nPress Remote Button to learn ....");
			fflush (stdout);
			NetworkCommand (COMMAND_LRNLONG,learn_remote,st,TIMEOUT,'*',&stat);
			printf ("OK\n");
			fflush (stdout);
			break;
		case 5:
			printf ("\nCommand Name: ");
			fflush (stdout);
			scanf ("%s",st);
			getchar ();
			printf ("\nPress Remote Button to learn ....");
			fflush (stdout);
			NetworkCommand (COMMAND_LRNRAW,learn_remote,st,TIMEOUT,'*',&stat);
			printf ("OK\n");
			fflush (stdout);
			break;
		case 99:
			if (*learn_remote) NetworkCommand (COMMAND_CLOSE,learn_remote,st,0,'L',&stat);
			return (0);
			break;
	}

	return (1);
}


void ShowSetStatus (int adr,int bus,NETWORKMODEEX2 *status)
{
	int i;
	status->stat[bus][adr].version[8] = 0;

	printf ("Device [%d-%d]: %s\n\n",bus,adr,status->stat[bus][adr].version);

	printf ("Repeat Mask: ");
	for (i=0;i<16;i++) {
		printf ("%c  ",(status->stat[bus][adr].send_mask & (1 << i) ? 'x':'o'));
	}
	printf ("\n             0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15\n\n");


	printf ("            Device Mode Send [20]: %c\n",(status->stat[bus][adr].device_mode & DEVMODE_SEND ? 'x':'o'));
	printf ("            IR               [21]: %c\n",(status->stat[bus][adr].device_mode & DEVMODE_IR ? 'x':'o'));
	printf ("            SBUS             [22]: %c\n",(status->stat[bus][adr].device_mode & DEVMODE_SBUS ? 'x':'o'));
	printf ("            SBUS RemoteCtrl  [24]: %c\n",(status->stat[bus][adr].device_mode & DEVMODE_SBUSCODE ? 'x':'o'));
	printf ("            RAW              [25]: %c\n",(status->stat[bus][adr].device_mode & DEVMODE_RAW ? 'x':'o'));
	printf ("            SBUS send Repeat [27]: %c\n",(status->stat[bus][adr].device_mode & DEVMODE_REPEAT ? 'x':'o'));

	if (status->stat[bus][adr].features & FN_DUALSND) {
		printf ("\n            Internal LEDs    [30]: %c\n",(status->stat[bus][adr].extended_mode & INTERNAL_LEDS ? 'x':'o'));
		printf ("            External LEDs    [31]: %c\n",(status->stat[bus][adr].extended_mode & EXTERNAL_LEDS ? 'x':'o'));
	}
	if (status->stat[bus][adr].features & FN_DUALRCV) {
		printf ("\n            Standard Receivr.[33]: %c\n",(status->stat[bus][adr].extended_mode & STANDARD_RCV ? 'x':'o'));
		printf ("            455 kHz Receiver [34]: %c\n",(status->stat[bus][adr].extended_mode & BO_RCV ? 'x':'o'));
	}

	if (status->stat[bus][adr].version[0] == 'V' || status->stat[bus][adr].version[0] == 'T' || status->stat[bus][adr].version[0] == 'C' || status->stat[bus][adr].version[0] == 'X' ) {	// 455kHz
		printf ("\n            Receive B&O      [35]: %c\n",(status->stat[bus][adr].extended_mode & BO_MODE ? 'x':'o'));
	}

	if (strcmp (status->stat[bus][adr].version+1,"3.02.10") >= 0) {
		printf ("\n                 Self Repeat [36]: %c\n",(status->stat[bus][adr].extended_mode & SELF_REPEAT ? 'x':'o'));
		if (status->stat[bus][adr].features & FN_DUALSND) {
			printf ("           via Internal LEDs [32]: %c\n",(status->stat[bus][adr].extended_mode & INTERNAL_REPEAT ? 'x':'o'));
		}
	}
	if (strcmp (status->stat[bus][adr].version+1,"4.04.01") >= 0) {
		printf ("\n         Learn Timeout   5ms [37]: %c\n",(((status->stat[bus][adr].extended_mode2 & LRN_TIMEOUT_MASK) == 0) ? 'x':'o'));
		printf ("         Learn Timeout  15ms [38]: %c\n",(((status->stat[bus][adr].extended_mode2 & LRN_TIMEOUT_MASK) == 1) ? 'x':'o'));
		printf ("         Learn Timeout  30ms [39]: %c\n",(((status->stat[bus][adr].extended_mode2 & LRN_TIMEOUT_MASK) == 2) ? 'x':'o'));
		printf ("         Learn Timeout  60ms [40]: %c\n",(((status->stat[bus][adr].extended_mode2 & LRN_TIMEOUT_MASK) == 3) ? 'x':'o'));
		printf ("         Learn Timeout  90ms [41]: %c\n",(((status->stat[bus][adr].extended_mode2 & LRN_TIMEOUT_MASK) == 4) ? 'x':'o'));
		printf ("         Learn Timeout 120ms [42]: %c\n",(((status->stat[bus][adr].extended_mode2 & LRN_TIMEOUT_MASK) == 5) ? 'x':'o'));
		printf ("         Learn Timeout 150ms [43]: %c\n",(((status->stat[bus][adr].extended_mode2 & LRN_TIMEOUT_MASK) == 6) ? 'x':'o'));
		if (strcmp (status->stat[bus][adr].version+1,"4.04.35") >= 0)
			printf ("         Learn Timeout 250ms [44]: %c\n",(((status->stat[bus][adr].extended_mode2 & LRN_TIMEOUT_MASK) == 7) ? 'x':'o'));
	}

	if (strcmp (status->stat[bus][adr].version+1,"4.05.01") >= 0) {
		printf ("\n         Repeat Timeout 5ms  [45]: %c\n",(status->stat[bus][adr].device_mode & DEVMODE_RAWFAST ? 'o':'x'));
		printf ("         Repeat Timeout 25ms [46]: %c\n",(status->stat[bus][adr].device_mode & DEVMODE_RAWFAST ? 'x':'o'));
	}

	if (status->stat[bus][adr].features & FN_SBUS_UART) {
		printf ("\n             SBUS Classic    [47]: %c\n",(status->stat[bus][adr].extended_mode & SBUS_UART ? 'o':'x'));
		printf ("             SBUS 4800 Baud  [48]: %c\n",((status->stat[bus][adr].extended_mode & SBUS_UART && (status->stat[bus][adr].extended_mode2 & SBUS_BAUD_MASK) == 0) ? 'x':'o'));
		printf ("             SBUS 9600 Baud  [49]: %c\n",((status->stat[bus][adr].extended_mode & SBUS_UART && (status->stat[bus][adr].extended_mode2 & SBUS_BAUD_MASK) == 8) ? 'x':'o'));
		printf ("             SBUS 19200 Baud [50]: %c\n",((status->stat[bus][adr].extended_mode & SBUS_UART && (status->stat[bus][adr].extended_mode2 & SBUS_BAUD_MASK) == 16) ? 'x':'o'));
		printf ("             SBUS 38400 Baud [51]: %c\n",((status->stat[bus][adr].extended_mode & SBUS_UART && (status->stat[bus][adr].extended_mode2 & SBUS_BAUD_MASK) == 24) ? 'x':'o'));
	}

	if (!(status->stat[bus][adr].features & FN_SOFTID) || (status->stat[bus][adr].features & FN_POWERON) || (status->stat[bus][adr].features & FN_USBWAKEUP)) {
		printf ("\nPowerOn Remote               [52]: %s\n",status->stat[bus][adr].remote);
		printf ("PowerOn Command              [53]: %s\n",status->stat[bus][adr].command);
	}

	if (status->stat[bus][adr].features & FN_DUALPOWERON) {
		printf ("\nPowerOff Remote              [54]: %s\n",status->stat[bus][adr].remote2);
		printf ("PowerOff Command             [55]: %s\n",status->stat[bus][adr].command2);
	}

	printf ("\nCancel                     [88]\n");
	printf ("Save & Exit                [99]\n");

	printf ("\nSelect command ");
	fflush (stdout);
}

void ShowReceiverType (int type)
{
	switch (type & 0x7) {
		case 1:
			printf ("56 kHz\n");
			break;
		case 2:
			printf ("38 kHz\n");
			break;
		case 4:
			printf ("455 kHz\n");
			break;
		case 5:
			printf ("455 kHz Plasma shielded\n");
			break;
		case 6:
			printf ("Universal learning receiver\n");
			break;
	}
}


void ShowDeviceStatusEx (NETWORKMODEEX2 *status,int bus,int adr,int panel)
{
	int i;

	if (panel == 1) {
		printf ("\n");
		printf ("IR Send                    [1]: %c\n",(status->stat[bus][adr].device_mode & DEVMODE_SEND ? 'x':'o'));
		printf ("IR Receive                 [2]: %c\n",(status->stat[bus][adr].device_mode & DEVMODE_IR ? 'x':'o'));
		printf ("\n");
		printf ("Internal LEDs              [3]: %c\n",(status->stat[bus][adr].extended_mode & INTERNAL_LEDS ? 'x':'o'));
		printf ("External LEDs              [4]: %c\n",(status->stat[bus][adr].extended_mode & EXTERNAL_LEDS ? 'x':'o'));
		printf ("\n");
		printf ("Self Repeat                [5]: %c\n",(status->stat[bus][adr].extended_mode & SELF_REPEAT ? 'x':'o'));
		printf ("Self Repeat via int. LEDs  [6]: %c\n",(status->stat[bus][adr].extended_mode & INTERNAL_REPEAT ? 'x':'o'));
		printf ("\n");
		printf ("Done                       [7]\n");

		printf ("\nSelect command ");
		fflush (stdout);
	}

	else if (panel == 2) {
		printf ("\n");
		printf ("IR Receiver 1              [1]: ");
		ShowReceiverType (status->stat[bus][adr].extended_mode_ex[0] & 0xf);
		if (status->stat[bus][adr].features & FN_EXT_SW) printf ("IR Receiver 1 External     [2]: %c\n",(status->stat[bus][adr].extended_mode_ex[0] & 8 ? 'x':'o'));
		printf ("IR Receiver 1 active       [3]: %c\n",(status->stat[bus][adr].extended_mode & STANDARD_RCV ? 'x':'o'));
		printf ("\n");

		if (status->stat[bus][adr].features & FN_DUALRCV) {
			printf ("IR Receiver 2              [4]: ");
			ShowReceiverType ((status->stat[bus][adr].extended_mode_ex[0] & 0xf0) >> 4);
			if (status->stat[bus][adr].features & FN_EXT_SW) printf ("IR Receiver 2 External     [5]: %c\n",(status->stat[bus][adr].extended_mode_ex[0] & 0x80 ? 'x':'o'));
			printf ("IR Receiver 2 active       [6]: %c\n",(status->stat[bus][adr].extended_mode & HI_RCV ? 'x':'o'));
			printf ("\n");
		}

		switch (status->stat[bus][adr].extended_mode_ex[2] & IR_FILTER_MASK) {
			case IR_FILTER_64:
				printf ("IR Filter                  [7]: 64 us\n");
				break;
			case IR_FILTER_120:
				printf ("IR Filter                  [7]: 120 us\n");
				break;
			case IR_FILTER_160:
				printf ("IR Filter                  [7]: 160 us\n");
				break;
			case IR_FILTER_280:
				printf ("IR Filter                  [7]: 280 us\n");
				break;
			case IR_FILTER_380:
				printf ("IR Filter                  [7]: 380 us\n");
				break;
			case IR_FILTER_480:
				printf ("IR Filter                  [7]: 480 us\n");
				break;
			case IR_FILTER_550:
				printf ("IR Filter                  [7]: 550 us\n");
				break;
			case IR_FILTER_800:
				printf ("IR Filter                  [7]: 800 us\n");
				break;
		}

		switch (status->stat[bus][adr].extended_mode2 & RCV_TOLERANCE_MASK) {
			case RCV_TOLERANCE_64:
				printf ("IR Receive Tolerance       [8]: 64 us\n");
				break;
			case RCV_TOLERANCE_96:
				printf ("IR Receive Tolerance       [8]: 96 us\n");
				break;
			case RCV_TOLERANCE_120:
				printf ("IR Receive Tolerance       [8]: 120 us\n");
				break;
			case RCV_TOLERANCE_160:
				printf ("IR Receive Tolerance       [8]: 160 us\n");
				break;
			case RCV_TOLERANCE_320:
				printf ("IR Receive Tolerance       [8]: 320 us\n");
				break;
			case RCV_TOLERANCE_480:
				printf ("IR Receive Tolerance       [8]: 480 us\n");
				break;
			case RCV_TOLERANCE_680:
				printf ("IR Receive Tolerance       [8]: 680 us\n");
				break;
			case RCV_TOLERANCE_960:
				printf ("IR Receive Tolerance       [8]: 960 us\n");
				break;
		}

		printf ("IR Receive Timeout         [9]: %d ms\n",status->stat[bus][adr].extended_mode_ex[1]);

		switch (status->stat[bus][adr].extended_mode_ex[2] & IDLE_TIMEOUT_MASK) {
			case IDLE_TIMEOUT_1:
				printf ("Idle Timeout              [10]: 1 ms\n");
				break;
			case IDLE_TIMEOUT_2:
				printf ("Idle Timeout              [10]: 2 ms\n");
				break;
			case IDLE_TIMEOUT_4:
				printf ("Idle Timeout              [10]: 4 ms\n");
				break;
			case IDLE_TIMEOUT_5:
				printf ("Idle Timeout              [10]: 5 ms\n");
				break;
			case IDLE_TIMEOUT_6:
				printf ("Idle Timeout              [10]: 6 ms\n");
				break;
			case IDLE_TIMEOUT_8:
				printf ("Idle Timeout              [10]: 8 ms\n");
				break;
			case IDLE_TIMEOUT_10:
				printf ("Idle Timeout              [10]: 10 ms\n");
				break;
			case IDLE_TIMEOUT_15:
				printf ("Idle Timeout              [10]: 15 ms\n");
				break;
		}
		printf ("\n");
		printf ("Receive long IR Repeats   [11]: %c\n",(status->stat[bus][adr].extended_mode2 & INSTANT_REP_COUNT ? 'x':'o'));
		if (((status->stat[bus][adr].extended_mode_ex[0] & 0x7) >= 4 && (status->stat[bus][adr].extended_mode_ex[0] & 0x7) <= 6) ||
			((status->stat[bus][adr].extended_mode_ex[0] & 0x70) >= 0x40 && (status->stat[bus][adr].extended_mode_ex[0] & 0x70) <= 0x60)) {
			printf ("B&O Mode                  [12]: %c\n",(status->stat[bus][adr].extended_mode & BO_MODE ? 'x':'o'));
		}

		printf ("No Sort of IR Codes       [13]: %c\n",(status->stat[bus][adr].extended_mode & RCV_NO_SORT ? 'x':'o'));
		printf ("Always RAW Mode           [14]: %c\n",(status->stat[bus][adr].device_mode & DEVMODE_RAW ? 'x':'o'));
		printf ("Framelength for IR Repeat [15]: %c\n",(status->stat[bus][adr].extended_mode2 & IR_FRAMELENGTH ? 'x':'o'));
		printf ("\n");
		printf ("Done                      [16]\n");

		printf ("\nSelect command ");
		fflush (stdout);
	}
	else if (panel == 3) {
		printf ("\n");
		printf ("RCMM Detection             [1]: %c\n",(status->stat[bus][adr].extended_mode_ex[3] & CHECK_RCMM ? 'x':'o'));
		printf ("Force RCMM Detection       [2]: %c\n",(status->stat[bus][adr].extended_mode_ex[3] & FORCE_RCMM ? 'x':'o'));
		printf ("RCMM Toggle support        [3]: %c\n",(status->stat[bus][adr].extended_mode_ex[3] & RCMM_TOGGLE ? 'x':'o'));
		printf ("\n");
		printf ("RC5 Detection              [4]: %c\n",(status->stat[bus][adr].extended_mode_ex[3] & RC5_DETECT ? 'x':'o'));
		printf ("Ignore RC5 Toggle bit      [5]: %c\n",(status->stat[bus][adr].device_mode & IGNORETOG_RC5 ? 'x':'o'));
		printf ("\n");
		printf ("RC6 Detection              [6]: %c\n",(status->stat[bus][adr].extended_mode_ex[3] & RC6_DETECT ? 'x':'o'));
		printf ("Ignore RC6 Toggle bit      [7]: %c\n",(status->stat[bus][adr].extended_mode_ex[3] & IGNORETOG_RC6 ? 'x':'o'));
		printf ("\n");
		printf ("56 kHz R-Step Keyboard     [8]: %c\n\n",(status->stat[bus][adr].extended_mode_ex[3] & RSTEP_KEYBOARD ? 'x':'o'));

		if (status->stat[bus][adr].extended_mode_ex[4] & TOGGLE_MAP_MASK) {
			printf ("Map out toggle bit at      [9]: %d\n",(status->stat[bus][adr].extended_mode_ex[4] & TOGGLE_MAP_MASK) - 1);
			printf ("Number of toggle bits     [10]: %d\n",(status->stat[bus][adr].extended_mode_ex[4] & TOGGLE_MAP_LEN) / 128 + 1);
		}
		else printf ("Map out toggle bit at      [9]: -\n");
		printf ("\nIR Duty Cycle             [11]: 1:%c\n",(status->stat[bus][adr].extended_mode_ex[3] & DUTY_CYCLE_4 ? '4':'2'));

		printf ("\n");
		printf ("Done                      [12]\n");

		printf ("\nSelect command ");
		fflush (stdout);
	}
	else if (panel == 4) {
		printf ("\n");
		printf ("Repeat Mask: ");
		for (i=0;i<16;i++) {
			printf ("%c  ",(status->stat[bus][adr].send_mask & (1 << i) ? 'x':'o'));
		}
		printf ("\n             0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15\n\n");
		printf ("SBUS Receive              [16]: %c\n",(status->stat[bus][adr].device_mode & DEVMODE_SBUS ? 'x':'o'));
		printf ("SBUS Send                 [17]: %c\n",(status->stat[bus][adr].extended_mode_ex[5] & SBUS_SEND_MODE ? 'x':'o'));
		printf ("SBUS Remote Control       [18]: %c\n",(status->stat[bus][adr].device_mode & DEVMODE_SBUSCODE ? 'x':'o'));
		printf ("SBUS Repeat               [19]: %c\n",(status->stat[bus][adr].device_mode & DEVMODE_REPEAT ? 'x':'o'));

		if (status->stat[bus][adr].device_mode & DEVMODE_SBUS_UART) {
			switch (status->stat[bus][adr].extended_mode_ex[2] & SBUS_BAUD_MASK) {
				case SBUS_BAUD_4800:
					printf ("SBUS Baudrate             [20]: 4800 Baud\n");
					break;
				case SBUS_BAUD_9600:
					printf ("SBUS Baudrate             [20]: 9600 Baud\n");
					break;
				case SBUS_BAUD_19200:
					printf ("SBUS Baudrate             [20]: 19200 Baud\n");
					break;
				case SBUS_BAUD_38400:
					printf ("SBUS Baudrate             [20]: 38400 Baud\n");
					break;
			}
		}
		else printf ("SBUS Baudrate             [20]: Classic\n");

		printf ("\n");
		printf ("Done                      [21]\n");

		printf ("\nSelect command ");
		fflush (stdout);
	}
	else if (panel == 5) {
		printf ("\n");
		if (!(status->stat[bus][adr].features & FN_SOFTID) || (status->stat[bus][adr].features & FN_POWERON) || (status->stat[bus][adr].features & FN_USBWAKEUP)) {
			printf ("PowerOn Remote               [1]: %s\n",status->stat[bus][adr].remote);
			printf ("PowerOn Command              [2]: %s\n",status->stat[bus][adr].command);
		}

		if (status->stat[bus][adr].features & FN_DUALPOWERON) {
			printf ("\nPowerOff Remote              [3]: %s\n",status->stat[bus][adr].remote2);
			printf ("PowerOff Command             [4]: %s\n",status->stat[bus][adr].command2);
		}

		if (status->stat[bus][adr].version[0] == 'E') {
			printf ("\nPowerOn MAC Address          [5]: ");

			if (!memcmp (status->stat[bus][adr].remote2,"@@@~~~LAN~~~@@@",15) &&
				(status->stat[bus][adr].command2[0] != 0 || status->stat[bus][adr].command2[1] != 0 || status->stat[bus][adr].command2[2] != 0 ||
				 status->stat[bus][adr].command2[3] != 0 || status->stat[bus][adr].command2[4] != 0 || status->stat[bus][adr].command2[5] != 0)) {
				for (i=0;i <= 5;i++) {
					printf ("%02x",(byte)status->stat[bus][adr].command2[i]);
					if (i < 5) printf ("-");
				}
				printf ("\n");
			}

		}

		printf ("\n");
		printf ("Done                         [6]\n");

		printf ("\nSelect command ");
		fflush (stdout);
	}
	else if (panel == 6) {
		printf ("\n");

		switch (status->stat[bus][adr].extended_mode2 & RS232_BAUD_MASK) {
			case RS232_BAUD_4800:
				printf ("RS232 Baudrate            [1]: 4800 Baud\n");
				break;
			case RS232_BAUD_9600:
				printf ("RS232 Baudrate            [1]: 9600 Baud\n");
				break;
			case RS232_BAUD_19200:
				printf ("RS232 Baudrate            [1]: 19200 Baud\n");
				break;
			case RS232_BAUD_38400:
				printf ("RS232 Baudrate            [1]: 38400 Baud\n");
				break;
		}

		if ((status->stat[bus][adr].features2 & FN2_RTS_CTS) || (status->stat[bus][adr].features & FN_LAN)) {
			printf ("RTS/CTS Handshake         [2]: %c\n",(status->stat[bus][adr].extended_mode2 & RS232_RTS_CTS ? 'x':'o'));
		}

		printf ("\n");
		printf ("Done                      [3]\n");

		printf ("\nSelect command ");
		fflush (stdout);
	}
}

int SelectIRReceiver (int type,int num)
{
	char st[255];
	int i,choice;
	do {
		printf ("\nIR Receiver %d:\n",num);
		for (i = 1;i <= 6;i++) {
			switch (i) {
				case 1:
					printf ("56 kHz                         : [1]");
					break;
				case 2:
					printf ("38 kHz                         : [2]");
					break;
				case 4:
					printf ("455 kHz                        : [3]");
					break;
				case 5:
					printf ("455 kHz Plasma shielded        : [4]");
					break;
				case 6:
					printf ("Universal learning receiver    : [5]");
					break;
			}
			if (type == i) printf (" - SELECTED");
			if (i != 3) printf ("\n");
		}
		printf ("\n");
		printf ("Done                           : [6]\n");

		printf ("\nSelect command ");
		fflush (stdout);

		scanf ("%s",st);
		getchar ();
		choice = atoi (st);

		if (choice <= 2) type = choice;
		else if (choice <= 5) type = choice + 1;
		else if (choice == 6) return (type);
	} while (1);
}

int SelectIRFilter (int val)
{
	char st[255];
	int i,choice;
	do {
		printf ("\nIR Filter\n");

		for (i=IR_FILTER_64;i <= IR_FILTER_800;i += 32) {
			switch (i) {
				case IR_FILTER_64:
					printf ("IR Filter 64 us          : [1]");
					break;
				case IR_FILTER_120:
					printf ("IR Filter 120 us         : [2]");
					break;
				case IR_FILTER_160:
					printf ("IR Filter 160 us         : [3]");
					break;
				case IR_FILTER_280:
					printf ("IR Filter 280 us         : [4]");
					break;
				case IR_FILTER_380:
					printf ("IR Filter 380 us         : [5]");
					break;
				case IR_FILTER_480:
					printf ("IR Filter 480 us         : [6]");
					break;
				case IR_FILTER_550:
					printf ("IR Filter 550 us         : [7]");
					break;
				case IR_FILTER_800:
					printf ("IR Filter 800 us         : [8]");
					break;
			}
			if (val == i) printf (" - SELECTED");
			printf ("\n");
		}
		printf ("\n");
		printf ("Done                     : [9]\n");

		printf ("\nSelect command ");
		fflush (stdout);

		scanf ("%s",st);
		getchar ();
		choice = atoi (st);

		if (choice <= 8) val = (choice-1) * 32;
		else if (choice == 9) return (val);
	} while (1);
}

int SelectIRTolerance (int val)
{
	char st[255];
	int i,choice;
	do {
		printf ("\nIR Receive Tolerance\n");
		for (i=RCV_TOLERANCE_64;i <= RCV_TOLERANCE_960;i++) {

			switch (i) {
				case RCV_TOLERANCE_64:
					printf ("IR Receive Tolerance  64 us   : [1]");
					break;
				case RCV_TOLERANCE_96:
					printf ("IR Receive Tolerance  96 us   : [2]");
					break;
				case RCV_TOLERANCE_120:
					printf ("IR Receive Tolerance 120 us   : [3]");
					break;
				case RCV_TOLERANCE_160:
					printf ("IR Receive Tolerance 160 us   : [4]");
					break;
				case RCV_TOLERANCE_320:
					printf ("IR Receive Tolerance 320 us   : [5]");
					break;
				case RCV_TOLERANCE_480:
					printf ("IR Receive Tolerance 480 us   : [6]");
					break;
				case RCV_TOLERANCE_680:
					printf ("IR Receive Tolerance 680 us   : [7]");
					break;
				case RCV_TOLERANCE_960:
					printf ("IR Receive Tolerance 960 us   : [8]");
					break;
			}
			if (val == i) printf (" - SELECTED");
			printf ("\n");
		}
		printf ("\n");
		printf ("Done                          : [9]\n");

		printf ("\nSelect command ");
		fflush (stdout);

		scanf ("%s",st);
		getchar ();
		choice = atoi (st);

		if (choice <= 8) val = (choice-1);
		else if (choice == 9) return (val);
	} while (1);
}


int SelectIRTimeout (int val)
{
	char st[255];
	int choice;
	do {
		printf ("\nIR Timeout:     %3d          : [1-255]\n\n",val);
		  printf ("Done                         : [0]\n");
		printf ("\nSelect command ");
		fflush (stdout);

		scanf ("%s",st);
		getchar ();
		choice = atoi (st);

		if (choice >= 1 && choice <= 255) val = choice;
		else if (choice == 0) return (val);
	} while (1);
}

int SelectIdleTimeout (int val)
{
	char st[255];
	int i,choice;
	do {
		printf ("\nIR Idle Timeout\n");
		for (i=IDLE_TIMEOUT_1;i <= IDLE_TIMEOUT_15;i++) {

			switch (i) {
			case IDLE_TIMEOUT_1:
				printf ("Idle Timeout  1 ms         : [1]");
				break;
			case IDLE_TIMEOUT_2:
				printf ("Idle Timeout  2 ms         : [2]");
				break;
			case IDLE_TIMEOUT_4:
				printf ("Idle Timeout  4 ms         : [3]");
				break;
			case IDLE_TIMEOUT_5:
				printf ("Idle Timeout  5 ms         : [4]");
				break;
			case IDLE_TIMEOUT_6:
				printf ("Idle Timeout  6 ms         : [5]");
				break;
			case IDLE_TIMEOUT_8:
				printf ("Idle Timeout  8 ms         : [6]");
				break;
			case IDLE_TIMEOUT_10:
				printf ("Idle Timeout 10 ms         : [7]");
				break;
			case IDLE_TIMEOUT_15:
				printf ("Idle Timeout 15 ms         : [8]");
				break;
			}
			if (val == i) printf (" - SELECTED");
			printf ("\n");
		}
		printf ("\n");
		printf ("Done                       : [9]\n");

		printf ("\nSelect command ");
		fflush (stdout);

		scanf ("%s",st);
		getchar ();
		choice = atoi (st);

		if (choice <= 8) val = (choice-1);
		else if (choice == 9) return (val);
	} while (1);
}

int SelectTogglebit (int val)
{
	char st[255];
	int choice;
	do {
		if (!val)
			printf ("\nMap out Togglebit at:      -          : [0-62]\n\n");
		else
			printf ("\nMap out Togglebit at:     %2d          : [0-62]\n\n",val-1);
		printf ("Done                                  : [99]\n");
		printf ("\nSelect command ");
		fflush (stdout);

		scanf ("%s",st);
		getchar ();
		choice = atoi (st);

		if (choice >= 0 && choice <= 62) val = choice + 1;
		else if (choice == 99) return (val);
	} while (1);
}

int SelectSBUSBaudrate (int val)
{
	char st[255];
	int i,choice;
	do {
		printf ("\nSBUS Baudrate\n");
		for (i=SBUS_BAUD_4800;i <= SBUS_BAUD_38400 + 8;i += 8) {

			switch (i) {
				case SBUS_BAUD_4800:
					printf ("SBUS Baudrate  4800 Baud           : [1]");
					break;
				case SBUS_BAUD_9600:
					printf ("SBUS Baudrate  9600 Baud           : [2]");
					break;
				case SBUS_BAUD_19200:
					printf ("SBUS Baudrate 19200 Baud           : [3]");
					break;
				case SBUS_BAUD_38400:
					printf ("SBUS Baudrate 38400 Baud           : [4]");
					break;
				case SBUS_BAUD_38400 + 8:
					printf ("SBUS Baudrate Classic              : [5]");
					break;
			}
			if (val == i) printf (" - SELECTED");
			printf ("\n");
		}
		printf ("\n");
		printf ("Done                               : [6]\n");

		printf ("\nSelect command ");
		fflush (stdout);

		scanf ("%s",st);
		getchar ();
		choice = atoi (st);

		if (choice <= 5) val = (choice-1) * 8;
		else if (choice == 6) return (val);
	} while (1);
}

int SelectRS232Baudrate (int val)
{
	char st[255];
	int i,choice;
	do {
		printf ("\nRS232 Baudrate\n");
		for (i=RS232_BAUD_38400;i <= RS232_BAUD_4800;i += 32) {

			switch (i) {
				case RS232_BAUD_4800:
					printf ("RS232 Baudrate  4800 Baud           : [4]");
					break;
				case RS232_BAUD_9600:
					printf ("RS232 Baudrate  9600 Baud           : [3]");
					break;
				case RS232_BAUD_19200:
					printf ("RS232 Baudrate 19200 Baud           : [2]");
					break;
				case RS232_BAUD_38400:
					printf ("RS232 Baudrate 38400 Baud           : [1]");
					break;
			}
			if (val == i) printf (" - SELECTED");
			printf ("\n");
		}
		printf ("\n");
		printf ("Done                                : [5]\n");

		printf ("\nSelect command ");
		fflush (stdout);

		scanf ("%s",st);
		getchar ();
		choice = atoi (st);

		if (choice <= 4) val = (choice-1) * 32;
		else if (choice == 5) return (val);
	} while (1);
}

int SetDeviceStatusPanel (NETWORKMODEEX2 *status,int bus,int adr,int panel)
{
	char st[255];
	int choice,sel;

	scanf ("%s",st);
	getchar ();
	choice = atoi (st);

	if (panel == 1) {
		if (choice == 1) status->stat[bus][adr].device_mode ^= DEVMODE_SEND;
		else if (choice == 2) status->stat[bus][adr].device_mode ^= DEVMODE_IR;
		else if (choice == 3) status->stat[bus][adr].extended_mode ^= INTERNAL_LEDS;
		else if (choice == 4) status->stat[bus][adr].extended_mode ^= EXTERNAL_LEDS;
		else if (choice == 5) status->stat[bus][adr].extended_mode ^= SELF_REPEAT;
		else if (choice == 6) status->stat[bus][adr].extended_mode ^= INTERNAL_REPEAT;

		else if (choice == 7) return (0);
		return (1);
	}
	if (panel == 2) {
		if (choice == 1) {
			sel = SelectIRReceiver (status->stat[bus][adr].extended_mode_ex[0] & 0x7,1);
			status->stat[bus][adr].extended_mode_ex[0] = (status->stat[bus][adr].extended_mode_ex[0] & ~7) | sel;
		}
		else if (choice == 2) status->stat[bus][adr].extended_mode_ex[0] ^= 8;
		else if (choice == 3) status->stat[bus][adr].extended_mode ^= STANDARD_RCV;
		else if (choice == 4) {
			if (status->stat[bus][adr].features & FN_DUALRCV) {
				sel = SelectIRReceiver ((status->stat[bus][adr].extended_mode_ex[0] & 0x70) >> 4,2);
				status->stat[bus][adr].extended_mode_ex[0] = (status->stat[bus][adr].extended_mode_ex[0] & ~0x70) | (sel << 4);
			}
		}
		else if (choice == 5) {
			if (status->stat[bus][adr].features & FN_DUALRCV) status->stat[bus][adr].extended_mode_ex[0] ^= 0x80;
		}
		else if (choice == 6) {
			if (status->stat[bus][adr].features & FN_DUALRCV) status->stat[bus][adr].extended_mode ^= HI_RCV;
		}
		else if (choice == 7) {
			sel = SelectIRFilter (status->stat[bus][adr].extended_mode_ex[2] & IR_FILTER_MASK);
			status->stat[bus][adr].extended_mode_ex[2] = (status->stat[bus][adr].extended_mode_ex[2] & ~IR_FILTER_MASK) | sel;
		}
		else if (choice == 8) {
			sel = SelectIRTolerance (status->stat[bus][adr].extended_mode2 & RCV_TOLERANCE_MASK);
			status->stat[bus][adr].extended_mode2 = (status->stat[bus][adr].extended_mode2 & ~RCV_TOLERANCE_MASK) | sel;
		}
		else if (choice == 9) {
			status->stat[bus][adr].extended_mode_ex[1] = SelectIRTimeout (status->stat[bus][adr].extended_mode_ex[1]);
		}
		else if (choice == 10) {
			sel = SelectIdleTimeout (status->stat[bus][adr].extended_mode_ex[2] & IDLE_TIMEOUT_MASK);
			status->stat[bus][adr].extended_mode_ex[2] = (status->stat[bus][adr].extended_mode_ex[2] & ~IDLE_TIMEOUT_MASK) | sel;
		}
		else if (choice == 11) status->stat[bus][adr].extended_mode2 ^= INSTANT_REP_COUNT;
		else if (choice == 12) status->stat[bus][adr].extended_mode ^= BO_MODE;
		else if (choice == 13) status->stat[bus][adr].extended_mode ^= RCV_NO_SORT;
		else if (choice == 14) status->stat[bus][adr].device_mode ^= DEVMODE_RAW;
		else if (choice == 15) status->stat[bus][adr].extended_mode2 ^= IR_FRAMELENGTH;


		else if (choice == 16) return (0);
		return (1);
	}
	else if (panel == 3) {
		if (choice == 1) status->stat[bus][adr].extended_mode_ex[3] ^= CHECK_RCMM;
		else if (choice == 2) status->stat[bus][adr].extended_mode_ex[3] ^= FORCE_RCMM;
		else if (choice == 3) status->stat[bus][adr].extended_mode_ex[3] ^= RCMM_TOGGLE;
		else if (choice == 4) status->stat[bus][adr].extended_mode_ex[3] ^= RC5_DETECT;
		else if (choice == 5) status->stat[bus][adr].device_mode ^= IGNORETOG_RC5;
		else if (choice == 6) status->stat[bus][adr].extended_mode_ex[3] ^= RC6_DETECT;
		else if (choice == 7) status->stat[bus][adr].extended_mode_ex[3] ^= IGNORETOG_RC6;
		else if (choice == 8) status->stat[bus][adr].extended_mode_ex[3] ^= RSTEP_KEYBOARD;

		else if (choice == 9) {
			sel = SelectTogglebit (status->stat[bus][adr].extended_mode_ex[4] & TOGGLE_MAP_MASK);
			status->stat[bus][adr].extended_mode_ex[4] = (status->stat[bus][adr].extended_mode_ex[4] & ~TOGGLE_MAP_MASK) | sel;
		}
		else if (choice == 10) status->stat[bus][adr].extended_mode_ex[4] ^= TOGGLE_MAP_LEN;
		else if (choice == 11) status->stat[bus][adr].extended_mode_ex[3] ^= DUTY_CYCLE_4;

		else if (choice == 12) return (0);
		return (1);
	}
	else if (panel == 4) {
		if (choice >= 0 && choice <= 15) {
			status->stat[bus][adr].send_mask ^=  1 << choice;
		}
		else if (choice == 16) status->stat[bus][adr].device_mode ^= DEVMODE_SBUS;
		else if (choice == 17) status->stat[bus][adr].extended_mode_ex[5] ^= SBUS_SEND_MODE;
		else if (choice == 18) status->stat[bus][adr].device_mode ^= DEVMODE_SBUSCODE;
		else if (choice == 19) status->stat[bus][adr].device_mode ^= DEVMODE_REPEAT;
		else if (choice == 20) {
			if (status->stat[bus][adr].device_mode & DEVMODE_SBUS_UART) sel = SelectSBUSBaudrate (status->stat[bus][adr].extended_mode_ex[2] & SBUS_BAUD_MASK);
			else sel = SelectSBUSBaudrate (SBUS_BAUD_38400 + 8);
			if (sel == 32) status->stat[bus][adr].device_mode &= ~DEVMODE_SBUS_UART;
			else {
				status->stat[bus][adr].device_mode |= DEVMODE_SBUS_UART;
				status->stat[bus][adr].extended_mode_ex[2] = (status->stat[bus][adr].extended_mode_ex[2] & ~SBUS_BAUD_MASK) | sel;
			}
		}
		else if (choice == 21) return (0);
		return (1);
	}
	else if (panel == 5) {
		if (choice == 1) {
			printf ("\n\nEnter PowerOn Remote: ");
			fflush (stdout);
			memset (st,0,255);
			fgets (st,255,stdin);
			while (st[strlen (st) - 1] == 10 || st[strlen (st) - 1] == 13) st[strlen (st) - 1] = 0;
			memcpy (status->stat[bus][adr].remote,st,80);

		}
		if (choice == 2) {
			printf ("\n\nEnter PowerOn Command: ");
			fflush (stdout);
			memset (st,0,255);
			fgets (st,255,stdin);
			while (st[strlen (st) - 1] == 10 || st[strlen (st) - 1] == 13) st[strlen (st) - 1] = 0;
			memcpy (status->stat[bus][adr].command,st,20);

		}
		if (choice == 3) {
			printf ("\n\nEnter PowerOff Remote: ");
			fflush (stdout);
			memset (st,0,255);
			fgets (st,255,stdin);
			while (st[strlen (st) - 1] == 10 || st[strlen (st) - 1] == 13) st[strlen (st) - 1] = 0;
			memcpy (status->stat[bus][adr].remote2,st,80);

		}
		if (choice == 4) {
			printf ("\n\nEnter PowerOff Command: ");
			fflush (stdout);
			memset (st,0,255);
			fgets (st,255,stdin);
			while (st[strlen (st) - 1] == 10 || st[strlen (st) - 1] == 13) st[strlen (st) - 1] = 0;
			memcpy (status->stat[bus][adr].command2,st,20);

		}
		if (choice == 5) {
			printf ("\n\nEnter MAC Address: ");
			fflush (stdout);
			memset (st,0,255);
			fgets (st,255,stdin);
			while (st[strlen (st) - 1] == 10 || st[strlen (st) - 1] == 13) st[strlen (st) - 1] = 0;
			if (st[0] == 0 || st[1] == 0) {
				memset (status->stat[bus][adr].command2,0,6);
			}
			else {
				memcpy (status->stat[bus][adr].remote2,"@@@~~~LAN~~~@@@",15);
				status->stat[bus][adr].command2[0] = (byte)strtol (st + 0,NULL,16);
				status->stat[bus][adr].command2[1] = (byte)strtol (st + 3,NULL,16);
				status->stat[bus][adr].command2[2] = (byte)strtol (st + 6,NULL,16);
				status->stat[bus][adr].command2[3] = (byte)strtol (st + 9,NULL,16);
				status->stat[bus][adr].command2[4] = (byte)strtol (st + 12,NULL,16);
				status->stat[bus][adr].command2[5] = (byte)strtol (st + 15,NULL,16);
			}

		}
		else if (choice == 6) return (0);
		return (1);
	}
	else if (panel == 6) {
		if (choice == 1) {
			sel = SelectRS232Baudrate (status->stat[bus][adr].extended_mode2 & RS232_BAUD_MASK);
			status->stat[bus][adr].extended_mode2 = (status->stat[bus][adr].extended_mode2 & ~RS232_BAUD_MASK) | sel;
		}
		else if (choice == 2) status->stat[bus][adr].extended_mode2 ^= RS232_RTS_CTS;
		else if (choice == 3) return (0);
		return (1);
	}

	return (0);
}

void SetDeviceStatusEx (NETWORKMODEEX2 *status,int bus,int adr)
{
	char st[255];
	int res,choice = 0;
	MODUSCOMMAND_EX mod;
	NETWORKSTATUS stat;

	while (choice < 7) {
		while (choice < 1 || choice > 8) {
			printf ("\n\nDevice [%d-%d]: %s\n\n",bus,adr,status->stat[bus][adr].version);
			printf (" 1: General Settings\n");
			printf (" 2: IR Settings\n");
			printf (" 3: IR Code Settings\n");
			printf (" 4: IR Bus Settings\n");
			printf (" 5: PowerOn Settings\n");
			printf (" 6: RS232 Settings\n");

			printf ("\n 7: Save Settings\n");
			printf (" 8: Cancel\n");

			printf ("\nSelect panel: ");
			fflush (stdout);
			scanf ("%s",st);
			getchar ();
			choice = atoi (st);
		}

		if (choice < 7) {

			do {
				ShowDeviceStatusEx (status,bus,adr,choice);
			} while (SetDeviceStatusPanel (status,bus,adr,choice));


			choice = 0;
		}

		if (choice == 7) {
			mod.netcommand = COMMAND_SETSTATEX2;
			mod.adress = adr + bus * 256;
			mod.protocol_version = 210;
			memcpy (mod.hotremote ,status->stat[bus][adr].remote,80);
			memcpy (mod.hotcommand,status->stat[bus][adr].command,20);

			memcpy (mod.hotremote_2 ,status->stat[bus][adr].remote2,80);
			if (!memcmp (status->stat[bus][adr].remote2,"@@@~~~LAN~~~@@@",15)) {
				memcpy (mod.wakeup_mac,status->stat[bus][adr].command2,6);
				strcpy (mod.hotremote_2,"_");
			}
			else memcpy (mod.hotcommand_2,status->stat[bus][adr].command2,20);

			mod.targetmask = status->stat[bus][adr].send_mask;
			mod.mode = status->stat[bus][adr].device_mode;
			mod.extmode = status->stat[bus][adr].extended_mode;
			mod.extmode_2 = status->stat[bus][adr].extended_mode2;
			memcpy (mod.extmode_ex,status->stat[bus][adr].extended_mode_ex,8);

			res = SendCommand ((NETWORKCOMMAND *)&mod,&stat);
			if (res) {
				printf ("\nSet Device Status Result: %d\n",res);
			}

		}
	}
}

void SetDeviceStatus (NETWORKMODEEX2 *status,int bus,int adr)
{
	int res;
	char st[255];
	int choice = 0;
	NETWORKCOMMAND command;
	NETWORKSTATUS stat;

	while (choice < 56) {
		ShowSetStatus (adr,bus,status);

		scanf ("%s",st);
		getchar ();
		choice = atoi (st);

		if (choice < 20) status->stat[bus][adr].send_mask ^= 1 << choice;

		else if (choice < 30) status->stat[bus][adr].device_mode ^= 1 << (choice - 20);
		else if (choice <= 44) {
			if (choice >= 37 && choice <= 44) status->stat[bus][adr].extended_mode2 = choice - 37;
			else {
				if (choice == 32) choice = 36;
				else if (choice > 32) choice--;
				status->stat[bus][adr].extended_mode ^= 1 << (choice - 30);
			}
		}
		if (choice == 45) status->stat[bus][adr].device_mode &= ~DEVMODE_RAWFAST;
		if (choice == 46) status->stat[bus][adr].device_mode |= DEVMODE_RAWFAST;
		if (choice >= 47 && choice <= 51) {
			if (choice == 47) status->stat[bus][adr].extended_mode &= ~SBUS_UART;
			else {
				status->stat[bus][adr].extended_mode2 &= ~SBUS_BAUD_MASK;
				status->stat[bus][adr].extended_mode2 |= (choice - 48) * 8;
				status->stat[bus][adr].extended_mode |= SBUS_UART;
			}
		}

		if (choice == 52) {
			printf ("\nEnter PowerOn Remote: ");
			fflush (stdout);
			scanf ("%s",status->stat[bus][adr].remote);
		}

		if (choice == 53) {
			printf ("\nEnter PowerOn Command: ");
			fflush (stdout);
			scanf ("%s",status->stat[bus][adr].command);
		}

		if (choice == 54) {
			printf ("\nEnter PowerOff Remote: ");
			fflush (stdout);
			scanf ("%s",status->stat[bus][adr].remote2);
		}

		if (choice == 55) {
			printf ("\nEnter PowerOff Command: ");
			fflush (stdout);
			scanf ("%s",status->stat[bus][adr].command2);
		}

		if (choice == 99) {
			command.netcommand = COMMAND_SETSTAT;
			strcpy (command.command,status->stat[bus][adr].command);
			strcpy (command.remote,status->stat[bus][adr].remote);
			command.timeout = adr;
			command.mode = status->stat[bus][adr].device_mode;
			command.adress = status->stat[bus][adr].send_mask | (status->stat[bus][adr].extended_mode  << 16);
			command.trasmit_freq = status->stat[bus][adr].extended_mode2;
			memset (&stat,0,sizeof (stat));
			res = SendCommand (&command,&stat);

			if (res) return;

			if (stat.statustype == STATUS_MESSAGE) {
				PrintStatError (&stat);
				return;
			}
			if (status->stat[bus][adr].features & FN_DUALPOWERON) {
				command.netcommand = COMMAND_SETSTAT2;
				strcpy (command.command,status->stat[bus][adr].command2);
				strcpy (command.remote,status->stat[bus][adr].remote2);
				memset (&stat,0,sizeof (stat));
				res = SendCommand (&command,&stat);

				if (res) return;

				if (stat.statustype == STATUS_MESSAGE) {
					PrintStatError (&stat);
					return;
				}
			}
		}

	}
}



int StatusMenu (void)
{
	char st[255];
	int choice = 0;
	int res,i,j,cnt,num,bus,dev;
	NETWORKMODEEX2 status;
	NETWORKCOMMAND com;


	printf ("Getting Device Status ...");
	fflush (stdout);

	com.netcommand = COMMAND_STATUSEX2;

	memset (&status,0,sizeof (status));
	res = SendCommand (&com,(NETWORKSTATUS *)&status);
	if (res) {
		printf ("\nDevice Status Result: %d\n",res);
		return (0);
	}

	if (status.statustype != STATUS_DEVICEMODEEX2) {
		PrintStatError ((NETWORKSTATUS *)&status);
		return (0);
	}

	cnt = 0;
	for (j=0;j < status.count;j++) {
		for (i=0;i < 16;i++) {
			if (status.stat[j][i].version[0]) cnt++;
			status.stat[j][i].version[8] = 0;
		}
	}

	printf ("%c                                   \n%d Device(s) Found:\n\n",13,cnt);
	num = 0;
	for (j=0;j < status.count;j++) {
		for (i=0;i < 16;i++) {
			if (status.stat[j][i].version[0]) printf ("%2d: - %s\n",num++,status.stat[j][i].version);
		}
	}

	printf ("\n99 - Exit\n");
	printf ("\nSelect command ");
	fflush (stdout);
	scanf ("%s",st);
	getchar ();
	choice = atoi (st);

	if (choice == 99) return (0);

	num = -1;
	for (j=0;j < status.count;j++) {
		for (i=0;i < 16;i++) {
			if (status.stat[j][i].version[0]) {
				num++;
				if (num == choice) {
					bus = j;
					dev = i;
					break;
				}
			}
		}
	}

	if (memcmp (status.stat[bus][dev].version + 1,"6.00.00",7) >= 0) SetDeviceStatusEx (&status,bus,dev);
	else SetDeviceStatus (&status,bus,dev);

	return (0);
}

int MainMenu (void)
{
	char st[255];
	int choice = 0;

	BuildMainMenu ();
	scanf ("%s",st);
	getchar ();
	choice = atoi (st);

	switch (choice) {
		case 1:
			while (SendMenu ());
			break;
		case 2:
			while (LearnMenu ());
			break;
		case 3:
			while (StatusMenu ());
			break;
		case 99:
			return (0);
			break;
	}

	return (1);
}


void BuildMainMenu ()
{
	printf ("\n\n  1 - Send\n");
	printf ("  2 - Learn\n");
	printf ("  3 - Status\n");
	printf ("\n 99 - Exit\n");
	printf ("\nSelect command ");
	fflush (stdout);
}


void BuildSendMenu ()
{
	printf ("\n\n**Selected Remote: [%s]\n\n",send_remote);
	printf ("  1 - Select remote\n");
	printf ("  2 - Send command\n");
	printf ("  3 - Send LCD\n");
	printf ("  4 - Set LCD Init String\n");
	printf ("  5 - Set Switch\n");
	printf ("\n 99 - Exit\n");
	printf ("\nSelect command ");
	fflush (stdout);
}

void BuildLearnMenu ()
{
	printf ("\n\n**Selected Remote: [%s]\n\n",learn_remote);
	printf ("  1 - Select remote\n");
	printf ("  2 - Learn Timing\n");
	printf ("  3 - Learn Command [Based on timing]\n");
	printf ("  4 - Learn Command [Command with timing]\n");
	printf ("  5 - Learn Command [RAW Data]\n");
	printf ("\n 99 - Exit\n");
	printf ("\nSelect command ");
	fflush (stdout);
}

void PrintStatError (NETWORKSTATUS *stat)
{
	printf ("%s\n",stat->message);
}

int FlashIRDB (int bus,char *action,char *remotelist)
{
	int res;
	char *pnt;
	word counter = 0;
	NETWORKSTATUS stat;

	res = NetworkCommand (COMMAND_STOREIRDB,"",action,counter++,0,&stat);
	if (res) {
		fprintf (stderr,"Error uploading IRDB Header: %s\n",stat.message);
		return (-1);
	}

	pnt = strtok (remotelist,",;");
	while (pnt) {
		res = NetworkCommand (COMMAND_STOREIRDB,pnt,"",counter++,0,&stat);
		if (res) {
			return (-1);
		}
		pnt = strtok (NULL,",;");
	}

	res = NetworkCommand (COMMAND_FLASHIRDB,"","",(word)bus,0,&stat);
//	res = NetworkCommand (COMMAND_SAVEIRDB,"mcc","",(word)bus,0,&stat);
	if (res) {
		return (-1);
	}

	return (0);
}

int LoadIRDB (int bus,char *filename)
{
	int res,md = 0;
	char rcv[255];
	NETWORKSTATUS stat;

	res = NetworkCommand (COMMAND_LOADIRDBFILE,filename,"",0,0,&stat);
	if (res) {
		fprintf (stderr,"Error opening IRDB File: %s\n",stat.message);
		return (-1);
	}


	if (bus == 99) {
		bus = 0;
		md = 0x20;
	}
	res = NetworkCommand (COMMAND_FLASHIRDB,"","",(word)bus,md,&stat);
	if (res) return (-1);

	do {
		ReceiveIR (0,rcv);
	} while (rcv[0] != 'F');


	if (rcv[1] == '0') printf ("IRDB Flash Error\n");

	if (rcv[1] == '2') printf ("IRDB Flash OK\n");

	return (0);
}

int NetworkCommand (int netcommand,char remote[],char command[],word timeout,int adr,NETWORKSTATUS *stat)
{
	int res;
	LCDCOMMAND *lcd;
	SERCOMMAND *ser;
	NETWORKCOMMAND *com;
	IRDBHEADER irdb;
	IRDBCOMMAND *irdbcom;

	memset (&irdb,0,sizeof (irdb));

	com = (NETWORKCOMMAND *)&irdb;
	lcd = (LCDCOMMAND *)&irdb;
	ser = (SERCOMMAND *)&irdb;
	irdbcom = (IRDBCOMMAND *)&irdb;

	com->adress = adr;
	com->netcommand = netcommand;

	if (netcommand == COMMAND_STOREIRDB) {
		irdb.number = timeout;
		if (remote[0]) {	// Remote
			irdb.type = IRDB_REM;
			strcpy (irdbcom->remote,remote);
			irdbcom->action_type = 1;
		}
		else {				// Header
			irdb.type = IRDB_TYPEHEADER;
			strcpy (irdb.default_action,command);
			irdb.active = 3;
		}
	}

	else if (netcommand == COMMAND_FLASHIRDB) {
		com->adress |= timeout * 256;
	}
	else if (netcommand == COMMAND_LCD || netcommand == COMMAND_LCDINIT) {
		strcpy (lcd->framebuffer,remote);
		lcd->hgt = 4;
		lcd->wid = 40;
		lcd->lcdcommand = (byte)timeout;
	}
	else if (netcommand == COMMAND_SETSWITCH) {
		com->remote[0] = remote[0];
		com->command[0] = command[0];
	}
	else if (netcommand == COMMAND_RS232_SEND) {
		ser->len = strlen (remote);
		strcpy (ser->data,remote);
	}
	else {
		strcpy (com->remote,remote);
		if (command) strcpy (com->command,command);
		com->timeout = timeout;
	}
	res = SendCommand (com,stat);

	if (res) {
		fprintf (stderr,"ERROR Sending Command: %d\n",res);
		exit (res);
	}
	if (stat->statustype == STATUS_MESSAGE && stat->netstatus) {
		PrintStatError (stat);
		if (stat -> statuslevel == FATAL) exit (res);
	}
	return (stat->netstatus);
}


int SendCommand (NETWORKCOMMAND *com,NETWORKSTATUS *stat)
{
	STATUSBUFFER buf;
	int res,size;
	fd_set events;
	struct timeval tv;

	com->protocol_version = 210;
	size = sizeof (NETWORKCOMMAND);
	if (com->netcommand == COMMAND_LCD || com->netcommand == COMMAND_LCDINIT) size = sizeof (LCDCOMMAND);
	if (com->netcommand == COMMAND_RS232_SEND) size = sizeof (SERCOMMAND);
	if (com->netcommand == COMMAND_STOREIRDB) size = sizeof (IRDBHEADER);
	if (com->netcommand == COMMAND_STORETIMER) size = sizeof (TIMERCOMMAND);
	if (com->netcommand == COMMAND_SETSTATEX2) size = sizeof (MODUSCOMMAND_EX);

	res = send (serv,(char *)com,size,0);

	if (res != size) {
		closesocket (serv);
		return (ERR_SEND);
	}

	memset (stat,0,sizeof (NETWORKSTATUS));

	if (com->timeout) tv.tv_sec = com->timeout/1000 + 1;
	else tv.tv_sec = 5;

	if (com->netcommand == COMMAND_STATUSEX2) tv.tv_sec = 10;

	tv.tv_usec = 0;
	FD_ZERO (&events);
	FD_SET (serv,&events);
	res = select (serv+1,&events,NULL,NULL,&tv);

	if (res <= 0) return (ERR_TIMEOUT);

	do {
		res = 0;
		do {
			res += recv (serv,((char *)&buf) + res,32768,0);
		} while (res < buf.statuslen);

		if (res && (buf.statustype == STATUS_MESSAGE || buf.statustype == STATUS_DEVICEMODEEX2  || buf.statustype == STATUS_DEVICEMODEEXN || buf.statustype == STATUS_REMOTELIST || buf.statustype == STATUS_COMMANDLIST)) memcpy (stat,&buf,res);
		if (res == 8) return (0);

	} while (buf.statustype == STATUS_RECEIVE);

	return (0);
}




int InitClientSocket (char host[],SOCKET *sock,unsigned long id)
{
	struct sockaddr_in serv_addr;
	unsigned long adr;
	struct hostent *he;
//	struct in_addr addr;

#ifdef WIN32

	int err;
    WORD	wVersionRequired;
    WSADATA	wsaData;
    wVersionRequired = MAKEWORD(2,2);
    err = WSAStartup(wVersionRequired, &wsaData);
    if (err != 0) exit(1);

#endif

	adr = inet_addr (host);
	if (adr == INADDR_NONE) {
		he = (struct hostent *)gethostbyname (host);
		if (he == NULL) return (ERR_FINDHOST);
		memcpy(&adr, he->h_addr_list[0],4);
	}



	*sock = socket (PF_INET,SOCK_STREAM,0);
	if (*sock < 0) return (ERR_OPENSOCKET);

	memset (&serv_addr,0,sizeof (serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = adr;
	serv_addr.sin_port = htons (TCP_PORT);

	if (connect (*sock,(struct sockaddr *)&serv_addr,sizeof (serv_addr)) < 0) return (ERR_CONNECT);

	send (*sock,(char *)&id,4,0);

	return (0);
}
