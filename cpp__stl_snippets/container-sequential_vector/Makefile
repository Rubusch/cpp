# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = vectorusage.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

vectorusage.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: vectorusage.exe

clean: 
	${RM} $(OBJECTS) vectorusage.exe *~ core


