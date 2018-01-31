# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE =  policydesign.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

policydesign.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: policydesign.exe

clean:
	${RM} $(OBJECTS) policydesign.exe *~ core


