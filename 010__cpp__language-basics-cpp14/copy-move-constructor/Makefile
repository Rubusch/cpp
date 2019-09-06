# Makefile (simple)
#
# use -O, -O1, -O2 for optimization
TARGET = moveconstructor.exe
SOURCE = moveconstructor.cpp
OBJECTS = ${SOURCE:.cpp=.o}
.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall
RM = rm -f

.cpp.o:
	${CC} -c ${CFLAGS} $<

$(TARGET): ${OBJECTS}
	${CC} -o $@ ${OBJECTS} -lm

all: $(TARGET)

clean:
	${RM} $(OBJECTS) $(TARGET) *~ core
