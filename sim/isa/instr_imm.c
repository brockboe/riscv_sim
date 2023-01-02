#include "sim.h"
#include "isa_types.h"

// See page 18 or RISC-V spec
// shift instructions only use the lower 5 bits
// of the immediate field
#define SHIFT_IMM_MASK (0x001F)

int instr_addi(riscv_state_t * state)
{
    uint32_t rd  = state->ir.I_type.rd;
    uint32_t rs1 = state->ir.I_type.rs1;
    int32_t  imm = (int32_t)(state->ir.I_type.imm11_0);

    reg_write(state, rd, imm + (int32_t)(state->regs[rs1]));

    incr_pc(state);
    return 0;
}

int instr_slti(riscv_state_t * state)
{
    uint32_t rd  = state->ir.I_type.rd;
    uint32_t rs1 = state->ir.I_type.rs1;
    int32_t  imm = (int32_t)(state->ir.I_type.imm11_0);

    if ((int32_t)(state->regs[rs1]) < imm)
        { reg_write(state, rd, 1); }
    else
        { reg_write(state, rd, 0); }

    incr_pc(state);
    return 0;
}

int instr_sltiu(riscv_state_t * state)
{
    uint32_t rd  = state->ir.I_type.rd;
    uint32_t rs1 = state->ir.I_type.rs1;
    uint32_t imm = state->ir.I_type.imm11_0;

    if (state->regs[rs1] < imm)
        { reg_write(state, rd, 1); }
    else
        { reg_write(state, rd, 0); }

    incr_pc(state);
    return 0;
}

int instr_andi(riscv_state_t * state)
{
    uint32_t rd  = state->ir.I_type.rd;
    uint32_t rs1 = state->ir.I_type.rs1;
    int32_t  imm = (int32_t)(state->ir.I_type.imm11_0);

    reg_write(state, rd, imm & (int32_t)(state->regs[rs1]));

    incr_pc(state);
    return 0;
}

int instr_ori(riscv_state_t * state)
{
    uint32_t rd  = state->ir.I_type.rd;
    uint32_t rs1 = state->ir.I_type.rs1;
    int32_t  imm = (int32_t)(state->ir.I_type.imm11_0);

    reg_write(state, rd, imm | (int32_t)(state->regs[rs1]));

    incr_pc(state);
    return 0;
}

int instr_xori(riscv_state_t * state)
{
    uint32_t rd  = state->ir.I_type.rd;
    uint32_t rs1 = state->ir.I_type.rs1;
    int32_t  imm = (int32_t)(state->ir.I_type.imm11_0);

    reg_write(state, rd, imm ^ (int32_t)(state->regs[rs1]));

    incr_pc(state);
    return 0;
}

int instr_slli(riscv_state_t * state)
{
    uint32_t rd  = state->ir.I_type.rd;
    uint32_t rs1 = state->ir.I_type.rs1;
    uint32_t imm = state->ir.I_type.imm11_0 & SHIFT_IMM_MASK;

    reg_write(state, rd, state->regs[rs1] << imm);

    incr_pc(state);
    return 0;
}

int instr_srli(riscv_state_t * state)
{
    uint32_t rd  = state->ir.I_type.rd;
    uint32_t rs1 = state->ir.I_type.rs1;
    uint32_t imm = state->ir.I_type.imm11_0 & SHIFT_IMM_MASK;

    reg_write(state, rd, (uint32_t)(state->regs[rs1]) >> imm);

    incr_pc(state);
    return 0;
}

int instr_srai(riscv_state_t * state)
{
    uint32_t rd  = state->ir.I_type.rd;
    uint32_t rs1 = state->ir.I_type.rs1;
    uint32_t imm = state->ir.I_type.imm11_0 & SHIFT_IMM_MASK;

    reg_write(state, rd, (int32_t)(state->regs[rs1]) >> imm);

    incr_pc(state);
    return 0;
}