file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/simple_shader.vert
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/simple_shader.frag
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(triangle
    main.cpp
)

target_link_libraries(triangle
    PRIVATE
        orbis
)
