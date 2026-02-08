#pragma once

#include "Core/API.h"
#include "Math/Types.h"

namespace Orbis {
    enum class Space {
        LOCAL,
        WORLD
    };

    class ORBIS_API Primitive {
    public:
        Primitive() = default;
        virtual ~Primitive() = default;

        void setPosition(const Math::Vec3& pos);
        void setRotation(const Math::Quat& rot);
        void setScale(const Math::Vec3& scale);

        void setEulerRotation(const Math::Vec3& eulerRot);

        void translate(const Math::Vec3& delta, Space space = Space::WORLD);
        void rotate(float angleRad, const Math::Vec3& axis, Space space = Space::WORLD);

        virtual void bind() const = 0;
        virtual void draw() const = 0;

        const Math::Vec3& position() const { return m_position; }
        const Math::Quat& rotation() const { return m_rotation; }
        const Math::Vec3& scale() const { return m_scale; }

        const Math::Mat4& modelMatrix() const { return m_modelMatrix; }

    protected:
        void updateModelMatrix();

        Math::Vec3 m_position {0.f};
        Math::Quat m_rotation {1.f, 0.f, 0.f, 0.f};
        Math::Vec3 m_scale {1.f};
        Math::Mat4 m_modelMatrix{};
    };
}
