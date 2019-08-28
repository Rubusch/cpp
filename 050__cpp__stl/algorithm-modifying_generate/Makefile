# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = generate.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

generate.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: generate.exe

clean:
	${RM} $(OBJECTS) generate.exe *~ core


