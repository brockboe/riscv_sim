#include "sim.h"

uint32_t reg_read(riscv_state_t * state, uint32_t reg_idx) {
    if(reg_idx == 0) {
        return 0;
    } else {
        return state->regs[reg_idx];
    }
}

void reg_write(riscv_state_t * state, uint32_t reg_idx, uint32_t val) {
    if(reg_idx != 0) {
        state->regs[reg_idx] = val;
    }
}

void incr_pc(riscv_state_t * state) {
    state->pc += 1;
}