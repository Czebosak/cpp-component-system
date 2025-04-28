#include <iostream>
#include <vector>
#include <memory>

#include <world.hpp>

class DataComponent : public Component {
    std::string x = "hi brotha";
public:
    DataComponent(std::string&& x) : x(x) {}

    std::string& get_x() {
        return x;
    }
};

class HelloWorldComponent : public Component {
public:
    void process(Entity& entity) override {
        auto& component = entity.get_component<DataComponent>();

        std::cout << "Hi " << component.get_x() << std::endl;
    }
};

int main() {
    World world;

    world.add_entity_with_component<HelloWorldComponent>().add_component<DataComponent>("x3");

    while (true) {
        world.process();
    }

    return 0;
};
