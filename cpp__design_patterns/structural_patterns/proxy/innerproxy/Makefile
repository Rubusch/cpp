# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = innerproxy.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

innerproxy.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: innerproxy.exe

clean:
	${RM} $(OBJECTS) innerproxy.exe *~ core


