# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = proxy.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

proxy.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: proxy.exe

clean:
	${RM} $(OBJECTS) proxy.exe *~ core


