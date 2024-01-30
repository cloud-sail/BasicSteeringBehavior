#pragma once
#include <SFML/Graphics.hpp>
#include "scenes/Scene.h"

class SceneManager {
private:
    std::map<std::string, std::unique_ptr<Scene>> scenes_;
    Scene* currentScene_;

public:
    SceneManager();
    void addScene(const std::string& name, std::unique_ptr<Scene> scene);
    void switchTo(const std::string& name);
    void handleInput(sf::Event event);
    void update(sf::Time deltaTime);
    void render(sf::RenderWindow& window);
};

namespace SceneName {
    const std::string SEEK = "seek";
    const std::string FLEE = "flee";
    const std::string ARRIVE = "arrive";

}
