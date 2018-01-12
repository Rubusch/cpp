# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE =  singleton.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

singleton.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: singleton.exe

clean:
	${RM} $(OBJECTS) singleton.exe *~ core


