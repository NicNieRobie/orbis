#pragma once

#include "orbis/render/mesh/primitive.hpp"

#include <memory>
#include <vector>

namespace orbis {
    class UVSphere : public Primitive {
    public:
        UVSphere(
            float radius = 0.5f,
            uint32_t rings = 16,
            uint32_t segments = 32
        );
        ~UVSphere();

        void bind() const override;
        void draw() const override;

    private:
        struct RenderData {
            unsigned int vao = 0;
            unsigned int vbo = 0;
            unsigned int ebo = 0;
            size_t indexCount = 0;
        };

        struct Vertex {
            math::Vec3 position;
            math::Vec3 normal;
            math::Vec2 uv;
        };

        std::unique_ptr<RenderData> m_renderData;
        std::vector<Vertex> m_vertices;
    };
}