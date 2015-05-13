# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = prevpermutation.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

prevpermutation.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: prevpermutation.exe

clean: 
	${RM} $(OBJECTS) prevpermutation.exe *~ core


