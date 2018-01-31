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

#ifdef LINUX
typedef int SOCKET;
typedef int WSAEVENT;
#endif


#define PROTOCOL_VERSION	209

#define MAX_IR_DEVICES	256


#define COMMAND_SEND		1
#define COMMAND_LRNREM		2
#define COMMAND_LRNTIM		3
#define COMMAND_LRNCOM		4
#define COMMAND_CLOSE		5
#define COMMAND_STATUS		6
#define COMMAND_RESEND		7
#define COMMAND_LRNRAW		8
#define COMMAND_LRNRPT		9
#define COMMAND_LRNTOG		10
#define COMMAND_SETSTAT		11
#define COMMAND_LRNLONG		12
#define COMMAND_LRNRAWRPT	13
#define COMMAND_RELOAD		14
#define COMMAND_LCD			15
#define COMMAND_LEARNSTAT	16
#define COMMAND_TEMP		17
#define COMMAND_GETREMOTES	18
#define COMMAND_GETCOMMANDS	19
#define COMMAND_STORETRANS	20
#define COMMAND_LOADTRANS	21
#define COMMAND_SAVETRANS	22
#define COMMAND_FLASHTRANS	23
#define	COMMAND_FUNCTIONS	24
#define	COMMAND_TESTCOM		25
#define	COMMAND_LONGSEND	26
#define	COMMAND_SHUTDOWN	27
#define COMMAND_SENDCCF		28
#define COMMAND_LCDINIT		29
#define COMMAND_SETSWITCH	30
#define COMMAND_STATUSEX	31
#define COMMAND_RESET		32
#define	COMMAND_DEVICEDATA	33
#define	COMMAND_STARTCLOCK	34
#define	COMMAND_LCDSTATUS	35
#define	COMMAND_FUNCTIONEX	36
#define COMMAND_MCE_CHARS	37
#define COMMAND_SUSPEND		38
#define COMMAND_RESUME		39
#define COMMAND_DELETECOM	40
#define COMMAND_EMPTY		41
#define COMMAND_SETSTAT2	42
#define COMMAND_STATUSEXN	43
#define COMMAND_BRIGHTNESS	44
#define COMMAND_DEFINECHAR	45
#define COMMAND_STOREIRDB	46
#define COMMAND_FLASHIRDB	47
#define COMMAND_SAVEIRDB	48
#define COMMAND_LOADIRDB	49
#define COMMAND_LED			50
#define COMMAND_TRANSFILE	51
#define COMMAND_IRDBFILE	52
#define COMMAND_LISTBUS		53
#define COMMAND_SENDCCFSTR	54
#define COMMAND_LEARNDIRECT	55
#define COMMAND_TESTCOMEX	56
#define COMMAND_SENDCCFSTRS	57
#define COMMAND_SETSTATEX	58
#define COMMAND_DELETEREM	59
#define COMMAND_READ_ANALOG 60
#define COMMAND_RS232_SEND	61
#define COMMAND_SENDCCFLONG	62
#define COMMAND_STORETIMER	63
#define COMMAND_LOADIRDBFILE	64
#define COMMAND_ASCII		65
#define COMMAND_LRNREMEX	66
#define COMMAND_CLIENTLOG	67
#define COMMAND_LEARNCCF	68
#define COMMAND_STATUSEX2	69
#define COMMAND_SETSTATEX2	70
#define COMMAND_LEARNRS232	71
#define COMMAND_SENDMASK	72
#define COMMAND_RESENDMASK	73
#define COMMAND_SSIDLIST	74
#define COMMAND_WLANPARAM	75
#define COMMAND_STOREWLAN	76
#define COMMAND_READ_SYSPARAM	77
#define COMMAND_WRITE_SYSPARAM	78
#define COMMAND_LANPARAM		79
#define COMMAND_LOGLEVEL		80
#define COMMAND_LEARNLINK		81
#define COMMAND_SENDMACRO		82
#define COMMAND_READ_ANALOG_EX	83
#define COMMAND_NORECEIVE		84
#define COMMAND_CLEARFLASH		85

#define COMMAND_LAN_ANALOG	'a' // 97
#define COMMAND_LAN_PING	'p' // 112
#define COMMAND_SENDSTRING	's' // 115




