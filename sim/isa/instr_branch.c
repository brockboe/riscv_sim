#include "sim.h"
#include "isa_types.h"

int instr_nop(riscv_state_t * state)  {
    incr_pc(state);
    return 0;
}

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
    uint64_t pc      = (uint64_t)(state->pc);

    reg_write(state, reg_idx, (imm << 12) + pc);

    incr_pc(state);
    return 0;
}

static inline int64_t untangle_jtype(instr_format_t ir)
{
    int64_t ret = 0;
    ret |= ir.J_type.imm_10_1  << 1;
    ret |= ir.J_type.imm_11    << 11;
    ret |= ir.J_type.imm_19_12 << 12;
    ret |= ir.J_type.imm_20    << 20;

    if( ir.J_type.imm_20 )
        { ret |= 0xFFF << 20; }

    return ret;
}

int instr_jal(riscv_state_t * state) {
    uint32_t reg_idx = state->ir.U_type.rd;
    int64_t imm      = untangle_jtype(state->ir);
    int64_t pc       = (int64_t)(state->pc);

    reg_write(state, reg_idx, pc + 4);

    state->pc = (program_counter_t)(pc + (imm << 1)) + 4;
    return 0;
}

int instr_jalr() {
    return 0;
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