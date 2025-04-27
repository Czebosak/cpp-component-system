#include <iostream>
#include <vector>
#include <memory>

#include <world.hpp>

class DataComponent : public Component {
public:
    std::string x = "hi brotha";
};

class HelloWorldComponent : public Component {
public:
    void process(Entity& entity) override {
        auto& component = entity.get_component<DataComponent>();

        std::cout << "Hi " << component.x << std::endl;
    }
};

int main() {
    World world;

    std::vector<std::unique_ptr<Component>> components;
    components.emplace_back(std::make_unique<HelloWorldComponent>());
    components.emplace_back(std::make_unique<DataComponent>());

    world.add_entity_with_components(std::move(components));

    while (true) {
        world.process();
    }

    return 0;
};
