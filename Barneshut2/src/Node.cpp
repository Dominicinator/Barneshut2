#include "Node.h"



bool Node::isEmpty()
{
	return particle == nullptr;
}

bool Node::isFull()
{
	return particle != nullptr;
}

bool Node::isInternal()
{
	return children[0] != nullptr;
}

bool Node::isExternal()
{
	return children[0] == nullptr;
}

bool Node::contains(Particle * p)
{
	return (p->position - position).abs() < size/2;
}

Node::Node() : parent(nullptr) {}

Node::Node(Node * const & parent, vec2f const & position, float const & size) 
	: parent(parent), position(position), size(size) {}


Node::~Node()
{
	if (isInternal())
		for (auto child : children)
			delete child;
}

void Node::updateCoM(const vec2f& pos, const float& m)
{
	//avg(i) = (i-1)/i*avg(i-1) + x(i)/i;    (i > 1)
	if (nParticles > 0) {
		float n = (float)nParticles;
		//vec2f half = CoMPosition * (n / (n + 1));
		//vec2f otherHalf = pos / (n + 1);
		CoMPosition = CoMPosition * (n / (n + 1)) + pos / (n + 1);
		containedMass += m;
		nParticles++;
	}
	else {
		CoMPosition = pos; 
		containedMass = m;
		nParticles++;
	}
}

void Node::insert(Particle * p)
{
	if (!contains(p))
		return;
	updateCoM(p->position, p->mass);
	if (isEmpty()) {
		if (isInternal()) {
			for (auto child : children)
				child->insert(p);
		}
		else {
			particle = p;
		}
	}
	else {
		if (p->position == particle->position) {
			std::cout << "Inserting particle into node which contains a particle with the same position\n";
			return;
		}
		subdivide();
		for (auto child : children) {
			child->insert(p);
			child->insert(particle);
		}
		particle = nullptr;
	}
}

void Node::subdivide()
{
	children[0] = new Node(this, position - vec2f(-size / 4, size / 4), size / 2);
	//NE
	children[1] = new Node(this, position - vec2f(size / 4, size / 4), size / 2);
	//SW
	children[2] = new Node(this, position - vec2f(-size / 4, -size / 4), size / 2);
	//SE
	children[3] = new Node(this, position - vec2f(size / 4, -size / 4), size / 2);
}

void Node::draw(sf::RenderWindow & targetWindow)
{
	sf::RectangleShape rect(sf::Vector2f(size, size));
	rect.setOrigin(size / 2, size / 2);
	rect.setPosition(position.x, position.y);
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineColor(sf::Color::Green);
	rect.setOutlineThickness(1.0f);
	targetWindow.draw(rect);

	if (isInternal()) 
		for (auto child : children)
			child->draw(targetWindow);
}
