BUILD_DIR:=./build/
BIN=LearnOpenGL
COMPILER:=ninja

all:
	cmake -S . -B $(BUILD_DIR) -G Ninja
	$(COMPILER) -C $(BUILD_DIR)

run: all
	$(BUILD_DIR)/$(BIN)

release: all
	strip $(BUILD_DIR)/$(BIN)

clean:
	$(RM) -r $(BUILD_DIR)
