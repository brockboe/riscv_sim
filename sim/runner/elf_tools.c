#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <assert.h>
#include <string.h>
#include "global.h"
#include "elf_tools.h"

uint8_t * elf_get_section( FILE * elf_file, char * sect_name )
{
    Elf64_Ehdr elf_hdr;
    Elf64_Shdr elf_sect_hdr;
    char * sect_names   = NULL;
    uint8_t * section_data = NULL;

    // retrieve the elf header
    fread( &elf_hdr, 1, sizeof(Elf64_Ehdr), elf_file );

    // retrieve the section header
    fseek(
        elf_file,
        elf_hdr.e_shoff + elf_hdr.e_shstrndx * sizeof(elf_sect_hdr),
        SEEK_SET
    );
    fread( &elf_sect_hdr, 1, sizeof(elf_sect_hdr), elf_file );

    // read the section string data
    sect_names = malloc(elf_sect_hdr.sh_size);
    fseek(elf_file, elf_sect_hdr.sh_offset, SEEK_SET);
    fread(sect_names, 1, elf_sect_hdr.sh_size, elf_file);

    // iterate through sections and find the text section
    for( int idx = 0; idx < elf_hdr.e_shnum; idx++ )
    {
        fseek(elf_file, elf_hdr.e_shoff + idx * sizeof(elf_sect_hdr), SEEK_SET);
        fread(&elf_sect_hdr, 1, sizeof(elf_sect_hdr), elf_file);

        if( elf_sect_hdr.sh_name
            && !strcmp(sect_names + elf_sect_hdr.sh_name, sect_name) )
        {
            // we've found the text section. Copy the text data into a
            // buffer so we can return it
            section_data = (uint8_t *)malloc(sizeof(elf_sect_hdr.sh_size));
            fseek(elf_file, elf_sect_hdr.sh_offset, SEEK_SET);
            fread(section_data, 1, sizeof(section_data), elf_file);
            break;
        }
    }

    free(sect_names);
    return section_data;
}

uint8_t * elf_get_section_fname( char * fname, char * sect_name)
{
    FILE * elf_file = NULL;
    uint8_t * section_data = NULL;

    elf_file = fopen(fname, "r");
    assert(elf_file != NULL);

    section_data = elf_get_section(elf_file, sect_name);
    assert(section_data != NULL);
    return section_data;
}