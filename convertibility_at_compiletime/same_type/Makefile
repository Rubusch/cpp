# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = sametype.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

sametype.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: sametype.exe

clean: 
	${RM} $(OBJECTS) sametype.exe *~ core


