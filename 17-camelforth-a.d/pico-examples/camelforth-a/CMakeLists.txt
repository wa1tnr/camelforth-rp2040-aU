add_executable(camelforth-a
        camelforth-a.c
        )


target_compile_definitions(camelforth-a PRIVATE
    # PICO_DEFAULT_BINARY_TYPE=no_flash # was: copy_to_ram
)

# target_link_libraries(camelforth-a forth pico-LED pico_stdlib)
# target_link_libraries(camelforth-a PRIVATE forth pico-LED hardware_flash pico_stdlib)
target_link_libraries(camelforth-a forth pico-LED hardware_flash pico_stdlib)

# pico_set_binary_type(camelforth-a copy_to_ram)
pico_set_binary_type(camelforth-a copy_to_ram)
# pico_set_binary_type(camelforth-a no_flash)
# pico_set_binary_type(camelforth-a no_flash)

# 8910 offset copy_to_ram differs
# ok next drop drop
# 10008B4C:  F8 B5 C0 46  00 00 00 00   01 B4 02 48  84 46 01 BC   ...F.......H.F..
# 20008900:  F8 B5 C0 46  00 00 00 00   01 B4 02 48  84 46 01 BC   ...F.......H.F..
# ok next drop drop
# 10008B5C:  60 47 00 BF  73 02 00 10   10 B5 02 68  00 24 EF F3   `G..s......h.$..
# 20008910:  60 47 00 BF  73 02 00 10   F5 5B D4 3A  7B CF 23 73   `G..s....[.:{.#s

pico_enable_stdio_usb(camelforth-a 1)
pico_enable_stdio_uart(camelforth-a 1) # was zero

pico_add_extra_outputs(camelforth-a)

example_auto_set_url(camelforth-a)

if ( CMAKE_COMPILER_IS_GNUCC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()

add_subdirectory(forth)
add_subdirectory(pico-hw)
