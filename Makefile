BUILD_DIR:=./build/
BIN=LearnOpenGL
COMPILER:=ninja
ASSETS:=$(wildcard textures/*) $(wildcard shaders/*)

all:
	cmake -S . -B $(BUILD_DIR) -G Ninja
	$(COMPILER) -C $(BUILD_DIR)

run: all
	$(BUILD_DIR)/$(BIN)

windows:
	cmake -DCMAKE_TOOLCHAIN_FILE=toolchain.cmake -S . -B $(BUILD_DIR) -G Ninja
	$(COMPILER) -C $(BUILD_DIR)

release: all assets
	strip $(BUILD_DIR)/$(BIN)

clean:
	$(RM) -r $(BUILD_DIR)

assets:
	@$(RM) src/embedded_assets.h
	@{ \
		for asset in $(ASSETS); do \
			xxd -i "$$asset" >> src/embedded_assets.h; \
		done \
	}
