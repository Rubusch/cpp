# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = mapusage.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

mapusage.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: mapusage.exe

clean: 
	${RM} $(OBJECTS) mapusage.exe *~ core


