#!/usr/bin/env bash

export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig/
gcc $(pkg-config --cflags glfw3) -o bin/debug/main src/*.c $(pkg-config --static --libs glfw3) -lpthread -Llib -lglad -I include