#define	STATUS_MESSAGE			1
#define	STATUS_TIMING			2
#define	STATUS_DEVICEMODE		3
#define	STATUS_RECEIVE			4
#define STATUS_LEARN			5
#define STATUS_REMOTELIST		6
#define STATUS_COMMANDLIST		7
#define STATUS_TRANSLATE		8
#define STATUS_FUNCTION			9
#define	STATUS_DEVICEMODEEX		10
#define STATUS_DEVICEDATA		11
#define STATUS_LCDDATA			12
#define STATUS_FUNCTIONEX		13
#define	STATUS_DEVICEMODEEXN	14
#define STATUS_IRDB				15
#define STATUS_TRANSLATIONFILE	16
#define STATUS_IRDBFILE			17
#define STATUS_BUSLIST			18
#define STATUS_LEARNDIRECT		19
#define STATUS_IRDBFLASH		20
#define STATUS_ANALOGINPUT		21
#define STATUS_RECEIVE_ASCII	22
#define STATUS_LOG				23
#define	STATUS_DEVICEMODEEX2	24
#define STATUS_SSIDLIST			25
#define STATUS_WLANPARAMETER	26
#define STATUS_SYSPARAMETER		27
#define STATUS_LANPARAMETER		28
#define STATUS_ANALOGINPUT_EX	29

#define STATUS_ASCII			65

#define FILE_MODE_SAVE			0
#define FILE_MODE_SAVEAS		1
#define FILE_MODE_OVERWRITE		2


#pragma pack(1)

typedef struct {
	uint32_t clientid;
	int16_t statuslen;
	int16_t statustype;
	int16_t adress;
    uint8_t align[2];
	IRDATA ird;
} IRDATA_BUFFER;

typedef struct {
	uint8_t mode;
	uint8_t time_cnt;
	uint8_t ir_repeat;
	uint8_t repeat_pause;
	uint16_t pause_len[TIME_LEN];
	uint16_t pulse_len[TIME_LEN];
	uint8_t data[CODE_LEN];
} TIMINGDATA;

typedef struct {
	uint8_t netcommand;
	uint8_t mode;
	uint16_t timeout;
	int32_t adress;
	int8_t remote[80];
	int8_t command[20];
	uint8_t trasmit_freq;
} OLD_NETWORKCOMMAND;


typedef struct {
	uint8_t netcommand;
	uint8_t mode;
	uint8_t lcdcommand;
	uint8_t timeout;
	int32_t adress;
	uint8_t wid;
	uint8_t hgt;
	int8_t framebuffer[200];
} OLD_LCDCOMMAND;

typedef struct {
	uint8_t netcommand;						//   0
	uint8_t mode;							//   1
	uint16_t pause;							//   2
	int32_t adress;							//   4
	int32_t protocol_version;				//   8
	int8_t remote[80];						//  12
	int8_t command[416];					//  92
} MACRO_NETCOMMAND;							// 508

typedef struct {
	uint8_t netcommand;
	uint8_t mode;
	uint16_t timeout;
	int32_t adress;
	int32_t protocol_version;
	int8_t remote[80];
	int8_t command[20];
	uint8_t trasmit_freq;
} NETWORKCOMMAND;

typedef struct {
	uint8_t netcommand;
	uint8_t mode;
	uint16_t timeout;
	int32_t adress;
	int32_t protocol_version;
	int8_t remote[80];
	int8_t command[20];
	int8_t ccf_data[5400];
} CCFLEARNCOMMAND;


typedef struct {
	uint8_t netcommand;
	uint8_t mode;
	uint16_t timeout;
	int32_t adress;
	int32_t protocol_version;
	uint8_t num;
	uint8_t tim_mode;
    uint8_t status;
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t min;
    uint8_t weekday;
	uint8_t remote[81];
	uint8_t ircommand[21];
	uint8_t ledselect;
	uint16_t targetmask;
} TIMERCOMMAND;

typedef struct {
	uint8_t		netcommand;
	uint8_t		mode;
	uint16_t	timeout;
	int32_t		adress;
	int32_t		protocol_version;
	int8_t		hotremote[80];
	int8_t		hotcommand[20];
	int8_t		hotremote_2[80];
	int8_t		hotcommand_2[20];
	int32_t		targetmask;
	uint8_t		extmode;
	uint8_t		extmode_2;
	uint8_t		extmode_3;
	uint8_t		extmode_4;
	uint8_t		wakeup_mac[6];
} MODUSCOMMAND;

