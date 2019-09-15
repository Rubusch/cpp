# Makefile for C++ Class
TARGET = async.exe
SOURCE	= async.cpp
OBJECTS	= $(SOURCE:.cpp=.o)
.PREFIXES = .cpp .o
CC = g++
CPPFLAGS = -g -Wall -Werror
RM = rm -f

.c.o:
	$(CC) $(CPPFLAGS) -c $<

$(TARGET): $(OBJECTS)
	$(CC) $(CPPFLAGS) -o $@ $(OBJECTS) -lpthread -lm

all: $(TARGET)

clean:
	-$(RM) $(TARGET) $(OBJECTS) core *~

.PHONY: clean
