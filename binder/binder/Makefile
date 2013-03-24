# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = functorbinder.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

functorbinder.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: functorbinder.exe

clean: 
	${RM} $(OBJECTS) functorbinder.exe *~ core


