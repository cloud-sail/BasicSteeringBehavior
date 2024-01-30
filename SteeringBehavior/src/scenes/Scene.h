#pragma once
#include <SFML/Graphics.hpp>


class Scene {
public:
    virtual ~Scene() = default;
    virtual void handleInput(sf::Event event) = 0;
    virtual void update(sf::Time deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
};
