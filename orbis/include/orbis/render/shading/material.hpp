#pragma once

#include "orbis/render/shading/shader.hpp"

#include <memory>
#include <string>
#include <unordered_map>

namespace orbis {
    class Shader;

    class Material {
    public:
        static std::shared_ptr<Material> create(std::shared_ptr<Shader> shader);

        void bind() const;

        void setUniform(const std::string& name, UniformValue value);

    private:
        explicit Material(std::shared_ptr<Shader> shader);

        std::shared_ptr<Shader> m_shader;
        std::unordered_map<std::string, UniformValue> m_uniformValues;
    };
}