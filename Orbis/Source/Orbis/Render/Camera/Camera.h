#pragma once

#include "Core/API.h"
#include "Math/Types.h"

namespace Orbis {
    class ORBIS_API Camera {
    public:
        Camera(float fov, float aspect, float nearPlane, float farPlane);

        Math::Mat4 getView() const;
        Math::Mat4 getProjection() const;

        void setPosition(const Math::Vec3& position);

        void setFOV(float fov);
        void setAspect(float aspect);

    private:
        Math::Vec3 m_position;
        Math::Quat m_orientation;

        float m_fov;
        float m_aspect;
        float m_near;
        float m_far;

        Math::Mat4 m_projection;

        void updateProjection();
    };
}