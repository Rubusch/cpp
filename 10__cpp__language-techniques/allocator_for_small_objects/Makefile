# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE =  allocatorforsmallobjects.cpp smallobjectallocator.cpp fixedallocator.cpp
HEADERS = smallobjectallocator.hpp fixedallocator.hpp smallobject.hpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

allocatorforsmallobjects.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: allocatorforsmallobjects.exe

clean:
	${RM} $(OBJECTS) allocatorforsmallobjects.exe *~ core


