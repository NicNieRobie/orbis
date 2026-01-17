#include "orbis/render/camera/camera.hpp"
#include "orbis/math/types.hpp"

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_common.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/trigonometric.hpp>

namespace orbis {
    Camera::Camera(float fov, float aspect, float nearPlane, float farPlane)
        : m_position(0.f), m_orientation(glm::quat_identity<float, glm::defaultp>()),
          m_fov(fov), m_aspect(aspect), m_near(nearPlane), m_far(farPlane) {
        updateProjection();
    }

    void Camera::updateProjection() {
        m_projection = glm::perspective(glm::radians(m_fov), m_aspect, m_near, m_far);
    }

    math::Mat4 Camera::getProjection() const {
        return m_projection;
    }

    math::Mat4 Camera::getView() const {
        math::Mat4 rotation = glm::toMat4(glm::conjugate(m_orientation));
        math::Mat4 translation = glm::translate(math::Mat4(1.f), -m_position);

        return rotation * translation;
    }

    void Camera::setFOV(float fov) {
        m_fov = fov;
        updateProjection();
    }

    void Camera::setAspect(float aspect) {
        m_aspect = aspect;
        updateProjection();
    }

    void Camera::setPosition(const math::Vec3& position) {
        m_position = math::Vec3(position);
    }
}
