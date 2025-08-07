# WiiMediaPlayer Makefile
# Wii Homebrew Media Player Development

# Project name
PROJECT_NAME = WiiMediaPlayer

# Source files
SOURCES = source/main.c source/decoder.c source/playlist.c source/movie_features.c

# Include directories
INCLUDES = -I$(DEVKITPRO)/libogc/include -I$(DEVKITPRO)/libogc/include/ogc

# Library directories
LIBDIRS = -L$(DEVKITPRO)/libogc/lib/wii

# Libraries to link
LIBS = -lwiiuse -lbte -logc -lm -lfat -lm

# Compiler flags
CFLAGS = -g -O2 -Wall $(MACHDEP) $(INCLUDES)
CXXFLAGS = $(CFLAGS)
LDFLAGS = $(MACHDEP) -Wl,-Map,$(notdir $@).map $(LIBDIRS) $(LIBS)

# Tools
CC = powerpc-eabi-gcc
CXX = powerpc-eabi-g++
OBJCOPY = powerpc-eabi-objcopy
STRIP = powerpc-eabi-strip

# Output files
ELF = $(PROJECT_NAME).elf
DOL = $(PROJECT_NAME).dol

# Default target
all: $(DOL)

# Build the DOL file
$(DOL): $(ELF)
	$(OBJCOPY) -O binary $< $@

# Build the ELF file
$(ELF): $(SOURCES:.c=.o)
	$(CC) -o $@ $^ $(LDFLAGS)

# Compile C files
%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

# Clean build files
clean:
	rm -f $(ELF) $(DOL) $(SOURCES:.c=.o) $(ELF).map

# Install to SD card (adjust path as needed)
install: $(DOL)
	cp $(DOL) /path/to/sd/card/apps/$(PROJECT_NAME)/boot.dol
	cp meta.xml /path/to/sd/card/apps/$(PROJECT_NAME)/

# Debug build
debug: CFLAGS += -DDEBUG -g3
debug: $(DOL)

# Release build
release: CFLAGS += -O3 -DNDEBUG
release: $(DOL)

.PHONY: all clean install debug release
