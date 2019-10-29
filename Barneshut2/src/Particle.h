#pragma once
#include "vector.h"
#include <SFML/Graphics.hpp>
class Particle
{
public:
	vec2f position;
	float mass;
	vec2f velocity;
	Particle();
	Particle(vec2f position, float mass);
	virtual ~Particle();

	//void update(const Tree & tree, const float & dt);
	void draw(sf::RenderWindow targetWindow);
};