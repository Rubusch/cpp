# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = setusage.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

setusage.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: setusage.exe

clean:
	${RM} $(OBJECTS) setusage.exe *~ core


