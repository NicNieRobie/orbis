#pragma once

#include "Render/Mesh/Primitive.h"

#include <memory>
#include <vector>

namespace Orbis {
    class Plane : public Primitive {
    public:
        Plane(float size = 1.f);
        ~Plane();

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
            Math::Vec3 position;
            Math::Vec3 normal;
            Math::Vec2 uv;
        };

        std::unique_ptr<RenderData> m_renderData;
        std::vector<Vertex> m_vertices;
    };
}