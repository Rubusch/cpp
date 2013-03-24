# Makefile (simple)
#
# use -O, -O1, -O2 for optimization 


SOURCE = main.cpp rcobject.cpp rcwidget.cpp someclass.cpp widget.cpp 
HEADERS = rciptr.hpp rcobject.hpp rcptr.hpp rcwidget.hpp someclass.hpp widget.hpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

referencecounting.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: referencecounting.exe

clean: 
	${RM} $(OBJECTS) referencecounting.exe *~ core
