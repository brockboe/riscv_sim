set(EXECUTABLE_NAME elf_reader)

set(SOURCES
    ../../runner/elf_tools.c
    elf_reader.c
)

include_directories(
    ../../runner
)

add_executable(${EXECUTABLE_NAME} ${SOURCES})

target_compile_options(${EXECUTABLE_NAME} PRIVATE
  -Wall -Wextra -Werror
)