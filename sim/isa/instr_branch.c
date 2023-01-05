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

// "The target address is obtained by adding the sign-extended
// 12-bit I-immediate to the register rs1, then setting the least
// significant bit of the result to 0"
int instr_jalr(riscv_state_t * state) {
    uint32_t rd  = state->ir.I_type.rd;
    uint32_t rs1 = state->ir.I_type.rs1;
    int64_t  imm = (int64_t)(state->ir.I_type.imm11_0);
    int64_t pc       = (int64_t)(state->pc);

    int64_t jump_addr = (int64_t)(state->regs[rs1]) + imm;
    // TODO: Get rid of magic numbers -- this is lazy
    jump_addr &= (0xFFFFFFFF) << 1;

    state->pc = (uint32_t *)jump_addr;
    reg_write(state, rd,  pc + 4);

    return 0;
}

// TODO - impliment branch instructions


int64_t untangle_B_type_imm(instr_format_t ir) {
    int64_t ret = 0;
    ret  = ir.B_type.imm_4_1  << 1;
    ret |= ir.B_type.imm_10_5 << 5;
    ret |= ir.B_type.imm_11   << 11;

    // TODO - get rid of magic numbers
    if(ir.B_type.imm_12)
        { ret |= (0xFFFFFFFF) << 12; }

    return ret;
}

int instr_beq(riscv_state_t * state) {
    uint32_t rs1 = state->ir.B_type.rs1;
    uint32_t rs2 = state->ir.B_type.rs2;
    int64_t  imm = untangle_B_type_imm(state->ir);
    int64_t  pc  = (int64_t)(state->pc);

    if(state->regs[rs1] == state->regs[rs2])
        { state->pc = (uint32_t *)(pc + imm); }
    else
        { incr_pc(state); }

    return 0;
}

int instr_bne(riscv_state_t * state) {
    uint32_t rs1 = state->ir.B_type.rs1;
    uint32_t rs2 = state->ir.B_type.rs2;
    int64_t  imm = untangle_B_type_imm(state->ir);
    int64_t  pc  = (int64_t)(state->pc);

    if(state->regs[rs1] != state->regs[rs2])
        { state->pc = (uint32_t *)(pc + imm); }
    else
        { incr_pc(state); }

    return 0;
}

// 12-bit B-immediate encodes a signed offset
// in multiples of 2 bytes
// BLT takes the branch if rs1 < rs2

int instr_blt(riscv_state_t * state) {
    uint32_t rs1 = state->ir.B_type.rs1;
    uint32_t rs2 = state->ir.B_type.rs2;
    int64_t  imm = untangle_B_type_imm(state->ir);
    int64_t  pc  = (int64_t)(state->pc);

    if((int32_t)(state->regs[rs1]) < (int32_t)(state->regs[rs2]))
        { state->pc = (uint32_t *)(pc + imm); }
    else
        { incr_pc(state); }

    return 0;
}

int instr_bge(riscv_state_t * state) {
    uint32_t rs1 = state->ir.B_type.rs1;
    uint32_t rs2 = state->ir.B_type.rs2;
    int64_t  imm = untangle_B_type_imm(state->ir);
    int64_t  pc  = (int64_t)(state->pc);

    if((int32_t)(state->regs[rs1]) >= (int32_t)(state->regs[rs2]))
        { state->pc = (uint32_t *)(pc + imm); }
    else
        { incr_pc(state); }

    return 0;
}

int instr_bltu(riscv_state_t * state) {
    uint32_t rs1 = state->ir.B_type.rs1;
    uint32_t rs2 = state->ir.B_type.rs2;
    int64_t  imm = untangle_B_type_imm(state->ir);
    int64_t  pc  = (int64_t)(state->pc);

    if(state->regs[rs1] < state->regs[rs2])
        { state->pc = (uint32_t *)(pc + imm); }
    else
        { incr_pc(state); }

    return 0;
}

int instr_bgeu(riscv_state_t * state) {
    uint32_t rs1 = state->ir.B_type.rs1;
    uint32_t rs2 = state->ir.B_type.rs2;
    int64_t  imm = untangle_B_type_imm(state->ir);
    int64_t  pc  = (int64_t)(state->pc);

    if(state->regs[rs1] >= state->regs[rs2])
        { state->pc = (uint32_t *)(pc + imm); }
    else
        { incr_pc(state); }

    return 0;
}