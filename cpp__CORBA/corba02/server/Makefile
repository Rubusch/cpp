# Makefile CORBA Server

CC		= g++
CPPFLAGS	= -g -c
LDFLAGS		= -g
OMNI_INCLUDES	= -I/usr/include/omniORB4
OMNIIDL		= /usr/bin/omniidl
INCLUDES	= $(OMNI_INCLUDES)
LIBS		= -lomniORB4 -lomnithread -lomniDynamic4
OBJECTS		= DataSK.o CServiceA.o server.o
RM		= rm -f

all server.exe: $(OBJECTS)
	$(CC) $(LDFLAGS) -o server.exe $(OBJECTS) $(LIBS)

# TODO check rename - Data.o -> DataSK.o
DataSK.o: DataSK.cc Data.hh
	$(CC) $(CPPFLAGS) $(INCLUDES) DataSK.cc

server.o: server.cpp Data.hh
	$(CC) $(CPPFLAGS) $(INCLUDES) server.cpp

CServiceA.o: CServiceA.cpp CServiceA.h Data.hh
	$(CC) $(CPPFLAGS) $(INCLUDES) CServiceA.cpp

DataSK.cc: ../idl/Data.idl
	$(OMNIIDL) -bcxx ../idl/Data.idl

clean:
	$(RM) $(OBJECTS) server.exe *.o *~ Data.hh DataSK.cc core 

