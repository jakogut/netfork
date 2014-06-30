CC = clang

CFLAGS = -Wall -pipe -Iinclude/ -std=gnu11
OFLAGS = 
LFLAGS = $(CFLAGS) -Llib/
PEDANTIC_FLAGS = -Werror -pedantic -pedantic-errors

NF_SOURCES = $(wildcard src/*.c)
NF_OBJECTS = $(NF_SOURCES:.c=.o)

BIN_DIR = bin
INC_DIR = include

DEBUG = no
PEDANTIC = no
OPTIMIZATION = -O2

ifeq ($(DEBUG), yes)
	CFLAGS += -g
endif

ifeq ($(PEDANTIC), yes)
	CFLAGS += $(PEDANTIC_FLAGS)
endif

CFLAGS += $(OPTIMIZATION)

all: netfork_client netfork_server

netfork_client: $(NF_OBJECTS)
	$(CC) $(LFLAGS) $(NF_OBJECTS) client/netfork_client.c -o $(BIN_DIR)/netfork_client


netfork_server: $(NF_OBJECTS)
	$(CC) $(LFLAGS) $(NF_OBJECTS) server/netfork_server.c -o $(BIN_DIR)/netfork_server

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BIN_DIR)/netfork* src/*.o client/*.o server/*.o

rebuild: clean all

.PHONY : clean
.SILENT : clean
.NOTPARALLEL : clean
