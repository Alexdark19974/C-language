.PHONY : all clean script
CC := gcc
CFLAGS := -Wall -Wextra --pedantic -O2 -std=c99
DIR := $(CURDIR)
BIN_DIR := $(DIR)/bin
SRC := *.c
SRC_DIR := $(DIR)/src
OBJ := 1.1.o
OBJ_DIR:= $(DIR)/obj
TARGET := 1.1

script:
	$(shell ./script.sh)

%.o: $(SRC_DIR)/$(SRC)
	if [ ! -d $(SRC_DIR) ]; then \
		echo "Directory $(SRC_DIR) does not exist!"; \
		echo "Creating one"; \
		mkdir -p $(SRC_DIR); \
		mv $(SRC) $(SRC_DIR); \
	fi
	if [ ! -d $(OBJ_DIR) ]; then \
		echo "Directory $(OBJ_DIR) does not exist!"; \
		echo "Creating one"; \
		mkdir -p $(OBJ_DIR); \
	fi
	if [ ! -f $(OBJ_DIR)/$(OBJ) ]; then \
		$(CC) -o $@ -c $< $(CFLAGS); \
	fi
all: $(OBJ_DIR) $(OBJ_DIR)/$(OBJ)
	if [ ! -d $(BIN_DIR) ]; then \
		echo "Directory $(BIN) does not exist!"; \
		echo "Creating one"; \
		mkdir -p $(BIN_DIR); \
	fi
	if [ ! -f $(BIN_DIR)/$(TARGET) ]; then \
		$(CC) $(OBJ_DIR)/$(OBJ) -o $(TARGET) $(CFLAGS); \
		mv $(TARGET) $(BIN_DIR); \
	fi
clean:
	rm -rf $(DIR)/$(TARGET) $(BIN_DIR)/$(TARGET) $(OBJ_DIR)/$(OBJ)
