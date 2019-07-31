# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = protocolclass.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall -std=c++98
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

protocolclass.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: protocolclass.exe

clean:
	${RM} $(OBJECTS) protocolclass.exe *~ core


