#pragma once

#include "Core/API.h"
#include "Render/Camera/Camera.h"
#include "Render/Mesh/Primitive.h"

#include <memory>
#include <vector>

class GLFWwindow;

namespace Orbis {
    class Cube;
    class Material;

    struct ORBIS_API RenderContext {
        std::shared_ptr<Camera> camera;
    };

    struct ORBIS_API RenderObject {
        Primitive* mesh;
        std::shared_ptr<Material> material;
    };

    class ORBIS_API Renderer {
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
