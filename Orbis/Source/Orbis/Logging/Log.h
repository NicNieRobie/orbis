#pragma once

#include "quill/Logger.h"

#include "Core/API.h"

namespace Orbis {
    class ORBIS_API Log {
    public:
        static void init();

        static quill::Logger* getLogger() { return s_logger; }
    private:
        static quill::Logger* s_logger;
    };
}
