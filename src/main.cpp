#include <iostream>
#include <vector>
#include <memory>

#include <event.hpp>
#include <world.hpp>

class DataComponent : public Component {
    std::string str;
public:
    Event<const std::string&> print_event;

    DataComponent(const std::string&& str) : str(std::move(str)) {}

    void process(Entity& entity) override {
        print_event.trigger(str);
    }
};

class HelloWorldComponent : public Component {
public:
    void added_to_entity(Entity& entity) {
        auto& data_component = entity.get_component<DataComponent>();
        data_component.print_event.subscribe(BIND_EVENT_CALLBACK(print));
    }

    void print(const std::string& str) {
        std::cout << "Hi " << str << std::endl;
    }
};

int main() {
    World world;

    world.add_entity_with_component<DataComponent>("x3").add_component<HelloWorldComponent>();

    while (true) {
        world.process();
    }

    return 0;
};
