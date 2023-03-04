#include "fs/fs.h"
asm(".asciz \"kernel start\\n\"");

#include "console.h"
#include "cpu/isr.h"
#include "cpu/gdt.h"
#include "drivers/vga.h"
#include "drivers/uart.h"
#include "drivers/pit.h"
#include "fs/fs.h"
#include "lib/mem.h"

#include "gif.h"

void _start() {
    load_gdt();
    uartinit();
    load_idt();
    init_pit();
    sti(); 
    printk("YABLOKO\n");
    

    int frame = 0;
    int x_shift = (SCREEN_WIDTH - width) / 2;
    int y_shift = (SCREEN_HEIGHT - height) / 2;
    char* data = kmalloc(width * height * n_frames);

    int res = read_file("gif.bin", data, width * height * n_frames);

    if (res != width * height * n_frames) {
        panic("can't read");
    }

    while (1) {
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                unsigned offset = get_vga_pixel_offset(x_shift + i, y_shift + j);

                int pixel_pos = frame * width * height + i * height + j;
                char pixel = data[pixel_pos];

                vga_set_pixel(offset, pixel);
            }
        }
        frame = (frame + 1) % 4;
        msleep(1000);
    }

    asm("hlt");
}