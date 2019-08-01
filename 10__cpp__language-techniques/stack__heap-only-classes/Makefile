# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = stackheaponlyclasses.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

stackheaponlyclasses.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: stackheaponlyclasses.exe

clean:
	${RM} $(OBJECTS) stackheaponlyclasses.exe *~ core


