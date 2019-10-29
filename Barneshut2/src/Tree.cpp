#include "Tree.h"



Tree::Tree()
{
	root = new Node;
}


Tree::~Tree()
{
	delete root;
}

void Tree::clear()
{
	if (root->isInternal())
		for (auto child : root->children)
			delete child;
}

void Tree::fit(Particle * const & particles, const int & nParticles)
{
	vec2f position(0.0f, 0.0f);
	float size = 0.0f;
	//Calculate average position
	for (int i = 0; i < nParticles; ++i)
		position += particles[i].position;
	position /= nParticles;
	//Calculate size
	for (int i = 0; i < nParticles; ++i) {
		float mag = (particles[i].position - position).mag();
		size = mag > size ? mag : size;
	}
	size *= 2;

	root->position = position;
	root->size = size;

}

void Tree::fill(Particle * const & particles, const int & nParticles)
{
	fit(particles, nParticles);
	for (int i = 0; i < nParticles; ++i)
		root->insert(&particles[i]);
	
}

vec2f Tree::getForce(const vec2f & pos)
{
	return _getForce(root, pos);
}

vec2f Tree::_getForce(Node * const & node, const vec2f & pos)
{
	if (!node->isInternal()) { //Node is External
		if (node->isEmpty()) //External node is empty
			return vec2f(0.0f, 0.0f);
		else {//External node is not empty
			if (node->particle->position == pos) {//Avoid 0 distance when comparing a particle to itself
				return vec2f(0.0f, 0.0f);
			}
			vec2f distanceVector = node->particle->position - pos;
			return distanceVector.norm()*(Units::G*node->particle->mass / (distanceVector.mag2()));
		}
	}
	else { //Node is internal
		vec2f force;
		vec2f distanceVector = node->CoMPosition - pos;
		float d2 = distanceVector.mag2();
		float d = std::sqrt(d2);
		if ((node->size) / d < 0.5f) {// ratio s/d is within threshhold; approximate using center of mass
			//vec2f norm = (distanceVector / d);
			return (distanceVector / d) * (Units::G * node->containedMass / d2);
		}
		else {// ratio s/d outside threshhold; continue recursing
			for (auto child : node->children) {
				force += _getForce(child, pos);
			}
			return force;
		}
	}
}

void Tree::update(const Particle & particle)
{

}
