#include "fs.h"
#include "../drivers/ata.h"
#include "../lib/string.h"
#include "../drivers/ata.h"
#include "../console.h"


int stat(const char* name, struct stat *buf) {
    panic("stat not implemented");
}



int read_file(const char* name, void* buf, uint32_t bufsize) {
    struct dir d;
    read_sectors_ATA_PIO((unsigned) &d, 1, 1);
    int i = 0;
    for (; i < ents_in_dir; ++i) {
        if (!strncmp(d.entries[i].name, name, 20)) {
            break;
        }
    }
    if (i == ents_in_dir) {
        return -1;
    }
    int offset = d.entries[i].offset_sectors + 1;
    int size = (d.entries[i].size_bytes);
    size = (size < bufsize ? size : bufsize);
    char x[sector_size];
    int got = 0;
    while (size) {
        read_sectors_ATA_PIO((unsigned) x, offset, 1);
        for (int i = 0; i < sector_size && size; ++i) {
            *(char*)buf = x[i];
            ++buf;
            --size;
            ++got;
        }
        ++offset;
    }
    return got;
}
