#include "SteeringManager.h"

#include "Vector2DUtility.h"
#include "Vehicle.h"

void SteeringManager::enableMode(Mode mode)
{
	modes_ |= mode;
}

void SteeringManager::disableMode(Mode mode)
{
	modes_ &= ~mode;
}

bool SteeringManager::isModeEnabled(Mode mode) const
{
	return modes_ & mode;
}

SteeringManager::SteeringManager(Vehicle* v, sf::RenderWindow& window): vehicle_(v), window_(window), steering_()
{
	targetLine_ = sf::VertexArray(sf::Lines, 2);
	targetLine_[0].position = sf::Vector2f(0.0f, 0.0f);
	targetLine_[0].color = sf::Color::Red;
	targetLine_[1].position = sf::Vector2f(0.0f, 0.0f);
	targetLine_[1].color = sf::Color::Red;
}

void SteeringManager::render()
{
	// line between target
	targetLine_[0].position = vehicle_->getTarget();
	targetLine_[1].position = vehicle_->getPosition();
	window_.draw(targetLine_);

	// Flee radius
	if (isModeEnabled(FLEE))
	{
		sf::CircleShape circle(FLEE_RADIUS);
		circle.setOutlineColor(sf::Color::Blue);
		circle.setOutlineThickness(5);
		circle.setFillColor(sf::Color::Transparent);
		circle.setPosition(vehicle_->getPosition().x - FLEE_RADIUS, vehicle_->getPosition().y - FLEE_RADIUS);
		window_.draw(circle);
	}

	// Slowing radius
	if (isModeEnabled(ARRIVE))
	{
		sf::CircleShape circle(ARRIVE_RADIUS);
		circle.setOutlineColor(sf::Color::Blue);
		circle.setOutlineThickness(3);
		circle.setFillColor(sf::Color::Transparent);
		circle.setPosition(vehicle_->getTarget().x - ARRIVE_RADIUS, vehicle_->getTarget().y - ARRIVE_RADIUS);
		window_.draw(circle);
	}

}

sf::Vector2f SteeringManager::calculate()
{
	steering_ = sf::Vector2f();

	if (isModeEnabled(SEEK))
	{
		steering_ += seek(vehicle_->getTarget());
	}
	if (isModeEnabled(FLEE))
	{
		steering_ += flee(vehicle_->getTarget());
	}
	if (isModeEnabled(ARRIVE))
	{
		steering_ += arrive(vehicle_->getTarget());
	}


	return Vector2DUtility::truncate(steering_, vehicle_->getMaxForce());
}

sf::Vector2f SteeringManager::seek(sf::Vector2f targetPos)
{
	sf::Vector2f desiredVelocity = Vector2DUtility::normalize(targetPos - vehicle_->getPosition())*vehicle_->getMaxSpeed();
	return (desiredVelocity - vehicle_->getVelocity());
}

sf::Vector2f SteeringManager::flee(sf::Vector2f targetPos)
{
	if (Vector2DUtility::distance(targetPos, vehicle_->getPosition())> FLEE_RADIUS)
	{
		return sf::Vector2f();
	}
	sf::Vector2f desiredVelocity = Vector2DUtility::normalize(vehicle_->getPosition() - targetPos) * vehicle_->getMaxSpeed();
	return (desiredVelocity - vehicle_->getVelocity());
}

sf::Vector2f SteeringManager::arrive(sf::Vector2f targetPos)
{
	sf::Vector2f desiredVelocity = targetPos - vehicle_->getPosition();
	float distance = Vector2DUtility::magnitude(desiredVelocity);

	if (distance < ARRIVE_RADIUS)
	{
		desiredVelocity = Vector2DUtility::normalize(desiredVelocity) * vehicle_->getMaxSpeed() * distance / ARRIVE_RADIUS;
	} else
	{
		desiredVelocity = Vector2DUtility::normalize(desiredVelocity) * vehicle_->getMaxSpeed();
	}
	return (desiredVelocity - vehicle_->getVelocity()) * 2.f;
}