typedef struct {
	uint8_t		netcommand;
	uint8_t		mode;
	uint16_t	timeout;
	int32_t		adress;
	int32_t		protocol_version;
	int8_t		hotremote[80];
	int8_t		hotcommand[20];
	int8_t		hotremote_2[80];
	int8_t		hotcommand_2[20];
	int32_t		targetmask;
	uint8_t		extmode;
	uint8_t		extmode_2;
	uint8_t		wakeup_mac[6];
	uint8_t		extmode_ex[8];
} MODUSCOMMAND_EX;

// Adress:
// xxxx ffff	Netmask
// xxx1 xxxx	Netmask active Flag
// xxx6 xxxx	LED select
// x7f8 xxxx	Bus Select
// 38xx xxxx	Extended LED select
// 8xxx xxxx	Extended LED enable
// 4xxx xxxx	Bus Broadcast

// xxxxxxxx xxxxxxxx 11111111 11111111	Netmask	 (wie bisher genutzt)
// xxxxxxxx xxxxxxx1 xxxxxxxx xxxxxxxx	Netmask	aktiv (wie bisher genutzt)
// xxxxxxxx xxxxx11x xxxxxxxx xxxxxxxx	LED Auswahl (intern / extern)
// xxxxx111 11111xxx xxxxxxxx xxxxxxxx	Bus Auswahl (mehrere USB / LAN Module; max: 0-255 = 256 Stück)
// 1x111xxx xxxxxxxx xxxxxxxx xxxxxxxx	Auswahl mehrer externer LEDs - bis zu 8/32
// x1xxxxxx xxxxxxxx xxxxxxxx xxxxxxxx	Broadcast über alle USB / LAN Module


typedef struct {
	uint32_t	clientid;
	int16_t		statuslen;
	int16_t		statustype;
	int8_t		memsize[32];
	int8_t		flashsize[8];
	int8_t		remotes[8];
	int8_t		commands[8];
	int8_t		actions[8];
} IRDB_FLASHINFO;


typedef struct {
	uint8_t netcommand;
	uint8_t mode;
	uint16_t timeout;
	int32_t adress;
	int32_t protocol_version;
	uint8_t len;
	uint8_t align;
	uint8_t adr;
	uint8_t parameter;
	uint8_t data[256];
} SERCOMMAND;


typedef struct {
	uint8_t netcommand;
	uint8_t mode;
	uint16_t timeout;
	int32_t adress;
	int32_t protocol_version;
	uint16_t ccf_data[256];
} CCFCOMMAND;

typedef struct {
	uint8_t netcommand;
	uint8_t mode;
	uint16_t timeout;
	int32_t adress;
	int32_t protocol_version;
	uint16_t ccf_data[450];
} LONGCCFCOMMAND;


typedef struct {
	uint8_t netcommand;
	uint8_t mode;
	uint16_t timeout;
	int32_t adress;
	int32_t protocol_version;
	char ccf_data[1100];
	byte repeatmode;
} CCFSTRINGCOMMAND;

typedef struct {
	uint8_t netcommand;
	uint8_t mode;
	uint16_t timeout;
	int32_t adress;
	int32_t protocol_version;
	char ccf_data[980];
	byte repeatmode;
} CCFSTRINGCOMMAND_SHORT;


typedef struct {
	uint8_t netcommand;
	uint8_t mode;
	uint8_t lcdcommand;
	uint8_t timeout;
	int32_t adress;
	int32_t protocol_version;
	uint8_t wid;
	uint8_t hgt;
	int8_t framebuffer[200];
} LCDCOMMAND;


typedef struct {
	uint8_t netcommand;
	uint8_t mode;
	uint16_t timeout;
	int32_t adress;
	int32_t protocol_version;
	int32_t number;
	uint8_t setup;
	uint8_t type;
	uint8_t accelerator_timeout;
	uint8_t accelerator_repeat;
    uint16_t wait_timeout;
    uint8_t remote_num;
    uint8_t group_num;
	int8_t remote[80];
	int8_t command[20];
	int32_t source_mask;
	int32_t target_mask;
    uint8_t multi_num;
    uint8_t include_names;
	uint8_t io_input;
	uint8_t io_value;
} TRANSLATECOMMAND;


