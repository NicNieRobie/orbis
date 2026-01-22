#include "orbis/render/mesh/cube.hpp"
#include "orbis/render/renderer.hpp"
#include "orbis/render/shading/material.hpp"
#include "orbis/render/shading/shader.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <orbis/orbis.hpp>

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Orbis - Cube Example", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGL()) {
        std::cerr << "Failed to init GLAD\n";
        return -1;
    }

    glViewport(0, 0, 1280, 720);
    glEnable(GL_DEPTH_TEST);

    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    orbis::Renderer renderer = orbis::Renderer::init();
    orbis::Cube cube = orbis::Cube(1.f);

    auto shader = orbis::Shader::fromSources({
        {
            orbis::ShadingStage::VERTEX,
            "./simple_shader.vert"
        },
        {
            orbis::ShadingStage::FRAGMENT,
            "./simple_shader.frag"
        }
    });

    auto material = orbis::Material::create(shader);

    while (!glfwWindowShouldClose(window)) {
        renderer.initFrame();

        renderer.submitRenderObject({
            &cube,
            material,
            orbis::math::Mat4(1.f)
        });

        cube.rotate(0.01f, {1.f, 1.f, 0.f});

        renderer.finishFrame();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}