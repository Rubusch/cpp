SOURCE	= uniqueptr.cpp
TARGET = $(SOURCE:.cpp=.elf)
OBJECTS	= $(SOURCE:.cpp=.o)
.PREFIXES = .cpp .o
CC = g++
CPPFLAGS = -g -Wall -Werror -pedantic
RM = rm -f

.c.o:
	$(CC) $(CPPFLAGS) -c $<

$(TARGET): $(OBJECTS)
	$(CC) $(CPPFLAGS) -o $@ $(OBJECTS)

all: $(TARGET)

clean:
	-$(RM) $(TARGET) $(OBJECTS) *~

.PHONY: clean
