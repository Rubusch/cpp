# Makefile (simple)
#
# use -O, -O1, -O2 for optimization

TARGET = exception3.exe
SOURCE = exception3.cpp
OBJECTS = $(SOURCE:.cpp=.o)

.PREFIXES = .cpp .o
CC = g++
CFLAGS = -g -Wall -Werror -pedantic
RM = rm -f

.cpp.o:
	$(CC) $(CFLAGS) -c $<

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) -lm

all: $(TARGET)

clean:
	$(RM) $(OBJECTS) $(TARGET) *~ core


