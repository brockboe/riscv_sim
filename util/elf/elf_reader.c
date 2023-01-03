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
    section_data_t text_data = elf_get_section_fname(elf_file, ".text");

    printf("printing %ld bytes of .text section data of %s...\n", text_data.size, elf_file);
    for(int i = 0; i < (int)text_data.size; i++)
    {
        printf("%02X ", text_data.data[i]);

        if( (i > 0) && !((i+1) % INSTR_WIDTH_BYTES) )
            { printf("\n"); }
    }

    free(text_data.data);
}

int main(int argc, char ** argv)
{
    if(argc != 2)
    {
        printf("usage: elf_reader <fname>\n");
        exit(1);
    }
 
    elf_print_text_data(argv[1]);

    return 0;
}