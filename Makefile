CC = xtensa-lx106-elf-gcc

CFLAGS = -I./src -mlongcalls

LDLIBS = -nostdlib -lgcc

LDFLAGS = -Teagle.app.v6.ld

BUILD_DIR = ./build

all: $(BUILD_DIR)/esp-bare-0x00000.bin

$(BUILD_DIR)/esp-bare-0x00000.bin: $(BUILD_DIR)/esp-bare build
	esptool.py elf2image $<

$(BUILD_DIR)/esp-bare: $(BUILD_DIR)/esp-bare.o build
	$(CC) $(LDFLAGS) $< $(LDLIBS) -o $@

$(BUILD_DIR)/esp-bare.o: src/esp-bare.c | build
	$(CC) $(CFLAGS) -c $< -o $@

build:
	mkdir -p build

flash: $(BUILD_DIR)/esp-bare-0x00000.bin
	esptool.py --port $(ESPPORT) write_flash 0x00000 $< 

clean:
	rm -rf build

.PHONY: all flash clean
