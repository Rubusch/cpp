# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = queueusage.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

queueusage.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: queueusage.exe

clean:
	${RM} $(OBJECTS) queueusage.exe *~ core


