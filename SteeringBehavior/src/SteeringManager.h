#pragma once
#include <SFML/Graphics.hpp>
class Vehicle;

class SteeringManager {
public:
    enum Mode {
        SEEK     = 1 << 0, // 1
        FLEE     = 1 << 1, // 2
        ARRIVE   = 1 << 2, // 4
        WANDER   = 1 << 3, // 8
		PERSUIT  = 1 << 4, // 16
    };

    // enable or disable steering behaviors
    void enableMode(Mode mode);
    void disableMode(Mode mode);
    bool isModeEnabled(Mode mode) const;

private:
    int modes_ = 0;
    const float FLEE_RADIUS = 200.f;
    const float ARRIVE_RADIUS = 100.f;

    Vehicle* vehicle_;
    sf::RenderWindow& window_;

    sf::VertexArray targetLine_;

    sf::Vector2f steering_;

public:
    SteeringManager(Vehicle* v, sf::RenderWindow& window);

    void render();

    sf::Vector2f calculate();
private:
    sf::Vector2f seek(sf::Vector2f targetPos);
    sf::Vector2f flee(sf::Vector2f targetPos);
    sf::Vector2f arrive(sf::Vector2f targetPos);
};

