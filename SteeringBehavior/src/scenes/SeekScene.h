#pragma once
#include "Scene.h"

class Vehicle;

class SeekScene:public Scene
{
private:
    sf::RenderWindow& window_;
    sf::Vector2i mousePosition_;
    sf::CircleShape cursorShape_;

	Vehicle* vehicle_;

public:
    SeekScene(sf::RenderWindow& window);
    ~SeekScene() override;

    void handleInput(sf::Event event) override;
    void update(sf::Time deltaTime) override;
    void render(sf::RenderWindow& window) override;

    void updateCursor();
};

