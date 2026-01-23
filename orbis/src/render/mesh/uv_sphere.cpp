#include "orbis/math/types.hpp"
#include "orbis/render/mesh/uv_sphere.hpp"

#include <glad/glad.h>
#include <glm/ext/scalar_constants.hpp>
#include <memory>

namespace orbis {
    UVSphere::UVSphere(float radius, uint32_t rings, uint32_t segments) : m_renderData(std::make_unique<UVSphere::RenderData>()) {
        m_vertices.reserve((rings + 1) * (segments + 1));

        for (uint32_t y = 0; y <= rings; ++y) {
            float v = static_cast<float>(y) / rings;
            float theta = v * glm::pi<float>();

            float sinTheta = std::sin(theta);
            float cosTheta = std::cos(theta);

            for (uint32_t x = 0; x <= segments; ++x) {
                float u = static_cast<float>(x) / segments;
                float phi = u * 2.f * glm::pi<float>();

                float sinPhi = std::sin(phi);
                float cosPhi = std::cos(phi);

                math::Vec3 normal{
                    cosPhi * sinTheta,
                    cosTheta,
                    sinPhi * sinTheta
                };

                math::Vec3 position = normal * radius;
                
                m_vertices.push_back({
                    position,
                    normal,
                    {u, 1.f - v}
                });
            }
        }

        std::vector<uint32_t> indices;
        indices.reserve(rings * segments * 6);

        for (uint32_t y = 0; y < rings; ++y) {
            for (uint32_t x = 0; x < segments; ++x) {
                uint32_t i0 = y * (segments + 1) + x;
                uint32_t i1 = i0 + 1;
                uint32_t i2 = i0 + (segments + 1);
                uint32_t i3 = i2 + 1;

                indices.insert(indices.end(), {
                    i0, i2, i1,
                    i1, i2, i3
                });
            }
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

    UVSphere::~UVSphere() {
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

    void UVSphere::bind() const {
        glBindVertexArray(m_renderData->vao);
    }

    void UVSphere::draw() const {
        glDrawElements(
            GL_TRIANGLES,
            static_cast<GLsizei>(m_renderData->indexCount),
            GL_UNSIGNED_INT,
            nullptr
        );
    }
}
