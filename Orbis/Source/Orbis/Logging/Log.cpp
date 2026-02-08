#include "Log.h"

#include "quill/Backend.h"
#include "quill/Frontend.h"
#include "quill/LogMacros.h"
#include "quill/Logger.h"
#include "quill/sinks/ConsoleSink.h"

namespace Orbis {
    quill::Logger* Log::s_logger{nullptr};

    void Log::init() {
        quill::Backend::start();

        auto consoleSink = quill::Frontend::create_or_get_sink<quill::ConsoleSink>("console_sink");
        s_logger = quill::Frontend::create_or_get_logger(
            "Orbis",
            std::move(consoleSink),
            quill::PatternFormatterOptions{"%(time) [%(thread_id)] %(log_level) %(message)", "%H:%M:%S"});

        s_logger->set_log_level(quill::LogLevel::Debug);

        LOG_INFO(s_logger, "Logger initialized");
    }
}
