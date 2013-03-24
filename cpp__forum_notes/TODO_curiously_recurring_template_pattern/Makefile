# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE =  crtp.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

crtp.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: crtp.exe

clean: 
	${RM} $(OBJECTS) crtp.exe *~ core


