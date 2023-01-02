.section .text
.global _start

_start:
    nop
    andi a0, a0, 0x0
    addi a0, a0, 0x7EF
    andi a1, a0, 0x003

    andi a2, a2, 0x0
    addi a2, a2, -1

    slli a3, a2, 2
    srai a4, a2, 1
    srli a5, a2, 1

    slti  a6, a2, 0
    sltiu a7, a2, 0

hang:
    jal t0, hang

