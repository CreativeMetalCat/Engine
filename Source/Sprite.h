#pragma once
#include <SFML/Graphics.hpp>

//class that includes sf::Sprite and handles animations etc.
class Sprite
{
	sf::Sprite sprite;
public:
	
	//Sprite that should be used by Owner
	//defined by animtion or any other way that should be used
	const sf::Sprite GetSprite() { return sprite; }

	void SetSprite(sf::Sprite) { this->sprite = sprite; }

	Sprite();
	~Sprite();
};

