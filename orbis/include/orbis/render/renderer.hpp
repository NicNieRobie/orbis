#pragma once

#include "orbis/math/types.hpp"
#include "orbis/render/camera/camera.hpp"

#include <memory>
#include <vector>

class GLFWwindow;

namespace orbis {
    class Cube;
    class Material;

    struct RenderContext {
        std::shared_ptr<Camera> camera;
    };

    struct RenderObject {
        Cube* mesh;
        std::shared_ptr<Material> material;
        math::Mat4 transform;
    };

    class Renderer {
    public:
        static Renderer init();

        void initFrame();
        void submitRenderObject(const RenderObject& renderObject);
        void finishFrame();

    private:
        RenderContext m_renderContext;

        std::vector<RenderObject> m_renderQueue;

        void renderQueue() const;
        void renderObject(const RenderObject& renderObject) const;
    };
}
