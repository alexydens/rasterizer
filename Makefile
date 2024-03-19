BUILD_DIR=build
SRC_DIR=src

CFLAGS = -std=c99 -Wall -Wextra -pedantic
LDFLAGS = -ffast-math -O3 -lm -lSDL2

$(BUILD_DIR)/main: $(SRC_DIR)/main.c
	gcc $(SRC_DIR)/*.c -o $@ $(CFLAGS) $(LDFLAGS)

.PHONY: test clean

clean:
	rm -rf $(BUILD_DIR)/*

test:	$(BUILD_DIR)/main
	$(BUILD_DIR)/main
