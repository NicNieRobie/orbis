#pragma once

#include "orbis/math/types.hpp"

namespace orbis {
    class Camera {
    public:
        Camera(float fov, float aspect, float nearPlane, float farPlane);

        math::Mat4 getView() const;
        math::Mat4 getProjection() const;

        void setPosition(const math::Vec3& position);

        void setFOV(float fov);
        void setAspect(float aspect);

    private:
        math::Vec3 m_position;
        math::Quat m_orientation;

        float m_fov;
        float m_aspect;
        float m_near;
        float m_far;

        math::Mat4 m_projection;

        void updateProjection();
    };
}