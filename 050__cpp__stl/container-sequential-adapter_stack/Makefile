# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = stackusage.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

stackusage.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: stackusage.exe

clean:
	${RM} $(OBJECTS) stackusage.exe *~ core


