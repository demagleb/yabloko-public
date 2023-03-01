asm(".asciz \"kernel start\\n\"");

#include "console.h"
#include "cpu/isr.h"
#include "cpu/gdt.h"
#include "drivers/keyboard.h"
#include "drivers/vga.h"
#include "drivers/ata.h"
#include "drivers/misc.h"
#include "drivers/uart.h"
#include "fs/fs.h"
#include "lib/string.h"
#include "proc.h"


void _start() {
    load_gdt();
    uartinit();
    load_idt();
    sti();

    printk("YABLOKO\n");

    char x = 0;

    while (1) {
        for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
            vga_set_pixel(i, x);
            for (int i = 0; i < 100; i++) {
                asm("pause");
            }
        }
        ++x;
    }

    asm("hlt");
}
