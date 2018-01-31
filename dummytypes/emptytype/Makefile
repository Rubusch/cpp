# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = emptytype.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

emptytype.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: emptytype.exe

clean:
	${RM} $(OBJECTS) emptytype.exe *~ core


