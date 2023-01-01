#include "sim.h"
#include "isa_types.h"

riscv_state_t state;


int riscv_init() {
    state.status.raw = 0;
    state.pc = 0;
    state.ir = 0;
    state.mem = (uint32_t *) malloc(sizeof(uint8_t) * RISCV_DEFAULT_MEMSIZE);
    state.mem_size = RISCV_DEFAULT_MEMSIZE;

    ASSERT(state.mem != 0x0, "could not allocate memory for RISCV sim!!!\n");
    return 0;
}

int riscv_teardown() {
    free(state.mem);
    return 0;
}

int main() {
    riscv_init();

    

    riscv_teardown();
    return 0;
}