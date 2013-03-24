# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = rotate.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

rotate.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: rotate.exe

clean: 
	${RM} $(OBJECTS) rotate.exe *~ core


