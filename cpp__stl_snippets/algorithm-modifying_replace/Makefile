# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = replace.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

replace.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: replace.exe

clean:
	${RM} $(OBJECTS) replace.exe *~ core


