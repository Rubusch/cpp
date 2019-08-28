# Makefile (simple)
#
# use -O, -O1, -O2 for optimization


SOURCE = bind1st.cpp
OBJECTS = ${SOURCE:.cpp=.o}

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

bind1st.exe: ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: bind1st.exe

clean:
	${RM} $(OBJECTS) bind1st.exe *~ core


