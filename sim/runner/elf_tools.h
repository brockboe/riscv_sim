#include <elf.h>

uint8_t * elf_get_section( FILE * elf_file, char * sect_name );
uint8_t * elf_get_section_fname( char * fname, char * sect_name);