#include "Render/Shading/Shader.h"
#include "Logging/Logger.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

namespace {
    GLenum toGL(Orbis::ShadingStage stage) {
        switch (stage) {
            case Orbis::ShadingStage::VERTEX:   return GL_VERTEX_SHADER;
            case Orbis::ShadingStage::FRAGMENT: return GL_FRAGMENT_SHADER;
        }

        return 0;
    }
}

namespace Orbis {
    LOG_CATEGORY(Shader);

    std::shared_ptr<Shader> Shader::fromSources(const std::vector<ShaderSource>& sources) {
        Shader shader;

        shader.m_programHandle = glCreateProgram();

        std::vector<unsigned int> compiledStages;

        for (ShaderSource source : sources) {
            unsigned int stage = compileStage(source);
            compiledStages.push_back(stage);
            glAttachShader(shader.m_programHandle, stage);
        }

        glLinkProgram(shader.m_programHandle);

        for (unsigned int handle : compiledStages) {
            glDeleteShader(handle);
        }

        return std::make_shared<Shader>(shader);
    }

    unsigned int Shader::compileStage(ShaderSource source) {
        std::ifstream sourceFile;
        sourceFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        std::string sourceCode;

        try {
            sourceFile.open(source.path);

            std::stringstream sourceStream;
            sourceStream << sourceFile.rdbuf();

            sourceFile.close();

            sourceCode = sourceStream.str();
        } catch (std::ifstream::failure e) {
            LOG_ERROR(LogCatShader, "Could not read source file ", source.path);
            LOG_ERROR(LogCatShader, "Exception: ", e.what());

            if (!sourceFile.is_open()) {
                LOG_ERROR(LogCatShader, "File is not open (likely missing or wrong path)");
            } else if (sourceFile.bad()) {
                LOG_ERROR(LogCatShader, "Stream is corrupted");
            } else if (sourceFile.fail()) {
                LOG_ERROR(LogCatShader, "Logical error on i/o operation");
            }
        }

        const char* code = sourceCode.c_str();

        unsigned int handle;
        int success;
        char infoLog[512];

        handle = glCreateShader(toGL(source.stage));
        glShaderSource(handle, 1, &code, NULL);
        glCompileShader(handle);
        glGetShaderiv(handle, GL_COMPILE_STATUS, &success);

        if(!success) {
            glGetShaderInfoLog(handle, 512, NULL, infoLog);
            LOG_ERROR(LogCatShader, "Stream is corrupted\n", infoLog);
        }

        return handle;
    }

    void Shader::setUniform(const std::string& name, UniformValue value) const {
        std::visit([&](auto&& v) {
            using T = std::decay_t<decltype(v)>;

            if constexpr(std::is_same_v<T, int>)
                glUniform1i(glGetUniformLocation(m_programHandle, name.c_str()), v); 
            else if constexpr (std::is_same_v<T, float>)
                glUniform1f(glGetUniformLocation(m_programHandle, name.c_str()), v);
            else if constexpr (std::is_same_v<T, bool>)
                glUniform1i(glGetUniformLocation(m_programHandle, name.c_str()), (int)v);
            else if constexpr (std::is_same_v<T, Math::Vec3>)
                glUniform3f(glGetUniformLocation(m_programHandle, name.c_str()), v.x, v.y, v.z);
            else if constexpr (std::is_same_v<T, Math::Vec4>)
                glUniform4f(glGetUniformLocation(m_programHandle, name.c_str()), v.x, v.y, v.z, v.w);
            else if constexpr (std::is_same_v<T, Math::Mat4>)
                glUniformMatrix4fv(glGetUniformLocation(m_programHandle, name.c_str()), 1, GL_FALSE, glm::value_ptr(v)); 
        }, value);
    }

    void Shader::bind() const {
        glUseProgram(m_programHandle);
    }

    void Shader::unbind() const {
        glUseProgram(0);
    }
}
