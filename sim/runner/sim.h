#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#define ASSERT(cond, message)                                                   \
if(!cond) {                                                                     \
    printf("ASSERT: %s:%d in %s: %s", __FILE__, __LINE__, __FUNCTION__,         \
            message);                                                           \
    assert(cond);                                                               \
}

#define MASK(bit_start, bit_end) ((((bit_end - bit_start + 2) << 1) - 1) << bit_start)
#define CLEAR_BITS(x, bit_start, bit_end) (x & (~MASK(bit_start, bit_end)))

// by default:
// set the memory range to 1MB
// set PC counter to 0x0
#define RISCV_DEFAULT_MEMSIZE   (0x100000)
#define RISCV_DEFAULT_PC        (0x0)

// negative/zero/postive flags
typedef union {
    struct {
        uint8_t n : 1;
        uint8_t z : 1;
        uint8_t p : 1;
    } flags;

    uint8_t raw;
} status_flags_t;

typedef uint32_t *    program_counter_t;
typedef uint32_t      instruction_register_t;

typedef struct {
    status_flags_t          status;         // negative/zero/positive status
    program_counter_t       pc;             // program counter
    instruction_register_t  ir;             // instruction register
    uint32_t *              mem;            // pointer to block of simulatred RISC-V memory
    uint32_t                mem_size;       // size of memory
    uint32_t                regs[32];       // register file
} riscv_state_t;

uint32_t reg_read(riscv_state_t * state, uint32_t reg_idx);
void reg_write(riscv_state_t * state, uint32_t reg_idx, uint32_t val);
void incr_pc(riscv_state_t * state);