BIN=window.out
CFLAGS=-lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl
INCLUDE=./include
SRC=src/*.c src/*.cpp

all:
	$(CC) $(CFLAGS) -I $(INCLUDE) $(SRC) -o $(BIN)

clean:
	$(RM) *.o
	$(RM) *.out

run: all
	./$(BIN)
