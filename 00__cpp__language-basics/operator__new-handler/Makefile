# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = operatornewhandler.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

operatornewhandler.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: operatornewhandler.exe

clean:
	${RM} $(OBJECTS) operatornewhandler.exe *~ core


