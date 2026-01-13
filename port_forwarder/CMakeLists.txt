cmake_minimum_required(VERSION 3.13...3.27)

# Generate compile_commands.json for VSCode IntelliSense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PICO_BOARD pico2)

include( ../../pico-sdk/pico_sdk_init.cmake)

set(project_name port_forwarder)
project(${project_name})

pico_sdk_init()

FILE(GLOB c_code_src *.c *.h)
FILE(GLOB pio_code_src *.pio)


add_executable(${project_name})

pico_generate_pio_header(${project_name} ${pio_code_src})
target_sources(${project_name} PRIVATE ${c_code_src})

target_include_directories(${project_name} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

# todo - want -pedantic
target_compile_options(${project_name} PRIVATE -Wall -Wextra -Werror)

# Add pico_stdlib library which aggregates commonly used featuresT
target_link_libraries(${project_name}
	pico_stdlib
	hardware_pio
	)

pico_enable_stdio_usb(${project_name} 1)
pico_enable_stdio_uart(${project_name} 0)


# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(${project_name})

