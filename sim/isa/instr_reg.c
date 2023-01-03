#include "sim.h"
#include "isa_types.h"

int instr_add(riscv_state_t * state)
{
    uint32_t rd  = state->ir.R_type.rd;
    uint32_t rs1 = state->ir.R_type.rs1;
    uint32_t rs2 = state->ir.R_type.rs2;

    int32_t result = (int32_t)(state->regs[rs1]) + (int32_t)(state->regs[rs2]);
    reg_write(state, rd, result);

    incr_pc(state);
    return 0;
}

int instr_slt(riscv_state_t * state)
{
    uint32_t rd  = state->ir.R_type.rd;
    uint32_t rs1 = state->ir.R_type.rs1;
    uint32_t rs2 = state->ir.R_type.rs2;
    uint32_t result;

    if ((int32_t)(state->regs[rs1]) < (int32_t)(state->regs[rs2]))
        { result = 1; }
    else
        { result = 0; }

    reg_write(state, rd, result);
    incr_pc(state);
    return 0;
}

int instr_sltu(riscv_state_t * state)
{
    uint32_t rd  = state->ir.R_type.rd;
    uint32_t rs1 = state->ir.R_type.rs1;
    uint32_t rs2 = state->ir.R_type.rs2;
    uint32_t result;

    if ((uint32_t)(state->regs[rs1]) < (uint32_t)(state->regs[rs2]))
        { result = 1; }
    else
        { result = 0; }

    reg_write(state, rd, result);
    incr_pc(state);
    return 0;
}

int instr_and(riscv_state_t * state)
{
    uint32_t rd  = state->ir.R_type.rd;
    uint32_t rs1 = state->ir.R_type.rs1;
    uint32_t rs2 = state->ir.R_type.rs2;
    uint32_t result = state->regs[rs1] & state->regs[rs2];

    reg_write(state, rd, result);
    incr_pc(state);
    return 0;
}

int instr_or(riscv_state_t * state)
{
    uint32_t rd  = state->ir.R_type.rd;
    uint32_t rs1 = state->ir.R_type.rs1;
    uint32_t rs2 = state->ir.R_type.rs2;
    uint32_t result = state->regs[rs1] | state->regs[rs2];

    reg_write(state, rd, result);
    incr_pc(state);
    return 0;
}

int instr_xor(riscv_state_t * state)
{
    uint32_t rd  = state->ir.R_type.rd;
    uint32_t rs1 = state->ir.R_type.rs1;
    uint32_t rs2 = state->ir.R_type.rs2;
    uint32_t result = state->regs[rs1] ^ state->regs[rs2];

    reg_write(state, rd, result);
    incr_pc(state);
    return 0;
}

int instr_sll(riscv_state_t * state)
{
    uint32_t rd  = state->ir.R_type.rd;
    uint32_t rs1 = state->ir.R_type.rs1;
    uint32_t rs2 = state->ir.R_type.rs2;
    uint32_t result = state->regs[rs1] << state->regs[rs2];

    reg_write(state, rd, result);
    incr_pc(state);
    return 0;
}

int instr_srl(riscv_state_t * state)
{
    uint32_t rd  = state->ir.R_type.rd;
    uint32_t rs1 = state->ir.R_type.rs1;
    uint32_t rs2 = state->ir.R_type.rs2;
    uint32_t result = (uint32_t)(state->regs[rs1]) >> (state->regs[rs2]);

    reg_write(state, rd, result);
    incr_pc(state);
    return 0;
}

int instr_sub(riscv_state_t * state)
{
    uint32_t rd  = state->ir.R_type.rd;
    uint32_t rs1 = state->ir.R_type.rs1;
    uint32_t rs2 = state->ir.R_type.rs2;
    int32_t result = (int32_t)(state->regs[rs1]) - (int32_t)(state->regs[rs2]);

    reg_write(state, rd, result);
    incr_pc(state);
    return 0;
}

int instr_sra(riscv_state_t * state)
{
    uint32_t rd  = state->ir.R_type.rd;
    uint32_t rs1 = state->ir.R_type.rs1;
    uint32_t rs2 = state->ir.R_type.rs2;
    int32_t result = (int32_t)(state->regs[rs1]) >> state->regs[rs2];

    reg_write(state, rd, result);
    incr_pc(state);
    return 0;
}