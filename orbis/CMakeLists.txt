add_library(orbis
    src/orbis.cpp
)

add_library(orbis::orbis ALIAS orbis)

target_include_directories(orbis
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(orbis
    PUBLIC
        glfw
        glad
        OpenGL::GL
)

target_compile_features(orbis PUBLIC cxx_std_17)

if (MSVC)
    target_compile_options(orbis PRIVATE /W4)
else()
    target_compile_options(orbis PRIVATE -Wall -Wextra -Wpedantic)
endif()
