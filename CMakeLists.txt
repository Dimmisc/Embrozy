cmake_minimum_required(VERSION 3.16)
project(MyOpenGLProject VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(glad STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/glad/src/glad.c
)

target_include_directories(glad PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/glad/include
)

find_package(glfw3 3.3 REQUIRED)
find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")
set(SOURCE_FILES ${SOURCE_FILES} main.cpp)

add_executable(Embrozy
    ${SOURCE_FILES}
)
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_link_options(Embrozy PRIVATE "-static-libgcc" "-static-libstdc++")
endif()

target_link_libraries(Embrozy PRIVATE
    glad
    glfw3
    glm::glm
    OpenGL::GL
)

set_target_properties(Embrozy PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..
)