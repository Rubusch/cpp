# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE =  state.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

state.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: state.exe

clean: 
	${RM} $(OBJECTS) state.exe *~ core


