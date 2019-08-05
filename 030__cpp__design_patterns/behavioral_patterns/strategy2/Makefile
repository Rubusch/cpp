# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE =  strategy.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

strategy.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: strategy.exe

clean:
	${RM} $(OBJECTS) strategy.exe *~ core


