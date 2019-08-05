# Makefile CORBA client

CC		= g++
CPPFLAGS	= -g -c
LDFLAGS		= -g
OMNI_INCLUDES	= -I/usr/include/omniORB4
OMNIIDL		= /usr/bin/omniidl
INCLUDES	= $(OMNI_INCLUDES)
LIBS		= -lomniORB4 -lomnithread -lomniDynamic4
OBJECTS		=  DataSK.o client.o CRequestServiceA.o
RM		= rm -f

all client.exe: $(OBJECTS)
	$(CC) $(LDFLAGS) -o client.exe $(OBJECTS) $(LIBS)

DataSK.o: DataSK.cc Data.hh
#	$(CC) $(CPPFLAGS) DataSK.cc
	$(CC) $(CPPFLAGS) $(INCLUDES) DataSK.cc

client.o: client.cpp CRequestServiceA.h
#	$(CC) $(CPPFLAGS) client.cpp
	$(CC) $(CPPFLAGS) $(INCLUDES) client.cpp

CRequestServiceA.o: CRequestServiceA.cpp CRequestServiceA.h Data.hh
#	$(CC) $(CPPFlags) CRequestServiceA.cpp
	$(CC) $(CPPFlags) $(INCLUDES) CRequestServiceA.cpp

DataSK.cc: ../idl/Data.idl
	$(OMNIIDL) -bcxx ../idl/Data.idl

clean:
	$(RM) $(OBJECTS) client.exe *.o *~ Data.hh DataSK.cc core


