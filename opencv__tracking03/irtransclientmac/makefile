SHELL = /bin/sh

CC = gcc

CFLAGS = 
CPPFLAGS = -DLINUX -DSILENT 
LDFLAGS =
LIBS =
ODIR = x86
ODIR64 = x64

_OBJS = client.o
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))
OBJS64 = $(patsubst %,$(ODIR64)/%,$(_OBJS))

all: irclient irclient64 sendpacket sendpackets

irclient: $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -m32 -o irclient $(LDFLAGS)

irclient64: $(OBJS64)
	$(CC) $(CFLAGS) -DX64 $(OBJS64) -m64 -o irclient64 $(LDFLAGS)

sendpacket: sendpacket.c makefile
	$(CC) sendpacket.c -o sendpacket

sendpackets: sendpackets.c makefile
#	$(CC) -DVERBOSE sendpackets.c -o sendpackets
	$(CC) sendpackets.c -o sendpackets

clean:
	-rm $(OBJS)
	-rm $(OBJS64)


$(ODIR)/%.o: %.c flash.h errcode.h network.h remote.h functioncodes.h makefile
	$(CC) $(CPPFLAGS) $(CFLAGS) -m32 -c $< -o $@


$(ODIR64)/%.o: %.c flash.h errcode.h network.h remote.h functioncodes.h makefile
	$(CC) $(CPPFLAGS) $(CFLAGS) -DX64 -m64 -c $< -o $@

				
