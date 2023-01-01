#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "sim.h"
#include "global.h"
#include "elf_tools.h"
#include "isa_types.h"

riscv_state_t state;

int riscv_init( void ) {
    state.status.raw = 0;
    state.pc = 0;
    state.ir.raw = 0;
    state.mem = (uint32_t *) malloc(sizeof(uint8_t) * RISCV_DEFAULT_MEMSIZE);
    state.mem_size = RISCV_DEFAULT_MEMSIZE;

    ASSERT(state.mem != 0x0, "could not allocate memory for RISCV sim!!!\n");
    return 0;
}

int riscv_teardown() {
    free(state.mem);
    return 0;
}

void sim_dispatch_instruction(uint32_t opcode)
{
    switch(opcode)
    {
    case OPC_LUI:
        instr_lui(&state);
        break;
    case OPC_NOP:
        instr_nop(&state);
        break;
    }
}

int main( int argc, char ** argv )
{
    char * elf_fname = NULL;
    FILE * elf_file  = NULL;
    uint8_t * text_data = NULL;

    riscv_init();

    if( argc != 2 )
    {
        printf("usage: riscv_sim <elf file>\n");
        exit(1);
    }

    elf_fname = argv[1];
    elf_file  = fopen(elf_fname, "r");
    assert(elf_file != NULL);

    text_data = elf_get_section(elf_file, ".text");

    for(uint32_t i = 0; i < sizeof(text_data)/sizeof(instr_format_t); i++)
    {
        state.ir.raw = ((uint32_t *)text_data)[i];
        sim_dispatch_instruction(state.ir.R_type.opcode);
    }

    riscv_teardown();
    return 0;
}