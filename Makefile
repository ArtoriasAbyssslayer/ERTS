SHELL := /bin/bash

CC = gcc
RM = rm -f
CFLAGS = -O3 -lpthread -lm 
SanitzeFlags = -fsanitize=address 
BUILD_DIR = build
INCLUDE = ./inc 
BIN_SOURCE = 

all : $(EXEC)
BT_Collect : MAC-BT_Collect.c
	$(CC)-o $(BUILD_DIR)/BT_Collect_main -l$(INCLUDE)
MAC-BT_Collect.c &(CFLAGS)
./src/BT_Collect-santized : MAC-BT_Collect.c 
	$(CC)-o $(BUILD_DIR)/BT_Collect_main -l$(INCLUDE)
./src/MAC-BT_Collect.c &(CFLAGS) &(SanitzeFlags)
clean:
	$(RM) *.O $~ $(EXEC)
sanitizer_compile : 
default:
	all