#include "Node.h"
int main()
{
	Node node(nullptr, vec2f(0.0f, 0.0f), 50);
	Particle p(vec2f(0.5f, 0.5f), 1);
	std::cout << node.isEmpty() << "\n"; // should be 1
	std::cout << node.isInternal() << "\n"; // 0
	node.insert(&p);
	std::cout << node.isEmpty() << "\n"; // 0
	std::cout << node.isInternal() << "\n"; // 0

	Particle p2(vec2f(-0.5f, -0.5f), 1);
	node.insert(&p2);
	std::cout << node.CoMPosition << "\n";
	std::cout << node.containedMass << "\n";

	Particle p3(vec2f(-6.0f, -6.0f), 3);
	node.insert(&p3);
	
	sf::RenderWindow window(sf::VideoMode(800, 800), "My window");
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(800, 800));

	
	while (window.isOpen())
	{
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			
			if (event.type == sf::Event::Closed)
				window.close();
		}
		sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(window) - sf::Vector2f(400.0f, 400.0f);
		vec2f mouse = vec2f(mousePos.x, mousePos.y);
		//std::cout << node.contains(&Particle(mouse, 1.0f));
		window.setView(view);
		window.clear(sf::Color::Black);

		node.draw(window);

		window.display();
	}
	//window.
	
	
	return 0;
}