typedef struct {
    int32_t send_mask;
    uint8_t device_mode;
    uint8_t extended_mode;
    uint8_t extended_mode2;
    uint8_t align;
	uint16_t switch_mode;
    uint16_t align2;
	uint32_t features;
    uint16_t align3;
    int8_t version[10];
	int8_t remote[80];
	int8_t command[20];
} MODELINE;

typedef struct {
    int32_t send_mask;
    uint8_t device_mode;
    uint8_t extended_mode;
    uint8_t extended_mode2;
    uint8_t align;
	uint16_t switch_mode;
    uint16_t switch_mode2;
	uint32_t features;
    uint8_t extended_mode3;
    uint8_t extended_mode4;
    int8_t version[10];
	int8_t remote[80];
	int8_t command[20];
	int8_t remote2[80];
	int8_t command2[20];
} MODELINEN;

typedef struct {
    int32_t send_mask;					//  0
    uint8_t device_mode;				//  4
    uint8_t extended_mode;				//  5
    uint8_t extended_mode2;				//  6
    uint8_t align;						//  7
	uint16_t switch_mode;				//  8
    uint16_t switch_mode2;				// 10
	uint32_t features;					// 12
	uint32_t features2;					// 16
	uint32_t features3;					// 20
	uint32_t features4;					// 24
    uint8_t extended_mode_ex[8];		// 28
    int8_t version[10];					// 36
	int8_t remote[80];					// 46
	int8_t command[20];					//126
	int8_t remote2[80];					//146
	int8_t command2[20];				//226
	uint8_t align2[2];					//246
} MODELINEEX;							//248

typedef struct {
	uint32_t clientid;
	int16_t statuslen;
	int16_t statustype;
	int16_t adress;
    uint8_t align[2];
	int8_t data[32768];
} STATUSBUFFER;

typedef struct {
	uint32_t clientid;
	int16_t statuslen;
	int16_t statustype;
	int16_t adress;
    uint8_t align[2];
	int8_t data[256];
} DATABUFFER;

typedef struct {
	uint32_t clientid;
	int16_t statuslen;
	int16_t statustype;
	int32_t serno;
	int32_t functions;
} FUNCTIONBUFFER;

typedef struct {
	uint32_t clientid;
	int16_t statuslen;
	int16_t statustype;
	ANALOG_INPUTS inputs;
} ANALOGBUFFER;

typedef struct {
	uint32_t clientid;
	int16_t statuslen;
	int16_t statustype;
	ANALOG_INPUTS_EX inputs;
} ANALOGBUFFER_EX;

typedef struct {
	uint32_t clientid;
	int16_t statuslen;
	int16_t statustype;
	int32_t serno;
	int32_t functions;
	int8_t version[8];
} FUNCTIONBUFFEREX;

/*
typedef struct {
	uint32_t target_mask;
	uint32_t source_mask;
	int8_t name[80];
} REMOTELINE;
*/

typedef struct {
	uint32_t clientid;
	int16_t statuslen;
	int16_t statustype;
    int16_t offset;
    int16_t count_buffer;
	int16_t count_total;
	int16_t count_remaining;
	REMOTELINE remotes[40];
} REMOTEBUFFER;

typedef struct {
	uint32_t clientid;
	int16_t statuslen;
	int16_t statustype;
    int16_t offset;
    int16_t count_buffer;
	int16_t count_total;
	int16_t count_remaining;
	char WLAN_SSID[32][32];
	byte WLAN_type[32];
	byte WLAN_rssi[32];
} WLANBUFFER;

typedef struct {
	uint8_t netcommand;				//  0
	uint8_t mode;					//  1
	uint16_t timeout;				//  2
	int32_t adress;					//  4
	int32_t protocol_version;		//  8
	WIFI_MODE wlan;					// 12
} WLANCONFIGCOMMAND;


