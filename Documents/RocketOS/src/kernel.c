#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

// TODO: Follow calling global constructors article on osdevwiki.org

/* Hardware text mode color constants. */
enum vga_color {
	VGA_COLOUR_BLACK = 0,
	VGA_COLOUR_BLUE = 1,
	VGA_COLOUR_GREEN = 2,
	VGA_COLOUR_CYAN = 3,
	VGA_COLOUR_RED = 4,
	VGA_COLOUR_MAGENTA = 5,
	VGA_COLOUR_BROWN = 6,
	VGA_COLOUR_LIGHT_GREY = 7,
	VGA_COLOUR_DARK_GREY = 8,
	VGA_COLOUR_LIGHT_BLUE = 9,
	VGA_COLOUR_LIGHT_GREEN = 10,
	VGA_COLOUR_LIGHT_CYAN = 11,
	VGA_COLOUR_LIGHT_RED = 12,
	VGA_COLOUR_LIGHT_MAGENTA = 13,
	VGA_COLOUR_LIGHT_BROWN = 14,
	VGA_COLOUR_WHITE = 15,
};

static inline uint8_t vga_entry_colour(enum vga_color fg, enum vga_color bg) 
{
    // Generates color value from the colours passed in. The colour value can later be used.
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
    // Returns a binary value that can be put into the terminal_buffer
	return (uint16_t) uc | (uint16_t) color << 8;
}

size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_colour;
uint16_t* terminal_buffer;

void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_colour = vga_entry_colour(VGA_COLOUR_WHITE, VGA_COLOUR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_colour);
		}
	}
}

void terminal_setcolour(uint8_t colour) 
{
	terminal_colour = colour;
}

void terminal_putentryat(char c, uint8_t colour, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, colour);
}

void terminal_putchar(char c, uint8_t colour) 
{
    if (c == '\n') {
        terminal_row++;
        terminal_column = 0;
        return;
    }
	terminal_putentryat(c, colour, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
        terminal_row++;
    }
    if (terminal_row + 1 == VGA_HEIGHT) {
        for (size_t i = VGA_WIDTH; i <= VGA_WIDTH * VGA_HEIGHT; i++) {
            terminal_buffer[i - VGA_WIDTH] = terminal_buffer[i];
        }
        terminal_row = VGA_HEIGHT - 2;
        /*terminal_row = 0;
        terminal_column = 0;*/
    }
}

void terminal_write(const char* data, size_t size, uint8_t colour) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i], colour);
}

void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data), terminal_colour);
}

void terminal_writestring_colour(const char* data, uint8_t colour)
{
    terminal_write(data, strlen(data), colour);
}

void kernel_main(void) 
{
	/* Initialize terminal interface */
	terminal_initialize();
    
    terminal_writestring("Hello World.");
}
