# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = passbywhat.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

passbywhat.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: passbywhat.exe

clean:
	${RM} $(OBJECTS) passbywhat.exe *~ core


