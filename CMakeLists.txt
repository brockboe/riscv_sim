cmake_minimum_required(VERSION 3.0)

project(riscv_sim)

set(SOURCES
    sim/runner/sim_main.c
    sim/runner/elf_tools.c
    sim/runner/sim_ops.c
    sim/isa/instr_branch.c
)

add_executable(riscv_sim ${SOURCES})

target_compile_options(riscv_sim PRIVATE
  -Wall -Wextra -Werror
)

target_include_directories(riscv_sim
    PUBLIC
        ${PROJECT_SOURCE_DIR}/sim/isa
        ${PROJECT_SOURCE_DIR}/sim/runner
)

add_subdirectory(sim/test/elf)
