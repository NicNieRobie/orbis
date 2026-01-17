#include "orbis/render/shading/shader.hpp"
#include "orbis/math/types.hpp"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

namespace {
    GLenum toGL(orbis::ShadingStage stage) {
        switch (stage) {
            case orbis::ShadingStage::VERTEX:   return GL_VERTEX_SHADER;
            case orbis::ShadingStage::FRAGMENT: return GL_FRAGMENT_SHADER;
        }

        return 0;
    }
}

namespace orbis {
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
            std::cout << "[INFO][SHADER] Loading shader source: " << source.path << std::endl;
            sourceFile.open(source.path);

            std::stringstream sourceStream;
            sourceStream << sourceFile.rdbuf();

            sourceFile.close();

            sourceCode = sourceStream.str();

            std::cout << "Code: " << sourceCode << "\n" << std::endl;
        } catch (std::ifstream::failure e) {
            std::cerr << "[ERROR][SHADER] Could not read source file" << std::endl;
            std::cerr << "[ERROR][SHADER] Exception: " << e.what() << std::endl;

            if (!sourceFile.is_open()) {
                std::cerr << "[ERROR][SHADER] File is not open (likely missing or wrong path)" << std::endl;
            } else if (sourceFile.bad()) {
                std::cerr << "[ERROR][SHADER] Stream is corrupted" << std::endl;
            } else if (sourceFile.fail()) {
                std::cerr << "[ERROR][SHADER] Logical error on i/o operation" << std::endl;
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
            std::cerr << "[ERROR][SHADER] Shader compilation failed\n" << infoLog << std::endl;
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
            else if constexpr (std::is_same_v<T, math::Vec3>)
                glUniform3f(glGetUniformLocation(m_programHandle, name.c_str()), v.x, v.y, v.z);
            else if constexpr (std::is_same_v<T, math::Vec4>)
                glUniform4f(glGetUniformLocation(m_programHandle, name.c_str()), v.x, v.y, v.z, v.w);
            else if constexpr (std::is_same_v<T, math::Mat4>)
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
