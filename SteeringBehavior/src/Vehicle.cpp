#include "Vehicle.h"
#include "SteeringManager.h"
#include <cmath>

#include "Vector2DUtility.h"

Vehicle::Vehicle(sf::Vector2f pos, float m, sf::RenderWindow& window):
	window_(window), position_(pos), velocity_(),
	direction_(1.0f,.0f),maxSpeed_(100.0f), maxForce_(100.0f),
	mass_(m), timeElapsed_(0.f),target_()
{
	steering_ = new SteeringManager(this, window);

    triangle_.setPointCount(3);
    triangle_.setPoint(0, sf::Vector2f(10, 0));
    triangle_.setPoint(1, sf::Vector2f(-5, -5));
    triangle_.setPoint(2, sf::Vector2f(-5, 5));
    triangle_.setOutlineColor(sf::Color::Blue);
    triangle_.setOutlineThickness(1); 
    triangle_.setFillColor(sf::Color::Transparent);
}

Vehicle::~Vehicle()
{
	delete steering_;
}

void Vehicle::update(sf::Time deltaTime)
{
    timeElapsed_ = deltaTime.asSeconds();
    sf::Vector2f steeringForce = steering_->calculate();
    velocity_ += steeringForce / mass_ * timeElapsed_;
    velocity_ = Vector2DUtility::truncate(velocity_, maxSpeed_);

    position_ += velocity_ * timeElapsed_;
    Vector2DUtility::confine(position_, window_.getSize().x, window_.getSize().y);

    if (Vector2DUtility::magnitude(velocity_)> Vector2DUtility::TOLERANCE)
    {
        direction_ = Vector2DUtility::normalize(velocity_);
    }

}

void Vehicle::render()
{
    // render vehicle
    triangle_.setPosition(position_);
    triangle_.setRotation(atan2(direction_.y, direction_.x) * 180.0f / 3.14159265358f);
    window_.draw(triangle_);
    // render help lines
    steering_->render();
}

void Vehicle::setMode(SteeringManager::Mode mode)
{
    steering_->enableMode(mode);
}
