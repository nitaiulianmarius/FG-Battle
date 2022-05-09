#ifndef BULLET_H
#define BULLET_H

#include<SFML/Graphics.hpp>

class Bullet2d
{
public:

	bool existaDestinatie;
	float v;
	float vx, vy;
	float l;
	int t;

	sf::Vector2f normalized;
	sf::Vector2f ABvector;
	sf::Vector2f position;
	sf::Vector2f A, B;
};

#endif