SOURCE = newdelete.cpp
TARGET = $(SOURCE:.cpp=.exe)
OBJECTS = $(SOURCE:.cpp=.o)
.PREFIXES = .c .o
CC = g++
CPPFLAGS += -g -Wall -funsigned-char
RM = rm -f

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CPPFLAGS) -o $@ $(OBJECTS) -lm

.c.o:
	$(CC) -c $(CPPFLAGS) $<

clean:
	$(RM) $(TARGET) $(OBJECTS) *~ out.txt

.PHONY: all clean
