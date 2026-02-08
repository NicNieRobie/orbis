add_executable(ExampleApp
    main.cpp
)

add_custom_command(
    TARGET ExampleApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/simple_shader.vert
        $<TARGET_FILE_DIR:ExampleApp>
)

add_custom_command(
    TARGET ExampleApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/simple_shader.frag
        $<TARGET_FILE_DIR:ExampleApp>
)

target_link_libraries(ExampleApp
    PRIVATE
        Orbis
)
