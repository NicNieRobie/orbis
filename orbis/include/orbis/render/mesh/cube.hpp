#pragma once

#include "orbis/math/types.hpp"
#include "orbis/render/mesh/primitive.hpp"

#include <memory>
#include <vector>

namespace orbis {
    class Cube : public Primitive {
    public:
        Cube(float size = 1.f);
        ~Cube();

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
