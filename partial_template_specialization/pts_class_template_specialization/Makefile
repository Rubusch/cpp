# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = classtemplatespecialization.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

classtemplatespecialization.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: classtemplatespecialization.exe

clean: 
	${RM} $(OBJECTS) classtemplatespecialization.exe *~ core


