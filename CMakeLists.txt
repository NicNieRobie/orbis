cmake_minimum_required(VERSION 3.16)

project(Orbis LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ----------------------------------------
# Options
# ----------------------------------------
option(ORBIS_BUILD_EXAMPLES "Build orbis examples" ON)

# ----------------------------------------
# GLFW
# ----------------------------------------
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)

# ----------------------------------------
# GLAD
# ----------------------------------------
add_library(glad
    external/glad/src/glad.c
)

target_include_directories(glad
    PUBLIC
        external/glad/include
)

target_link_libraries(glad
    PUBLIC
        ${CMAKE_DL_LIBS}
)

# ----------------------------------------
# OpenGL
# ----------------------------------------
find_package(OpenGL REQUIRED)

# ----------------------------------------
# Engine
# ----------------------------------------
add_subdirectory(orbis)

# ----------------------------------------
# Examples
# ----------------------------------------
if (ORBIS_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
