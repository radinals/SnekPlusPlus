CC = g++
LDFLAGS = -lncurses
CFLAGS = -std=c++14 -Wall -pedantic

SOURCE = Main.cpp Game.cpp Snake.cpp Map.cpp Food.cpp Curse.cpp
HEADER = Utils.h

TARGET = Snek

all: build

debug: CFLAGS += -ggdb
debug: build

build : $(SOURCE) $(HEADER)
	$(CC) $(CFLAGS) -o $(TARGET) $^ $(LDFLAGS)

.PHONY: clean

clean:
	@echo "deleting ${TARGET}"
	@rm -f $(TARGET)
