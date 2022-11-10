TARGET = uniqueptr.elf
SOURCE	= uniqueptr.cpp
OBJECTS	= $(SOURCE:.cpp=.o)
.PREFIXES	= .cpp .o
CC		= g++
CPPFLAGS	= -g -Wall -Werror
RM		= rm -f

.c.o:
	$(CC) $(CPPFLAGS) -c $<

$(TARGET): $(OBJECTS)
	$(CC) $(CPPFLAGS) -o $@ $(OBJECTS)

all: $(TARGET)

clean:
	-$(RM) $(TARGET) $(OBJECTS) *~

.PHONY: clean
