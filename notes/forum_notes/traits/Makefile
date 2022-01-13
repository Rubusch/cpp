# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE =  traits.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

traits.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: traits.exe

clean:
	${RM} $(OBJECTS) traits.exe *~ core


