# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE =  command.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

command.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: command.exe

clean:
	${RM} $(OBJECTS) command.exe *~ core


