#include <stdlib.h>
#include <stdint.h>

// Taken from RISC-V ISA
// https://github.com/riscv/riscv-isa-manual/releases/download/Ratified-IMAFDQC/riscv-spec-20191213.pdf

// RISC-V has 4 instruction formats
typedef union {
    struct {
        uint32_t opcode     : 7;
        uint32_t rd         : 5;
        uint32_t funct3     : 3;
        uint32_t rs1        : 5;
        uint32_t rs2        : 5;
        uint32_t funct7     : 7;
    } R_type;

    struct {
        uint32_t opcode     : 7;
        uint32_t rd         : 5;
        uint32_t funct3     : 3;
        uint32_t rs1        : 5;
        uint32_t imm11_0    : 12;
    } I_type;

    struct {
        uint32_t opcode     : 7;
        uint32_t imm4_0     : 5;
        uint32_t funct3     : 3;
        uint32_t rs1        : 5;
        uint32_t rs2        : 5;
        uint32_t imm11_5    : 7;
    } S_type;

    struct {
        uint32_t opcode     : 7;
        uint32_t rd         : 5;
        uint32_t imm31_12   : 20;
    } U_type;
} instr_format_t;

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
};