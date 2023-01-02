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

void sim_dispatch_instruction(instr_format_t ir)
{
    switch(ir.R_type.opcode)
    {
    case OPC_LUI:
        instr_lui(&state);
        break;
    case OPC_JAL:
        instr_jal(&state);
        break;

    // immediate instructions
    case OPC_ADDI:
        switch(ir.I_type.funct3)
        {
            case FUNCT3_ADDI:
                instr_addi(&state);
                break;
            case FUNCT3_SLTI:
                instr_slti(&state);
                break;
            case FUNCT3_SLTIU:
                instr_sltiu(&state);
                break;
            case FUNCT3_XORI:
                instr_xori(&state);
                break;
            case FUNCT3_ORI:
                instr_ori(&state);
                break;
            case FUNCT3_ANDI:
                instr_andi(&state);
                break;
            case FUNCT3_SLLI:
                instr_slli(&state);
                break;
            case FUNCT3_SR:
                switch(ir.I_type.imm11_0 >> 5)
                {
                    case IMM_FUNCT_SRLI:
                        instr_srli(&state);
                        break;
                    case IMM_FUNCT_SRAI:
                        instr_srai(&state);
                        break;
                }
                break;
        }
        break;
    }
}

int main( int argc, char ** argv )
{
    char * elf_fname = NULL;
    FILE * elf_file  = NULL;
    section_data_t text_data;

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
    assert(text_data.data != NULL);

    state.pc  = (uint32_t *)(text_data.data);

    //for(uint32_t i = 0; i < sizeof(text_data)/sizeof(uint32_t); i++)
    while(1)
    {
        state.ir.raw = *(state.pc);
        sim_dispatch_instruction(state.ir);
    }

    riscv_teardown();
    return 0;
}