# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = bank.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

bank.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: bank.exe

clean: 
	${RM} $(OBJECTS) bank.exe *~ core