typedef struct {
	uint32_t clientid;				// 12
	int16_t statuslen;				// 16
	int16_t statustype;				// 18
	byte ip_adr[4];					// 20
	byte ip_netmask[4];				// 24
	byte ip_gateway[4];				// 28
	byte ntp_server[4];				// 32
	byte dhcp_flag;					// 33
	byte wpa_key[64];				// 34
	byte wlan_ssid[32];				// 98
	byte wlan_channel;				//130
	byte wlan_speed;				//131
	byte wlan_power;	// Sending Power 132
	byte wlan_mode;		//(AD-Hoc / AP) 133
	byte wlan_security;				// 134
	byte connected_mode;			// 135
	byte connected_rssi;			// 136
	byte timezone;					// 137
	byte mac_addr[6];				// 138
	byte connected_if;				// 144
} WLANSTATUSBUFFER;


typedef struct {
	uint8_t netcommand;				//  0
	uint8_t mode;					//  1
	uint16_t timeout;				//  2
	int32_t adress;					//  4
	int32_t protocol_version;		//  8
	SYS_PARAMETER	sysparm;		// 12
} SYSPARAMCOMMAND;

typedef struct {
	uint32_t clientid;
	int16_t statuslen;
	int16_t statustype;
	LAN_PARAMETER	lanparm;
} LANSTATUSBUFFER;

typedef struct {
	uint32_t clientid;
	int16_t statuslen;
	int16_t statustype;
	SYS_PARAMETER	sysparm;
} SYSPARAMBUFFER;


typedef struct {
	uint32_t clientid;
	int16_t statuslen;
	int16_t statustype;
    int16_t offset;
    int16_t count_buffer;
	int16_t count_total;
	int16_t count_remaining;
	BUSLINE bus[40];
} BUSBUFFER;

typedef struct {
	uint32_t clientid;
	int16_t statuslen;
	int16_t statustype;
    int16_t offset;
    int16_t count_buffer;
	int16_t count_total;
	int16_t count_remaining;
	int8_t commands[200][20];
} COMMANDBUFFER;

typedef struct {
	uint32_t clientid;
	int16_t statuslen;
	int16_t statustype;
    int16_t offset;
    int16_t count_buffer;
	int16_t count_total;
	int16_t count_remaining;
	TRANSLATECOMMAND trdata[30];
} TRANSLATEBUFFER;


typedef struct {
	uint8_t netcommand;					//   0
	uint8_t mode;						//   1
	uint16_t timeout;					//   2
	int32_t adress;						//   4
	int32_t protocol_version;			//   8
	int32_t number;						//  12
	uint8_t relais;						//  16
	uint8_t type;						//  17
	uint8_t action_type;				//  18
	uint8_t action_len;					//  19
	int32_t remote_num;					//  20
	int32_t command_num;				//  24
	uint32_t ip;						//  28
	uint16_t port;						//  32
	uint16_t align;						//  34
	int8_t remote[80];					//  36
	int8_t command[20];					// 116
	uint8_t action[256];				// 136
} IRDBCOMMAND;							// 392 = Total

typedef struct {
	uint8_t netcommand;					//   0
	uint8_t mode;						//   1
	uint16_t timeout;					//   2
	int32_t adress;						//   4
	int32_t protocol_version;			//   8
	int32_t number;						//  12
	uint8_t active;						//  16
	uint8_t type;						//  17
	word	port;						//  18
	uint8_t default_action[100];		//  20
	uint8_t err_status[20];				// 120
	uint8_t ok_status[20];				// 140
	uint8_t inputmode[4];				// 160
	uint8_t min[4];						// 164
	uint8_t max[4];						// 168
	uint8_t hyst[4];					// 172
	uint8_t minledsel[4];				// 176
	uint8_t maxledsel[4];				// 180
	int32_t minmask[4];					// 184
	int32_t maxmask[4];					// 200
	int8_t minremote[4][80];			// 216
	int8_t mincommand[4][50];			// 536
	int8_t maxremote[4][80];			// 736
	int8_t maxcommand[4][50];			//1056
	uint32_t ip;						//1256
	uint8_t rs232_config[4];			//1260
} IRDBHEADER;							//1264 = Total



