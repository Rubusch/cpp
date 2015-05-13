# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = opnewdelete.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

opnewdelete.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: opnewdelete.exe

clean: 
	${RM} $(OBJECTS) opnewdelete.exe *~ core


