#pragma once

#include <fstream>
#include <string>
#include <mutex>
#include <ctime>
#include <sstream>
#include <iostream>
#include <glad/glad.h>

namespace orbis {
    enum class LogLevel { INFO, WARNING, ERROR, DEBUG };

    class Logger {
    public:
        static Logger& getInstance() {
            static Logger instance;
            return instance;
        }

        void setLogFile(const std::string& filename) {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_file.open(filename, std::ios::out | std::ios::app);
            if (!m_file.is_open())
                std::cerr << "[LOGGER] Failed to open log file: " << filename << std::endl;
        }

        template<typename... Args>
        void log(LogLevel level, const std::string& category, Args&&... args) {
            std::lock_guard<std::mutex> lock(m_mutex);

            std::ostringstream msgStream;
            (msgStream << ... << std::forward<Args>(args));

            std::ostringstream logStream;
            logStream << "[" << getTimestamp() << "] "
                      << "[" << logLevelToString(level) << "] "
                      << "[" << category << "] "
                      << msgStream.str();

            std::cout << colorCode(level) << logStream.str() << "\033[0m" << std::endl;
            if (m_file.is_open())
                m_file << logStream.str() << std::endl;
        }

        void checkGLError(const char* file, int line) {
            GLenum err;
            while ((err = glGetError()) != GL_NO_ERROR) {
                log(LogLevel::ERROR, "OpenGL Error: ", glErrorToString(err), " (", file, ":", line, ")");
            }
        }

    private:
        Logger() = default;
        ~Logger() { if (m_file.is_open()) m_file.close(); }
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;

        inline std::string logLevelToString(LogLevel level) {
            switch (level) {
                case LogLevel::INFO: return "INFO";
                case LogLevel::WARNING: return "WARNING";
                case LogLevel::ERROR: return "ERROR";
                case LogLevel::DEBUG: return "DEBUG";
            }
            return "UNKNOWN";
        }

        inline std::string colorCode(LogLevel level) {
            switch (level) {
                case LogLevel::INFO: return "\033[32m";
                case LogLevel::WARNING: return "\033[33m";
                case LogLevel::ERROR: return "\033[31m";
                case LogLevel::DEBUG: return "\033[36m";
            }
            return "\033[0m";
        }

        inline std::string getTimestamp() {
            std::time_t now = std::time(nullptr);
            char buf[20];
            std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
            return buf;
        }

        inline std::string glErrorToString(GLenum err) {
            switch (err) {
                case GL_NO_ERROR: return "GL_NO_ERROR";
                case GL_INVALID_ENUM: return "GL_INVALID_ENUM";
                case GL_INVALID_VALUE: return "GL_INVALID_VALUE";
                case GL_INVALID_OPERATION: return "GL_INVALID_OPERATION";
                case GL_STACK_OVERFLOW: return "GL_STACK_OVERFLOW";
                case GL_STACK_UNDERFLOW: return "GL_STACK_UNDERFLOW";
                case GL_OUT_OF_MEMORY: return "GL_OUT_OF_MEMORY";
                case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";
            }
            return "Unknown OpenGL Error";
        }

        std::ofstream m_file;
        std::mutex m_mutex;
    };

    #define LOG_CATEGORY(name) static constexpr const char* LogCat##name = #name;

    #define LOG_INFO(cat, ...) Logger::getInstance().log(LogLevel::INFO, cat, __VA_ARGS__)
    #define LOG_WARN(cat, ...) Logger::getInstance().log(LogLevel::WARNING, cat, __VA_ARGS__)
    #define LOG_ERROR(cat, ...) Logger::getInstance().log(LogLevel::ERROR, cat, __VA_ARGS__)
    #define LOG_DEBUG(cat, ...) Logger::getInstance().log(LogLevel::DEBUG, cat, __VA_ARGS__)
    #define GL_CHECK() Logger::getInstance().checkGLError(__FILE__, __LINE__)
}
