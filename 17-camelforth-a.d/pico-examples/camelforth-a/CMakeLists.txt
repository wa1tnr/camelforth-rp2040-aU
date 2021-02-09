add_executable(camelforth-a
        camelforth-a.c
        )

target_link_libraries(camelforth-a forth pico-LED pico_stdlib)

pico_enable_stdio_usb(camelforth-a 1)
pico_enable_stdio_uart(camelforth-a 1) # was zero

pico_add_extra_outputs(camelforth-a)

example_auto_set_url(camelforth-a)
add_subdirectory(forth)
add_subdirectory(pico-hw)
