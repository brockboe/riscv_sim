.section .text
.global _start

_start:
    nop
    andi a0, a0, 0x0
    andi a1, a1, 0x0
    addi a1, a1, 0x7ef
    add a1, a0, a1

    andi a0, a0, 0x0
    addi a0, a0, 0x3
    and a0, a1, a0

    andi a2, a2, 0x0
    addi a2, a2, -1
    andi a3, a3, 0x0
    addi a3, a3, 1
    addi a3, a3, 0x3

    sll a4, a2, a3
    sra a5, a2, a3
    srl a6, a2, a3

    slt a7, a2, a3
    sltu t1, a2, a3

hang:
    jal t0, hang

