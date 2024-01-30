#pragma once
#include "Scene.h"

class Vehicle;

class FleeScene :public Scene
{
private:
    sf::RenderWindow& window_;
    sf::Vector2i mousePosition_;
    sf::CircleShape cursorShape_;

    Vehicle* vehicle_;

public:
    FleeScene(sf::RenderWindow& window);
    ~FleeScene() override;

    void handleInput(sf::Event event) override;
    void update(sf::Time deltaTime) override;
    void render(sf::RenderWindow& window) override;

    void updateCursor();
};

