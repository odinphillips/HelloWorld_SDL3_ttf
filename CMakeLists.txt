cmake_minimum_required(VERSION 3.12.0)
project(HelloWorld_SDL3_ttf)

find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_ttf CONFIG REQUIRED)

add_executable(helloworld-sdl3-ttf
    main.cpp
)

target_link_libraries(helloworld-sdl3-ttf PRIVATE SDL3::SDL3)
target_link_libraries(helloworld-sdl3-ttf PRIVATE SDL3_ttf::SDL3_ttf)

file(GLOB DLLS "${CMAKE_SOURCE_DIR}/dlls/*.dll")
add_custom_target(copy_dlls
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${DLLS}
        "${CMAKE_BINARY_DIR}"
    COMMENT "Copying dlls to build directory"
)

set(FONT_DIR "${CMAKE_SOURCE_DIR}/fonts")
add_custom_target(copy_fonts
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
        "${FONT_DIR}"
        "${CMAKE_BINARY_DIR}/fonts"
    COMMENT "Copying fonts to build directory"
)

add_dependencies(helloworld-sdl3-ttf copy_dlls copy_fonts)

# This is safe to set on all platforms. Otherwise your SDL app will
#  have a terminal window pop up with it on Windows.
set_property(TARGET helloworld-sdl3-ttf PROPERTY WIN32_EXECUTABLE TRUE)
