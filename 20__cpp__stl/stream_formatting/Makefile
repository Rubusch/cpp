# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = streamformatting.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

streamformatting.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: streamformatting.exe

clean:
	${RM} $(OBJECTS) streamformatting.exe *~ core


