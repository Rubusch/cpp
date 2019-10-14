#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(argc, argv) int argc;
char *argv[];
{
  int i, j;
  if (argc != 6) {
    fprintf(stderr,
            "Exacty 5 parameters are required. Received %d parameters.\n",
            argc - 1);
    fprintf(stderr, "    %s <id> <pos_x> <pos_y> <target_x> <target_y>",
            argv[0]);
    return 1;
  }
  char address[] = "192.168.1.117";
  char command[8096];
  char number[3] = " 0";
  int ret = 0;
  sprintf(command, "../irtransclientmac/irclient64 %s -sequence rc5 volup",
          address);
  // ret = system(command);
  // fprintf(stdout,"*** start packet (%s) return code is %d*** \n",
  // command,ret);
  for (i = 1; i < 6; i++) {
    char last = '\0';
    for (j = 0; j < strlen(argv[i]); j++) {
      if (argv[i][j] == last) {
        strcat(command, " chdown");
        last = '\0';
      } else if (argv[i][j] == '-') {
        strcat(command, " chdown");
      } else {
        number[1] = argv[i][j];
        strcat(command, number);
        last = argv[i][j];
      }
      // ret = system(command);
      // fprintf(stdout,"*** digit (%s) return code is %d*** \n",command,ret);
    }
    if (i == 5)
      strcat(command, " voldown");
    else
      strcat(command, " chup");
    // ret = system(command);
    // fprintf(stdout,"*** seperator/end (%s) return code is %d***
    // \n",command,ret);
  }
#ifdef VERBOSE
  fprintf(stdout, "Sending '%s'.\n", command);
#endif
  ret = system(command);
  if (ret) {
#ifdef VERBOSE
    fprintf(stderr, "*** system returns with %d *** \n", ret);
#else
    fprintf(stderr, "*** system returns with %d while sending '%s' *** \n", ret,
            command);
#endif
  }
  return ret;
}
