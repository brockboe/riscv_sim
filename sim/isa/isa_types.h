#include <stdlib.h>
#include <stdint.h>

// Taken from RISC-V ISA
// https://github.com/riscv/riscv-isa-manual/releases/download/Ratified-IMAFDQC/riscv-spec-20191213.pdf

// RISC-V has 4 instruction formats

enum {
    OPC_LUI     = 0b0110111,
    OPC_AUIPC   = 0b0010111,
    OPC_JAL     = 0b1101111,
    OPC_JALR    = 0b1100111,
    OPC_BEQ     = 0b1100011,
    OPC_BNE     = 0b1100011,
    OPC_BLT     = 0b1100011,
    OPC_BGE     = 0b1100011,
    OPC_BLTU    = 0b1100011,
    OPC_BGEU    = 0b1100011,
    OPC_LB      = 0b0000011,
    OPC_LH      = 0b0000011,
    OPC_LW      = 0b0000011,
    OPC_LBU     = 0b0000011,
    OPC_LHU     = 0b0000011,
    OPC_SB      = 0b0100011,
    OPC_SH      = 0b0100011,
    OPC_SW      = 0b0100011,
    OPC_ADDI    = 0b0010011,
    OPC_SLTI    = 0b0010011,
    OPC_SLTIU   = 0b0010011,
    OPC_XORI    = 0b0010011,
    OPC_ORI     = 0b0010011,
    OPC_ANDI    = 0b0010011,
    OPC_SLLI    = 0b0010011,
    OPC_SRLI    = 0b0010011,
    OPC_SRAI    = 0b0010011,
    OPC_ADD     = 0b0110011,
    OPC_SUB     = 0b0110011,
    OPC_SLL     = 0b0110011,
    OPC_SLT     = 0b0110011,
    OPC_SLTU    = 0b0110011,
    OPC_XOR     = 0b0110011,
    OPC_SRL     = 0b0110011,
    OPC_SRA     = 0b0110011,
    OPC_OR      = 0b0110011,
    OPC_AND     = 0b0110011,
    OPC_NOP     = 0b0010011,
};

int instr_nop(riscv_state_t * state);
int instr_lui(riscv_state_t * state);
int instr_jal(riscv_state_t * state);