typedef struct {
	uint32_t clientid;
	int16_t statuslen;
	int16_t statustype;
    int16_t offset;
    int16_t count_buffer;
	int16_t count_total;
	int16_t count_remaining;
	IRDBCOMMAND dbdata[12];
} IRDBBUFFER;

typedef struct {
	uint32_t clientid;
	int16_t statuslen;
	int16_t statustype;
    int16_t offset;
    int16_t count_buffer;
	int16_t count_total;
	int16_t count_remaining;
	IRDBHEADER header;
} IRDBHEADERBUFFER;

typedef struct {
	uint32_t clientid;
	int16_t statuslen;
	int16_t statustype;
	int16_t adress;
    uint8_t align[2];
    MODELINE stat[16];
} NETWORKMODE;

typedef struct {
	uint32_t clientid;
	int16_t statuslen;
	int16_t statustype;
	int16_t adress;
    uint8_t align;
	uint8_t count;
	uint8_t dev_adr[8];
    MODELINE stat[8][16];
} NETWORKMODEEX;

typedef struct {
	uint32_t clientid;
	int16_t statuslen;
	int16_t statustype;
	int16_t adress;
    uint8_t offset;
	uint8_t count;
	uint8_t dev_adr[8];
    MODELINEN stat[8][16];
} NETWORKMODEEXN;

typedef struct {
	uint32_t clientid;
	int16_t statuslen;
	int16_t statustype;
	int16_t adress;
    uint8_t offset;
	uint8_t count;
	uint8_t dev_adr[8];
    MODELINEEX stat[8][16];
} NETWORKMODEEX2;

typedef struct {
	uint32_t clientid;
	int16_t statuslen;
	int16_t statustype;
	int16_t adress;
	uint16_t netstatus;
	uint16_t statuslevel;
    uint8_t align[2];
	int8_t message[256];
} NETWORKSTATUS;

typedef struct {
	uint32_t clientid;
	int16_t statuslen;
	int16_t statustype;
	int16_t adress;
    uint8_t align[2];
	int8_t message[4096];
} NETWORKLOG;


typedef struct {
	uint32_t clientid;
	int16_t statuslen;
	int16_t statustype;
	int16_t adress;
	uint16_t netstatus;
	uint16_t statuslevel;
    uint8_t align;
	uint8_t	virtual_col;
	uint8_t numcol;
	uint8_t numrows;
	uint8_t clockflag;
} NETWORKLCDSTAT;

typedef struct {
	uint32_t clientid;
	int16_t statuslen;
	int16_t statustype;
	int16_t adress;
    uint8_t align[2];
	TIMINGDATA timing;
} NETWORKTIMING;

typedef struct {
	uint32_t clientid;
	int16_t statuslen;
	int16_t statustype;
	int16_t adress;
    uint16_t command_num;
	int8_t remote[80];
	int8_t command[20];
	int8_t data[200];
} NETWORKRECV;


typedef struct {
	uint32_t clientid;
	int16_t statuslen;
	int16_t statustype;
	int16_t adress;
	uint8_t learnok;
	uint8_t carrier;
	int8_t remote[80];
	int16_t num_timings;
	int16_t num_commands;
	int8_t received[CODE_LEN];
} NETWORKLEARNSTAT;


typedef struct {
	SOCKET fd;
	int32_t type;
	int32_t mode;
	uint32_t clientid;
	uint32_t callno;
	int8_t ip[20];
	WSAEVENT event;
	FILE *fp;
	char filename[84];
	int32_t timing;
	uint8_t resend_load;
	IRDATA ird;
	NETWORKLEARNSTAT learnstatus;
	int8_t restdata[sizeof (LCDCOMMAND)];
	int32_t restlen;
	int32_t restread;
	uint8_t msg_mode;
} NETWORKCLIENT;


#define MODE_ASCII		1
#define MODE_ASCII_TIME	5
#define MODE_NO_RECEIVE 10


#define TCP_PORT		21000
#define IRTRANS_PORT	21000
#define LIRC_PORT		8765
#define UDP_PORT		21000
#define WEB_PORT		80
#define ALTERNATE_WEB	8080
#define XAP_PORT		3639


#ifdef WIN32
#define CLIENT_COUNT	MAXIMUM_WAIT_OBJECTS - 3
#endif

#ifdef LINUX
#define CLIENT_COUNT	64
#endif



