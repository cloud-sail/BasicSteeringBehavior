#include "FleeScene.h"
#include "../Vehicle.h"

FleeScene::FleeScene(sf::RenderWindow& window) : window_(window)
{
	// cursor
	cursorShape_.setRadius(4);
	cursorShape_.setOutlineThickness(2);
	cursorShape_.setOutlineColor(sf::Color::Red);
	cursorShape_.setFillColor(sf::Color::Transparent);
	cursorShape_.setOrigin(4, 4);

	// Vehicle
	vehicle_ = new Vehicle(sf::Vector2f(200.f, 200.f), 1.f, window);
	vehicle_->setMode(SteeringManager::Mode::FLEE);
}

FleeScene::~FleeScene()
{
	delete vehicle_;
}

void FleeScene::handleInput(sf::Event event)
{
}

void FleeScene::update(sf::Time deltaTime)
{
	updateCursor();
	vehicle_->setTarget(cursorShape_.getPosition());
	vehicle_->update(deltaTime);
}

void FleeScene::render(sf::RenderWindow& window)
{
	window.clear(sf::Color::White);
	window.draw(cursorShape_);
	vehicle_->render();
}

void FleeScene::updateCursor()
{
	mousePosition_ = sf::Mouse::getPosition(window_);
	sf::Vector2u windowSize = window_.getSize();
	const int radius = static_cast<int>(cursorShape_.getRadius());
	mousePosition_.x = std::max(radius, std::min(static_cast<int>(windowSize.x) - radius, mousePosition_.x));
	mousePosition_.y = std::max(radius, std::min(static_cast<int>(windowSize.y) - radius, mousePosition_.y));

	cursorShape_.setPosition(static_cast<sf::Vector2f>(mousePosition_));
}
