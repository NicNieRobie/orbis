#include "Render/Mesh/Primitive.h"

#include <glm/geometric.hpp>

namespace Orbis {
    void Primitive::setPosition(const Math::Vec3& pos) {
        m_position = pos;
        updateModelMatrix();
    }

    void Primitive::setRotation(const Math::Quat& rot) {
        m_rotation = rot;
        updateModelMatrix();
    }

    void Primitive::setScale(const Math::Vec3& scale) {
        m_scale = scale;
        updateModelMatrix();
    }

    void Primitive::setEulerRotation(const Math::Vec3& eulerRot) {
        m_rotation = glm::quat(eulerRot);
        updateModelMatrix();
    }

    void Primitive::translate(const Math::Vec3& delta, Space space) {
        if (space == Space::WORLD) {
            m_position += delta;
        } else {
            m_position += m_rotation * delta;
        }

        updateModelMatrix();
    }

    void Primitive::rotate(float angleRad, const Math::Vec3& axis, Space space) {
        Math::Quat q = glm::angleAxis(angleRad, glm::normalize(axis));

        if (space == Space::WORLD) {
            m_rotation = glm::normalize(q * m_rotation);
        } else {
            m_rotation = glm::normalize(m_rotation * q);
        }

        updateModelMatrix();
    }

    void Primitive::updateModelMatrix() {
        Math::Mat4 model = Math::Mat4(1.0f);

        model = glm::translate(model, m_position);
        model *= glm::mat4_cast(m_rotation);
        model = glm::scale(model, m_scale);

        m_modelMatrix = model;
    }
}
