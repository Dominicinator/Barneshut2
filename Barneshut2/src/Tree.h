#pragma once
#include "Node.h"
#include "Util.h"
class Tree
{
public:
	Node* root;
	Tree();
	virtual ~Tree();

	void clear();
	void fit(Particle* const& particles, const int& nParticles);
	void fill(Particle* const& particles, const int& nParticles);

	vec2f getForce(const vec2f & pos);
	vec2f _getForce(Node* const & node, const vec2f & pos);
	
	void update(const Particle & particle);

};

