# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = lazyfetching.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

lazyfetching.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: lazyfetching.exe

clean: 
	${RM} $(OBJECTS) lazyfetching.exe *~ core


