#pragma once

#include "Core/API.h"

namespace Orbis {
    class ORBIS_API Application {
    public:
        Application();
        virtual ~Application();

        void run();
    };
}