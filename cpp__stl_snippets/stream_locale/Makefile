# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = locale.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

locale.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: locale.exe

clean:
	${RM} $(OBJECTS) locale.exe *~ core


