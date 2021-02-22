add_executable(camelforth-a
        camelforth-a.c
        )
target_compile_definitions(camelforth-a PRIVATE
    #PICO_ENTER_USB_BOOT_ON_EXIT=1
    PICO_ENTER_USB_BOOT_ON_EXIT=0
)

# target_link_libraries(camelforth-a forth pico-LED pico_stdlib)
# target_link_libraries(pico_stdlib_test PRIVATE pico_stdlib)
target_link_libraries(camelforth-a PRIVATE forth pico-LED pico_stdlib)

pico_enable_stdio_usb(camelforth-a 1)
pico_enable_stdio_uart(camelforth-a 1) # was zero

pico_add_extra_outputs(camelforth-a)

example_auto_set_url(camelforth-a)

if ( CMAKE_COMPILER_IS_GNUCC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()

add_subdirectory(forth)
add_subdirectory(pico-hw)
