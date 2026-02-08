#pragma once

#include "Log.h"

#define QUILL_DISABLE_NON_PREFIXED_MACROS

#include "quill/LogMacros.h"

#define LOG_DEBUG(fmt, ...) QUILL_LOG_DEBUG(Log::getLogger(), fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...) QUILL_LOG_INFO(Log::getLogger(), fmt, ##__VA_ARGS__)
#define LOG_WARNING(fmt, ...) QUILL_LOG_WARNING(Log::getLogger(), fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) QUILL_LOG_ERROR(Log::getLogger(), fmt, ##__VA_ARGS__)
#define LOG_FATAL(fmt, ...) QUILL_LOG_CRITICAL(Log::getLogger(), fmt, ##__VA_ARGS__)
