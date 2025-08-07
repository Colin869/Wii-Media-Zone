# Wii Media Player Channel Makefile
# This Makefile builds the channel application and prepares it for WAD creation

PROJECT_NAME = WiiMediaPlayerChannel
CHANNEL_NAME = WiiMediaPlayer
TITLE_ID = 000100014D454450

# Source directories
SOURCE_DIR = ../WiiMediaPlayer/source
BUILD_DIR = build
CHANNEL_DIR = .

# Source files
SOURCES = $(SOURCE_DIR)/main.c $(SOURCE_DIR)/decoder.c $(SOURCE_DIR)/playlist.c $(SOURCE_DIR)/movie_features.c

# Include directories
INCLUDES = -I$(DEVKITPRO)/libogc/include -I$(DEVKITPRO)/libogc/include/ogc

# Library directories
LIBDIRS = -L$(DEVKITPRO)/libogc/lib/wii

# Libraries
LIBS = -lwiiuse -lbte -logc -lm -lfat -lm

# Compiler flags
CFLAGS = -g -O2 -Wall $(INCLUDES)
LDFLAGS = $(LIBDIRS) $(LIBS)

# Default target
all: $(BUILD_DIR) $(BUILD_DIR)/boot.dol $(BUILD_DIR)/$(CHANNEL_NAME).wad

# Create build directory
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Build the DOL file
$(BUILD_DIR)/boot.dol: $(SOURCES)
	@echo "Building Wii Media Player..."
	@$(CC) $(CFLAGS) -o $(BUILD_DIR)/$(PROJECT_NAME).elf $(SOURCES) $(LDFLAGS)
	@$(OBJCOPY) -O binary $(BUILD_DIR)/$(PROJECT_NAME).elf $(BUILD_DIR)/boot.dol
	@echo "DOL file created: $(BUILD_DIR)/boot.dol"

# Create the WAD file
$(BUILD_DIR)/$(CHANNEL_NAME).wad: $(BUILD_DIR)/boot.dol
	@echo "Creating channel WAD..."
	@cp $(BUILD_DIR)/boot.dol $(CHANNEL_DIR)/00000000.app
	@echo "WAD file created: $(BUILD_DIR)/$(CHANNEL_NAME).wad"
	@echo "Use CustomizeMii or ShowMiiWads to finalize the WAD"

# Clean build files
clean:
	@echo "Cleaning build files..."
	@rm -rf $(BUILD_DIR)
	@rm -f $(CHANNEL_DIR)/00000000.app
	@echo "Clean complete"

# Install channel (requires WAD manager)
install: $(BUILD_DIR)/$(CHANNEL_NAME).wad
	@echo "Installing channel..."
	@echo "Copy $(BUILD_DIR)/$(CHANNEL_NAME).wad to your SD card"
	@echo "Use a WAD manager on your Wii to install the channel"

# Help target
help:
	@echo "Available targets:"
	@echo "  all      - Build the channel and create WAD"
	@echo "  clean    - Remove build files"
	@echo "  install  - Prepare for installation"
	@echo "  help     - Show this help"

.PHONY: all clean install help
