#pragma once

#include "orbis/math/types.hpp"

namespace orbis {
    enum class Space {
        LOCAL,
        WORLD
    };

    class Primitive {
    public:
        Primitive() = default;

        void setPosition(const math::Vec3& pos);
        void setRotation(const math::Quat& rot);
        void setScale(const math::Vec3& scale);

        void setEulerRotation(const math::Vec3& eulerRot);

        void translate(const math::Vec3& delta, Space space = Space::WORLD);
        void rotate(float angleRad, const math::Vec3& axis, Space space = Space::WORLD);

        virtual void bind() const = 0;
        virtual void draw() const = 0;

        const math::Vec3& position() const { return m_position; }
        const math::Quat& rotation() const { return m_rotation; }
        const math::Vec3& scale() const { return m_scale; }

        const math::Mat4& modelMatrix() const { return m_modelMatrix; }

    protected:
        void updateModelMatrix();

        math::Vec3 m_position {0.f};
        math::Quat m_rotation {1.f, 0.f, 0.f, 0.f};
        math::Vec3 m_scale {1.f};
        math::Mat4 m_modelMatrix;
    };
}
