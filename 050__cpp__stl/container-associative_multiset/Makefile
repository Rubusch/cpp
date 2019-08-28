# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = multisetusage.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

multisetusage.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: multisetusage.exe

clean:
	${RM} $(OBJECTS) multisetusage.exe *~ core


