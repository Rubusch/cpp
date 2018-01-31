# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = noduplicates.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

noduplicates.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: noduplicates.exe

clean:
	${RM} $(OBJECTS) noduplicates.exe *~ core


