# Makefile (simple)
#
TARGET = typelist.exe
SOURCE = typelist.cpp
HEADERS = conversion.hpp
OBJECTS = $(SOURCE:.cpp=.o)

.PREFIXES = .cpp .o
CC = g++
CPPFLAGS = -g -Wall -Werror -pedantic -std=c++17
RM = rm -f

.cpp.o:
	$(CC) $(CPPFLAGS) -c $<

$(TARGET): $(OBJECTS)
	$(CC) $(CPPFLAGS) -o $@ $(OBJECTS) -lm

all: $(TARGET)

clean:
	$(RM) $(OBJECTS) $(TARGET) *~ core


