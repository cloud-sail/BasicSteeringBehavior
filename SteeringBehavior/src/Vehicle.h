#pragma once
#include <SFML/Graphics.hpp>

#include "SteeringManager.h"


class SteeringManager;

class Vehicle
{
private:
    sf::RenderWindow& window_;
    sf::Vector2f position_;
    sf::Vector2f velocity_;
    sf::Vector2f direction_;
    float maxSpeed_;
    float maxForce_;
    float mass_;
    float timeElapsed_;

    sf::Vector2f target_;

    sf::ConvexShape triangle_;

public:
    sf::Vector2f getPosition() const { return position_; }
    sf::Vector2f getVelocity() const { return velocity_; }
    sf::Vector2f getDirection() const { return direction_; }

    float getMaxSpeed() const { return maxSpeed_; }
    void setMaxSpeed(float s) { maxSpeed_ = s; }
    float getMaxForce() const { return maxForce_; }
    void setMaxForce(float f) { maxForce_ = f; }
    float getMass() const { return mass_; }
    void setMass(float m) { mass_ = m; }

    float getTimeElapsed() { return timeElapsed_; }

    sf::Vector2f getTarget() const { return target_; }
    void setTarget(const sf::Vector2f& tgt) { target_ = tgt; }

private:
    SteeringManager* steering_;

public:
    Vehicle(sf::Vector2f pos, float m, sf::RenderWindow& window);
    ~Vehicle();

    void update(sf::Time deltaTime);
    void render();

    void setMode(SteeringManager::Mode mode);
};

