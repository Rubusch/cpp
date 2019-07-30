# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = exception4.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall -std=c++98
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

exception4.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: exception4.exe

clean:
	${RM} $(OBJECTS) exception4.exe *~ core


