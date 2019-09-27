# Makefile (simple)
#
# use -O, -O1, -O2 for optimization

SOURCE = traits.cpp
TARGET = $(SOURCE:.cpp=.exe)
OBJECTS = $(SOURCE:.cpp=.o)
.PREFIXES = .cpp .o
CC = g++
CPPFLAGS = -g -Wall -Werror -pedantic -std=c++98
RM = rm -f

.cpp.o:
	$(CC) $(CPPFLAGS) -c $<

$(TARGET): $(OBJECTS)
	$(CC) $(CPPFLAGS) -o $@ $(OBJECTS) -lm

all: $(TARGET)

clean:
	$(RM) $(OBJECTS) $(TARGET) *~ core


