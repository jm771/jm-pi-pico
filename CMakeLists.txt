cmake_minimum_required(VERSION 3.13...3.27)

include( ../pico-sdk/pico_sdk_init.cmake)

set(project_name $ENV{PROJECT_NAME})
project(${project_name})

pico_sdk_init()

FILE(GLOB c_code_src *.c *.h)
FILE(GLOB pio_code_src *.pio)


add_executable(${project_name})

target_sources(${project_name} PRIVATE ${c_code_src})

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(${project_name}
	pico_stdlib
	)

pico_enable_stdio_usb(${project_name} 1)
pico_enable_stdio_uart(${project_name} 0)


# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(${project_name})

