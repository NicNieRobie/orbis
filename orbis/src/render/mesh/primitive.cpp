#include "orbis/render/mesh/primitive.hpp"
#include "orbis/math/types.hpp"

namespace orbis {
    void Primitive::updateModelMatrix() {
        math::Mat4 model = math::Mat4(1.0f);

        model = glm::translate(model, m_position);
        model *= glm::mat4_cast(m_rotation);
        model = glm::scale(model, m_scale);

        m_modelMatrix = model;
    }
}
