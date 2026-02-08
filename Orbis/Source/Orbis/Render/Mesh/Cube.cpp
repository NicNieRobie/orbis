#include "Render/Mesh/Cube.h"

#include <glad/glad.h>
#include <memory>

namespace Orbis {
    Cube::Cube(float size) : m_renderData(std::make_unique<Cube::RenderData>()) {
        const float h = size * 0.5f;

        m_vertices.reserve(24);

        // +Z
        {
            Math::Vec3 n{0.f, 0.f, 1.f};
            m_vertices.push_back({{-h, -h,  h}, n, {0.f, 0.f}});
            m_vertices.push_back({{ h, -h,  h}, n, {1.f, 0.f}});
            m_vertices.push_back({{ h,  h,  h}, n, {1.f, 1.f}});
            m_vertices.push_back({{-h,  h,  h}, n, {0.f, 1.f}});
        }

        // -Z
        {
            Math::Vec3 n{0.f, 0.f, -1.f};
            m_vertices.push_back({{ h, -h, -h}, n, {0.f, 0.f}});
            m_vertices.push_back({{-h, -h, -h}, n, {1.f, 0.f}});
            m_vertices.push_back({{-h,  h, -h}, n, {1.f, 1.f}});
            m_vertices.push_back({{ h,  h, -h}, n, {0.f, 1.f}});
        }

        // +X
        {
            Math::Vec3 n{1.f, 0.f, 0.f};
            m_vertices.push_back({{ h, -h,  h}, n, {0.f, 0.f}});
            m_vertices.push_back({{ h, -h, -h}, n, {1.f, 0.f}});
            m_vertices.push_back({{ h,  h, -h}, n, {1.f, 1.f}});
            m_vertices.push_back({{ h,  h,  h}, n, {0.f, 1.f}});
        }

        // -X
        {
            Math::Vec3 n{-1.f, 0.f, 0.f};
            m_vertices.push_back({{-h, -h, -h}, n, {0.f, 0.f}});
            m_vertices.push_back({{-h, -h,  h}, n, {1.f, 0.f}});
            m_vertices.push_back({{-h,  h,  h}, n, {1.f, 1.f}});
            m_vertices.push_back({{-h,  h, -h}, n, {0.f, 1.f}});
        }

        // +Y
        {
            Math::Vec3 n{0.f, 1.f, 0.f};
            m_vertices.push_back({{-h,  h,  h}, n, {0.f, 0.f}});
            m_vertices.push_back({{ h,  h,  h}, n, {1.f, 0.f}});
            m_vertices.push_back({{ h,  h, -h}, n, {1.f, 1.f}});
            m_vertices.push_back({{-h,  h, -h}, n, {0.f, 1.f}});
        }

        // -Y
        {
            Math::Vec3 n{0.f, -1.f, 0.f};
            m_vertices.push_back({{-h, -h, -h}, n, {0.f, 0.f}});
            m_vertices.push_back({{ h, -h, -h}, n, {1.f, 0.f}});
            m_vertices.push_back({{ h, -h,  h}, n, {1.f, 1.f}});
            m_vertices.push_back({{-h, -h,  h}, n, {0.f, 1.f}});
        }

        std::vector<uint32_t> indices;
        indices.reserve(36);

        for (uint32_t i = 0; i < 6; ++i) {
            uint32_t base = i * 4;
            indices.push_back(base + 0);
            indices.push_back(base + 1);
            indices.push_back(base + 2);
            indices.push_back(base + 2);
            indices.push_back(base + 3);
            indices.push_back(base + 0);
        }

        m_renderData->indexCount = indices.size();

        glGenVertexArrays(1, &m_renderData->vao);
        glGenBuffers(1, &m_renderData->vbo);
        glGenBuffers(1, &m_renderData->ebo);

        glBindVertexArray(m_renderData->vao);

        glBindBuffer(GL_ARRAY_BUFFER, m_renderData->vbo);
        glBufferData(
            GL_ARRAY_BUFFER,
            m_vertices.size() * sizeof(Vertex),
            m_vertices.data(),
            GL_STATIC_DRAW
        );

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderData->ebo);
        glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            indices.size() * sizeof(uint32_t),
            indices.data(),
            GL_STATIC_DRAW
        );

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(
            0, 3, GL_FLOAT, GL_FALSE,
            sizeof(Vertex),
            (void*)offsetof(Vertex, position)
        );

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(
            1, 3, GL_FLOAT, GL_FALSE,
            sizeof(Vertex),
            (void*)offsetof(Vertex, normal)
        );

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(
            2, 2, GL_FLOAT, GL_FALSE,
            sizeof(Vertex),
            (void*)offsetof(Vertex, uv)
        );

        glBindVertexArray(0);

        updateModelMatrix();
    }

    Cube::~Cube() {
        if (m_renderData) {
            if (m_renderData->vao) {
                glDeleteVertexArrays(1, &m_renderData->vao);
            }
            if (m_renderData->vbo) {
                glDeleteBuffers(1, &m_renderData->vbo);
            }
            if (m_renderData->ebo) {
                glDeleteBuffers(1, &m_renderData->ebo);
            }
        }
    }

    void Cube::bind() const {
        glBindVertexArray(m_renderData->vao);
    }

    void Cube::draw() const {
        glDrawElements(
            GL_TRIANGLES,
            static_cast<GLsizei>(m_renderData->indexCount),
            GL_UNSIGNED_INT,
            nullptr
        );
    }
}
