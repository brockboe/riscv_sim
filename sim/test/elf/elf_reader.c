#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <assert.h>
#include <string.h>
#include "global.h"
#include "elf_tools.h"

#define INSTR_WIDTH_BYTES (4)

void elf_print_text_data(char * elf_file)
{
    uint8_t * text_data = elf_get_section_fname(elf_file, ".text");

    for(int i = 0; i < (int)sizeof(text_data); i++)
    {
        printf("%02X ", ((uint8_t *)text_data)[i]);

        if( (i > 0) && !((i+1) % INSTR_WIDTH_BYTES) )
            { printf("\n"); }
    }

    free(text_data);
}

int main()
{
    elf_print_text_data("lui_auipc.elf");

    return 0;
}