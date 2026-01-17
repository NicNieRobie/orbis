#pragma once

#include "orbis/math/types.hpp"

namespace orbis {
    class Primitive {
    public:
        Primitive() = default;

        void setPosition(const math::Vec3& pos) { m_position = pos; }
        void setRotation(const math::Quat& rot) { m_rotation = rot; }
        void setScale(const math::Vec3& scale) { m_scale = scale; }

        virtual void bind() const = 0;
        virtual void draw() const = 0;

        const math::Mat4& modelMatrix() const { return m_modelMatrix; }

    protected:
        void updateModelMatrix();

        math::Vec3 m_position {0.f};
        math::Quat m_rotation {1.f, 0.f, 0.f, 0.f};
        math::Vec3 m_scale {1.f};
        math::Mat4 m_modelMatrix;
    };
}
