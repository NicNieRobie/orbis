#pragma once

#include "Core/API.h"
#include "Render/Shading/Types.h"

#include <memory>
#include <string>
#include <vector>

namespace Orbis {
    enum class ShadingStage {
        VERTEX,
        FRAGMENT
    };

    struct ORBIS_API ShaderSource {
        ShadingStage stage;
        std::string path;
    };

    class ORBIS_API Shader {
    public:
        static std::shared_ptr<Shader> fromSources(const std::vector<ShaderSource>& sources);

        void bind() const;
        void unbind() const;

        void setUniform(const std::string& name, UniformValue value) const;

    private:
        unsigned int m_programHandle = 0;

        static unsigned int compileStage(ShaderSource source);
    };
}