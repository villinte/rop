SRC_DIR = src
CC=g++
CFLAGS= -Wall -g -std=c++11 -lSDL2 -lSDL2_image
LDFLAGS=-lncurses
SOURCES =$(wildcard $(SRC_DIR)/*.cpp)
TARGET = rop
OBJS = $(SOURCES:.cpp=.o)
.PHONY:$(TARGET)
$(TARGET): 
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) $(LDFLAGS) 

clean:
	$(RM) $(OBJS)
