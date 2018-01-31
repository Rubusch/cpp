# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = rc_cow_shareable.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

rc_cow_shareable.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: rc_cow_shareable.exe

clean:
	${RM} $(OBJECTS) rc_cow_shareable.exe *~ core


