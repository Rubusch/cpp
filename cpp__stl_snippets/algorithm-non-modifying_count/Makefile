# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = count.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

count.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: count.exe

clean:
	${RM} $(OBJECTS) count.exe *~ core


