BUILD_DIR:=./build/
BIN=LearnOpenGL

all:
	cmake -S . -B $(BUILD_DIR)
	$(MAKE) -C $(BUILD_DIR) -j$(nproc)

run: all
	$(BUILD_DIR)/$(BIN)

clean:
	$(RM) -r $(BUILD_DIR)
