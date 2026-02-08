set(ORBIS_SOURCES
        Source/Orbis/Render/Camera/Camera.cpp
        Source/Orbis/Render/Mesh/Primitive.cpp
        Source/Orbis/Render/Mesh/Cube.cpp
        Source/Orbis/Render/Mesh/Plane.cpp
        Source/Orbis/Render/Mesh/UVSphere.cpp
        Source/Orbis/Render/Mesh/Cylinder.cpp
        Source/Orbis/Render/Renderer/Renderer.cpp
        Source/Orbis/Render/Shading/Shader.cpp
        Source/Orbis/Render/Shading/Material.cpp
        Source/Orbis/Core/Application.cpp
        Source/Orbis/Logging/Log.cpp
)

set(ORBIS_HEADERS
        Source/Orbis/Math/Types.h
        Source/Orbis/Render/Camera/Camera.h
        Source/Orbis/Render/Mesh/Primitive.h
        Source/Orbis/Render/Mesh/Cube.h
        Source/Orbis/Render/Mesh/Plane.h
        Source/Orbis/Render/Mesh/UVSphere.h
        Source/Orbis/Render/Mesh/Cylinder.h
        Source/Orbis/Render/Renderer/Renderer.h
        Source/Orbis/Render/Shading/Shader.h
        Source/Orbis/Render/Shading/Material.h
        Source/Orbis/Render/Shading/Types.h
        Source/Orbis/Orbis.h
        Source/Orbis/Core/Application.h
        Source/Orbis/Logging/Log.h
        Source/Orbis/Logging/LogMacros.h
        Source/Orbis/Core/API.h
        Source/Orbis/Core/Main.h
)

add_library(Orbis SHARED)

target_sources(Orbis
    PRIVATE
        ${ORBIS_SOURCES}
    PUBLIC
        Source/Orbis/Orbis.h
)

target_include_directories(Orbis
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Source/Orbis>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Orbis
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(Vendor/glfw)

add_subdirectory(Vendor/glm)

add_subdirectory(Vendor/quill)

target_compile_definitions(Orbis PRIVATE ORBIS_BUILD_DLL)

add_library(glad
        STATIC
        Vendor/glad/src/glad.c
)

target_include_directories(glad
        PUBLIC
        Vendor/glad/include
)

find_package(OpenGL REQUIRED)

target_link_libraries(Orbis
    PUBLIC glm quill::quill
    PRIVATE glad glfw
)

target_compile_features(Orbis PUBLIC cxx_std_20)