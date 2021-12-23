#!/usr/bin/env bash

export PATH="$HOME/opt/cross/bin:$PATH"

nasm -felf32 src/boot.asm -o src/boot.o
i686-elf-gcc -c src/kernel.c -o src/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -T src/linker.ld -o src/myos.bin -ffreestanding -O2 -nostdlib src/boot.o src/kernel.o -lgcc
if grub-file --is-x86-multiboot src/myos.bin; then
  echo multiboot confirmed
else
  echo the file is not multiboot
fi
cp src/myos.bin src/isodir/boot/myos.bin
cp src/grub.cfg src/isodir/boot/grub/grub.cfg
grub-mkrescue -o src/myos.iso src/isodir

