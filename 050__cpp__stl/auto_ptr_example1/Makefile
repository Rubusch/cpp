# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = autoptr.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

autoptr.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: autoptr.exe

clean:
	${RM} $(OBJECTS) autoptr.exe *~ core


