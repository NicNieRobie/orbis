#include "Render/Shading/Material.h"
#include "Render/Shading/Shader.h"

#include <memory>
#include <stdexcept>

namespace Orbis {
    std::shared_ptr<Material> Material::create(std::shared_ptr<Shader> shader) {
        if (!shader) {
            throw std::runtime_error("[ERROR][MATERIAL] Material::create() received a null shader");
        }

        return std::shared_ptr<Material>(new Material(shader));
    }

    Material::Material(std::shared_ptr<Shader> shader) : m_shader(std::move(shader)) { }

    void Material::setUniform(const std::string& name, UniformValue value) {
        m_uniformValues[name] = std::move(value);
    }

    void Material::bind() const {
        if (!m_shader) return;
        m_shader->bind();

        for (const auto& [name, value] : m_uniformValues) {
            m_shader->setUniform(name, value);
        }
    }
}
