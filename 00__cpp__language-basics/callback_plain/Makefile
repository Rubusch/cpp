# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE =  callbackplain.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

callbackplain.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: callbackplain.exe

clean:
	${RM} $(OBJECTS) callbackplain.exe *~ core


