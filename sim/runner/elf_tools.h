#include <elf.h>

typedef struct
{
    uint64_t size;
    uint8_t * data;
} section_data_t;

section_data_t elf_get_section( FILE * elf_file, char * sect_name );
section_data_t elf_get_section_fname( char * fname, char * sect_name);