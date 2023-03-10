#include <stdlib.h>
#include <stdint.h>

// Taken from RISC-V ISA
// https://github.com/riscv/riscv-isa-manual/releases/download/Ratified-IMAFDQC/riscv-spec-20191213.pdf

// individual opcodes
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

// immediate codes
enum {
    FUNCT3_ADDI  = 0b000,
    FUNCT3_SLTI  = 0b010,
    FUNCT3_SLTIU = 0b011,
    FUNCT3_XORI  = 0b100,
    FUNCT3_ORI   = 0b110,
    FUNCT3_ANDI  = 0b111,
    FUNCT3_SLLI  = 0b001,
    FUNCT3_SR    = 0b101,
};

enum {
    IMM_FUNCT_SRLI = 0b0000000,
    IMM_FUNCT_SRAI = 0b0100000,
};

// register codes
enum {
    FUNCT3_ADD  = 0b000,
    FUNCT3_SUB  = 0b000,
    FUNCT3_SLL  = 0b001,
    FUNCT3_SLT  = 0b010,
    FUNCT3_SLTU = 0b011,
    FUNCT3_XOR  = 0b100,
    FUNCT3_SRL  = 0b101,
    FUNCT3_SRA  = 0b101,
    FUNCT3_OR   = 0b110,
    FUNCT3_AND  = 0b111,
};

// branch codes
enum {
    FUNCT3_BEQ  = 0b000,
    FUNCT3_BNE  = 0b001,
    FUNCT3_BLT  = 0b100,
    FUNCT3_BGE  = 0b101,
    FUNCT3_BLTU = 0b110,
    FUNCT3_BGEU = 0b111,
};

enum {
    FUNCT7_ADD = 0b0000000,
    FUNCT7_SUB = 0b0100000,
    FUNCT7_SRL = 0b0000000,
    FUNCT7_SRA = 0b0100000,
};

// branch & flow control instructions
int instr_nop(riscv_state_t * state);
int instr_lui(riscv_state_t * state);
int instr_jal(riscv_state_t * state);
int instr_jalr(riscv_state_t * state);
int instr_beq(riscv_state_t * state);
int instr_bne(riscv_state_t * state);
int instr_blt(riscv_state_t * state);
int instr_bge(riscv_state_t * state);
int instr_bltu(riscv_state_t * state);
int instr_bgeu(riscv_state_t * state);


// immediate instructions
int instr_addi(riscv_state_t * state);
int instr_slti(riscv_state_t * state);
int instr_sltiu(riscv_state_t * state);
int instr_andi(riscv_state_t * state);
int instr_ori(riscv_state_t * state);
int instr_xori(riscv_state_t * state);
int instr_slli(riscv_state_t * state);
int instr_srli(riscv_state_t * state);
int instr_srai(riscv_state_t * state);

// reg-reg instructions
int instr_add(riscv_state_t * state);
int instr_slt(riscv_state_t * state);
int instr_sltu(riscv_state_t * state);
int instr_and(riscv_state_t * state);
int instr_or(riscv_state_t * state);
int instr_xor(riscv_state_t * state);
int instr_sll(riscv_state_t * state);
int instr_srl(riscv_state_t * state);
int instr_sub(riscv_state_t * state);
int instr_sra(riscv_state_t * state);