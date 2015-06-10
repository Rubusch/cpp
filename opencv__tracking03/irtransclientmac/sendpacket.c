#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main (argc,argv)
	int argc;
	char *argv[];
{
	int i,j;
	if (argc!=6) return 1;
	char address[] = "10.20.6.136";
	char command[256];
	int ret=0;
	sprintf(command, "./irclient64 %s rc5 volup",address);
	ret = system(command);
	fprintf(stdout,"*** start packet (%s) return code is %d*** \n", command,ret);
	for (i=1;i<6;i++)
	{
		char last='\0';
		for (j=0;j<strlen(argv[i]);j++)
		{
			if (argv[i][j]==last)
			{
				sprintf(command, "./irclient64 %s rc5 chdown",address);
				last = '\0';
			}
			else if (argv[i][j]=='-')
			{
				sprintf(command, "./irclient64 %s rc5 chdown",address);
			}
			else
			{
				sprintf(command, "./irclient64 %s rc5 %c",address,argv[i][j]);
				last = argv[i][j];
			}
			ret = system(command);
			fprintf(stdout,"*** digit (%s) return code is %d*** \n",command,ret); 
		}
		if (i==5)
			sprintf(command, "./irclient64 %s rc5 voldown",address);
		else
			sprintf(command, "./irclient64 %s rc5 chup",address);
		ret = system(command);
		fprintf(stdout,"*** seperator/end (%s) return code is %d*** \n",command,ret); 
	}
	return 0;
}
