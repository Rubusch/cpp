# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = findfirstof.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

findfirstof.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: findfirstof.exe

clean:
	${RM} $(OBJECTS) findfirstof.exe *~ core


