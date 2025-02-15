#pragma once

extern char* const video_memory;
extern char* const pixel_memory;

enum {
    ROWS = 25,
    COLS = 80,

    VGA_CTRL_REGISTER = 0x3d4,
    VGA_DATA_REGISTER = 0x3d5,
    VGA_OFFSET_LOW = 0x0f,
    VGA_OFFSET_HIGH = 0x0e,

    SCREEN_WIDTH = 320,
    SCREEN_HEIGHT = 200
};

enum colors16 {
    black = 0,
    blue,
    green,
    cyan,
    red,
    magenta,
    brown,
    light_gray,
    dark_gray,
    light_blue,
    light_green,
    light_cyan,
    light_red,
    light_magenta,
    yellow,
    white,
};

void vga_clear_screen();

void vga_set_char(unsigned offset, char c);
void vga_print_string(const char* s);
void vga_print_string_noscroll(const char* s);

void vga_set_pixel(unsigned offset, char pixel);
unsigned get_vga_pixel_offset(int x, int y);