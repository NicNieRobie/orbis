#include <iostream>
#include <Orbis.h>

class ExampleApp : public Orbis::Application {
public:
    ExampleApp() {

    }

    ~ExampleApp() {

    }
};

Orbis::Application* Orbis::initApplication() {
    return new ExampleApp();
}
