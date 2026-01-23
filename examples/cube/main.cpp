#include "orbis/math/types.hpp"
#include "orbis/render/mesh/cube.hpp"
#include "orbis/render/mesh/plane.hpp"
#include "orbis/render/mesh/cylinder.hpp"
#include "orbis/render/mesh/uv_sphere.hpp"
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
    orbis::Plane plane = orbis::Plane(3.f);
    orbis::Cylinder cylinder = orbis::Cylinder();
    orbis::UVSphere sphere = orbis::UVSphere(0.6f);

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

    plane.rotate(10.f, {1.f, 0.f, 0.f});

    cylinder.translate({3.f, 1.f, 0.f});

    auto material1 = orbis::Material::create(shader);
    material1->setUniform("color", orbis::math::Vec4{1.0f, 0.4f, 1.0f, 1.0f});

    auto material2 = orbis::Material::create(shader);
    material2->setUniform("color", orbis::math::Vec4{0.0f, 0.4f, 0.0f, 1.0f});

    auto material3 = orbis::Material::create(shader);
    material3->setUniform("color", orbis::math::Vec4{0.0f, 0.4f, 1.0f, 1.0f});

    auto material4 = orbis::Material::create(shader);
    material4->setUniform("color", orbis::math::Vec4{1.0f, 0.2f, 1.0f, 1.0f});

    while (!glfwWindowShouldClose(window)) {
        renderer.initFrame();

        renderer.submitRenderObject({
            &cube,
            material1
        });

        renderer.submitRenderObject({
            &plane,
            material2
        });

        renderer.submitRenderObject({
            &cylinder,
            material3
        });

        renderer.submitRenderObject({
            &sphere,
            material4
        });

        cube.rotate(0.01f, {1.f, 1.f, 0.f});
        plane.rotate(0.05f, {1.f, 0.f, 0.f});
        cylinder.rotate(-0.01f, {1.f, 1.f, 0.f});

        renderer.finishFrame();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}