# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = listusage.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

listusage.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: listusage.exe

clean: 
	${RM} $(OBJECTS) listusage.exe *~ core


