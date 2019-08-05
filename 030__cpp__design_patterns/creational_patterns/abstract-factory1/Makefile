# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE =  abstractfactory.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

abstractfactory.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: abstractfactory.exe

clean:
	${RM} $(OBJECTS) abstractfactory.exe *~ core


