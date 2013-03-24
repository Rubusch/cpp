# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE =  optionalpolicy.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

optionalpolicy.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: optionalpolicy.exe

clean: 
	${RM} $(OBJECTS) optionalpolicy.exe *~ core


