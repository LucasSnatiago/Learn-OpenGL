BIN=LearnOpenGL.out
SRC=src/*.c src/*.cpp src/window/*.c src/input/*.c
CFLAGS=-lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -O2
INCLUDE=./include

all:
	$(CXX) $(CFLAGS) -I $(INCLUDE) $(SRC) -o $(BIN)

release: all
	strip $(BIN)

clean:
	$(RM) *.out
	$(RM) *.o

run: all
	./$(BIN)
