cmake_minimum_required(VERSION 3.10)
project(OpenGL)

set(CMAKE_CXX_STANDARD 14)
set(GLAD_INCLUDE /Users/bytedance/Documents/OpenGL/glad/include)

find_package(glfw3 REQUIRED)

include_directories(${GLAD_INCLUDE})

add_executable(
        OpenGL
        src/includes/shader_s.h
        src/includes/stb_image.h
        src/includes/utils.h
        src/includes/utils.cpp
        src/texture.cpp
        glad.c
)

target_link_libraries(OpenGL glfw)
