#include "Render/Mesh/Cylinder.h"

#include <glad/glad.h>
#include <memory>

namespace Orbis {
    Cylinder::Cylinder(float radius, float height, uint32_t segments) : m_renderData(std::make_unique<Cylinder::RenderData>()) {
        const float h = height * 0.5f;
        const float step = 2.f * glm::pi<float>() / segments;

        std::vector<uint32_t> indices;

        indices.reserve(segments * 12);
        m_vertices.reserve(segments * 4 + 2);

        // Sides
        for (uint32_t i = 0; i <= segments; ++i) {
            float angle = i * step;
            float x = std::cos(angle) * radius;
            float z = std::sin(angle) * radius;

            Math::Vec3 normal{x / radius, 0.f, z / radius};

            m_vertices.push_back({
                {x, -h, z},
                normal,
                {static_cast<float>(i) / segments, 0.f}
            });

            m_vertices.push_back({
                {x, h, z},
                normal,
                {static_cast<float>(i) / segments, 1.f}
            });
        }

        for (uint32_t i = 0; i < segments; ++i) {
            uint32_t i0 = i * 2;
            uint32_t i1 = i0 + 1;
            uint32_t i2 = i0 + 2;
            uint32_t i3 = i0 + 3;

            indices.insert(indices.end(), {
                i0, i2, i1,
                i1, i2, i3
            });
        }

        // Top face
        uint32_t topCenterIndex = segments * 2;
        m_vertices.push_back({{0.f, h, 0.f}, {0.f, 1.f, 0.f}, {0.5f, 0.5f}});

        for (uint32_t i = 0; i <= segments; ++i) {
            float angle = i * step;
            float x = std::cos(angle) * radius;
            float z = std::sin(angle) * radius;

            m_vertices.push_back({
                {x, h, z},
                {0.f, 1.f, 0.f},
                {(x / radius + 1.f) * 0.5f, (z / radius + 1.f) * 0.5f}
            });
        }

        for (uint32_t i = 0; i < segments; ++i) {
            indices.insert(indices.end(), {
                topCenterIndex,
                topCenterIndex + i + 1,
                topCenterIndex + i + 2
            });
        }

        // Bottom face
        uint32_t bottomCenterIndex = segments * 3 + 1;
        m_vertices.push_back({{0.f, -h, 0.f}, {0.f, -1.f, 0.f}, {0.5f, 0.5f}});

        for (uint32_t i = 0; i <= segments; ++i) {
            float angle = i * step;
            float x = std::cos(angle) * radius;
            float z = std::sin(angle) * radius;

            m_vertices.push_back({
                {x, -h, z},
                {0.f, -1.f, 0.f},
                {(x / radius + 1.f) * 0.5f, (z / radius + 1.f) * 0.5f}
            });
        }

        for (uint32_t i = 0; i < segments; ++i) {
            indices.insert(indices.end(), {
                bottomCenterIndex,
                bottomCenterIndex + i + 2,
                bottomCenterIndex + i + 1
            });
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

    Cylinder::~Cylinder() {
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

    void Cylinder::bind() const {
        glBindVertexArray(m_renderData->vao);
    }

    void Cylinder::draw() const {
        glDrawElements(
            GL_TRIANGLES,
            static_cast<GLsizei>(m_renderData->indexCount),
            GL_UNSIGNED_INT,
            nullptr
        );
    }
}