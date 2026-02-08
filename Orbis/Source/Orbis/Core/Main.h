#pragma once

#include "Application.h"
#include "Logging/Log.h"

namespace Orbis {
    extern Application* initApplication();
}

int main(int argc, char** argv) {
    Orbis::Log::init();

    auto app = Orbis::initApplication();
    app->run();
    delete app;
}
