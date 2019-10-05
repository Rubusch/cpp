# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE =  callbackversion.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

callbackversion.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: callbackversion.exe

clean:
	${RM} $(OBJECTS) callbackversion.exe *~ core


