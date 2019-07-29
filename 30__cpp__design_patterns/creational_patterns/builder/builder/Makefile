# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE =  builder.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

builder.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: builder.exe

clean:
	${RM} $(OBJECTS) builder.exe *~ core


