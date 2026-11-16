CC = gcc
CFLAGS = -Wall -O2 -I src/engine -I lib
LIBS = -lGL -lglfw -ldl -lm -lcglm
OUT = game
SRC = $(wildcard lib/*.c src/*.c src/engine/*.c src/engine/*/*.c)
OBJ = $(SRC:.c=.o)

.PHONY: build run clean deps

# Install system dependencies (Debian/Ubuntu)
deps:
	sudo apt-get update
	sudo apt-get install -y build-essential pkg-config libglfw3-dev libgl1-mesa-dev libcglm-dev

build: $(OUT)

$(OUT): $(OBJ)
	$(CC) $(OBJ) -o $(OUT) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: build
	./$(OUT)

clean:
	rm -f $(OBJ) $(OUT)
