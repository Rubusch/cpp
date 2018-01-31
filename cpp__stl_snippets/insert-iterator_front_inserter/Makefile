# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = frontinserter.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

frontinserter.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: frontinserter.exe

clean:
	${RM} $(OBJECTS) frontinserter.exe *~ core


