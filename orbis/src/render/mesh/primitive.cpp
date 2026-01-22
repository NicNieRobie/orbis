#include "orbis/render/mesh/primitive.hpp"
#include "orbis/math/types.hpp"
#include <glm/geometric.hpp>

namespace orbis {
    void Primitive::setPosition(const math::Vec3& pos) {
        m_position = pos;
        updateModelMatrix();
    }

    void Primitive::setRotation(const math::Quat& rot) {
        m_rotation = rot;
        updateModelMatrix();
    }

    void Primitive::setScale(const math::Vec3& scale) {
        m_scale = scale;
        updateModelMatrix();
    }

    void Primitive::setEulerRotation(const math::Vec3& eulerRot) {
        m_rotation = glm::quat(eulerRot);
        updateModelMatrix();
    }

    void Primitive::translate(const math::Vec3& delta, Space space) {
        if (space == Space::WORLD) {
            m_position += delta;
        } else {
            m_position += m_rotation * delta;
        }

        updateModelMatrix();
    }

    void Primitive::rotate(float angleRad, const math::Vec3& axis, Space space) {
        math::Quat q = glm::angleAxis(angleRad, glm::normalize(axis));

        if (space == Space::WORLD) {
            m_rotation = glm::normalize(q * m_rotation);
        } else {
            m_rotation = glm::normalize(m_rotation * q);
        }

        updateModelMatrix();
    }

    void Primitive::updateModelMatrix() {
        math::Mat4 model = math::Mat4(1.0f);

        model = glm::translate(model, m_position);
        model *= glm::mat4_cast(m_rotation);
        model = glm::scale(model, m_scale);

        m_modelMatrix = model;
    }
}
