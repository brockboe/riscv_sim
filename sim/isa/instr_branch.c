#include "isa_types.h"
#include "sim.h"

int instr_lui(riscv_state_t * state) {
    uint32_t reg_idx = state->ir.U_type.rd;
    uint32_t imm     = state->ir.U_type.imm31_12;

    reg_write(state, reg_idx, imm << 12);

    incr_pc(state);
    return 0;
}

int instr_auipc(riscv_state_t * state) {
    uint32_t reg_idx = state->ir.U_type.rd;
    uint32_t imm     = state->ir.U_type.imm31_12;
    uint32_t pc      = (uint32_t)(state->pc);

    reg_write(state, reg_idx, (imm << 12) + pc);

    incr_pc(state);
    return 0;
}

int isntr_jal(riscv_state_t * state) {
    uint32_t reg_idx = state->ir.U_type.rd;
    uint32_t imm     = state->ir.U_type.imm31_12;
    uint32_t pc      = (uint32_t)(state->pc);

    reg_write(state, reg_idx, pc + 4);

    state->pc = pc + (imm << 1);
    return 0;
}

int instr_jalr(riscv_state_t * state) {
    
}

// TODO - impliment later

/*
int instr_beq

int instr_bne

int instr_blt

int instr_bge

int instr_bltu

int instr_bgeu
*/