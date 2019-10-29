#pragma once

#include "Particle.h"



struct CoM 
{

};


class Node
{
public:
	Particle* particle;
	Node* parent;
	Node* children[4] = { nullptr, nullptr, nullptr, nullptr };

	vec2f position;
	float size;

	unsigned int nParticles = 0;
	float containedMass;
	vec2f CoMPosition;

	//Self Checks
	bool isEmpty();
	bool isFull();
	bool isInternal();
	bool isExternal();
	
	bool contains(Particle* p);

	//Create empty root node
	Node();
	//
	Node(Node* const & parent, vec2f const & position, float const & size);
	//Recursively destroy this node and all of its children
	virtual ~Node();

	//Functions
	void updateCoM(const vec2f& pos, const float& m);
	void insert(Particle* p);
	void subdivide();
	void draw(sf::RenderWindow & targetWindow);
};

