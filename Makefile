CC      := gcc
CFLAGS  := -std=c11 -Wall -Wextra -Iinclude -MMD -MP

# Use pkg-config so include/lib paths aren't hardcoded.
PKGS    := libmosquitto libcjson
CFLAGS  += $(shell pkg-config --cflags $(PKGS))
LIBS    := $(shell pkg-config --libs $(PKGS))

TARGET  := mqtt_broker
SRCS    := $(wildcard src/*.c)
OBJS    := $(patsubst src/%.c,build/%.o,$(SRCS))
DEPS    := $(OBJS:.o=.d)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LIBS)

build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

build:
	mkdir -p $@

clean:
	rm -rf build $(TARGET)

-include $(DEPS)

.PHONY: all clean
