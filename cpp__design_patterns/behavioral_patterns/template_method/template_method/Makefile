# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE =  templatemethod.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

templatemethod.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: templatemethod.exe

clean: 
	${RM} $(OBJECTS) templatemethod.exe *~ core


