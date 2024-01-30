#pragma once
#include <SFML/Graphics.hpp>

namespace Vector2DUtility {
	constexpr const float TOLERANCE = 1e-5f;

	inline void confine(sf::Vector2f& pos, float maxX, float maxY)
	{
        if (pos.x > maxX) { pos.x = 0.0f; }
        if (pos.x < 0) { pos.x = maxX; }
        if (pos.y < 0) { pos.y = maxY; }
        if (pos.y > maxY) { pos.y = 0.0f; }
	}


	inline float magnitude(const sf::Vector2f& v)
	{
		return std::sqrt(v.x * v.x + v.y * v.y);
	}

	inline sf::Vector2f normalize(const sf::Vector2f& v)
	{
		float len = magnitude(v);
		if (len > TOLERANCE)
		{
			return sf::Vector2f(v.x / len, v.y / len);
		}
		return sf::Vector2f(0.0f, 0.0f);
	}

	inline sf::Vector2f truncate(const sf::Vector2f& v, float max)
	{
		if (magnitude(v) > max)
		{
			return normalize(v) * max;
		}
		return v;
	}

	inline float distance(const sf::Vector2f& v1, const sf::Vector2f& v2)
	{
		return magnitude(v1 - v2);
	}
}
