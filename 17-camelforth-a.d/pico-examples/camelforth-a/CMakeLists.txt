add_executable(camelforth-a
        camelforth-a.c
        )


target_compile_definitions(camelforth-a PRIVATE
    # PICO_DEFAULT_BINARY_TYPE=no_flash # was: copy_to_ram
)

# target_link_libraries(camelforth-a forth pico-LED pico_stdlib)
target_link_libraries(camelforth-a PRIVATE forth pico-LED hardware_flash pico_stdlib)

pico_set_binary_type(camelforth-a copy_to_ram)
pico_enable_stdio_usb(camelforth-a 1)
pico_enable_stdio_uart(camelforth-a 1) # was zero

pico_add_extra_outputs(camelforth-a)

example_auto_set_url(camelforth-a)

if ( CMAKE_COMPILER_IS_GNUCC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()

add_subdirectory(forth)
add_subdirectory(pico-hw)
