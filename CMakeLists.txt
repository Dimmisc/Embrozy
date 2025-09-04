cmake_minimum_required(VERSION 3.10)
project(Embrozy VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories for header files
include_directories(include)                # For glad, KHR etc.
include_directories(glad/include)

# Find packages
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(glm REQUIRED)

# Add include dirs from your packages
include_directories(${GLEW_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS})

# Recursively collect all .cpp files from src, including all subdirectories
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

# Also include main.cpp if it's outside of src
set(SOURCE_FILES ${SOURCE_FILES} main.cpp)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Link libraries
target_link_libraries(${PROJECT_NAME} OpenGL::GL  glfw)
    
# Optional Windows definitions
if(WIN32)
    add_definitions(-D_WIN32_WINNT=0x0A00)
endif()