#include "orbis/render/renderer.hpp"
#include "orbis/render/mesh/cube.hpp"
#include "orbis/render/shading/material.hpp"

#include <glad/glad.h>

namespace orbis {
    Renderer Renderer::init() {
        Renderer renderer;
        renderer.m_renderContext = {
            std::make_shared<Camera>(60.f, 1280.f / 720.f, 0.1f, 100.f)
        };

        renderer.m_renderContext.camera->setPosition({0.f, 0.f, 5.f});

        return renderer;
    }

    void Renderer::initFrame() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::finishFrame() {
        renderQueue();
    }

    void Renderer::submitRenderObject(const RenderObject& renderObject) {
        m_renderQueue.push_back(renderObject);
    }

    void Renderer::renderQueue() const {
        for (auto renderObj : m_renderQueue) {
            renderObject(renderObj);
        }
    }

    void Renderer::renderObject(const RenderObject& renderObject) const {
        renderObject.material->setUniform("view", m_renderContext.camera->getView());
        renderObject.material->setUniform("proj", m_renderContext.camera->getProjection());
        renderObject.material->setUniform("model", renderObject.mesh->modelMatrix());

        renderObject.material->bind();

        renderObject.mesh->bind();
        renderObject.mesh->draw();
    }
}