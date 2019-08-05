# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = inplacemerge.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

inplacemerge.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: inplacemerge.exe

clean:
	${RM} $(OBJECTS) inplacemerge.exe *~ core


