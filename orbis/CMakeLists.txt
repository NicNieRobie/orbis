file(GLOB_RECURSE ORBIS_HEADERS "Source/*.h")
file(GLOB_RECURSE ORBIS_SOURCES "Source/*.cpp")

add_library(Orbis STATIC ${ORBIS_SOURCES} ${ORBIS_HEADERS})

target_include_directories(Orbis PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Source
)

target_link_libraries(Orbis PUBLIC glad glfw glm)
