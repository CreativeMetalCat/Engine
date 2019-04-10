#pragma once

#include "Character.h"

//Example player that moves using physics and has one sprite 
//Category: Test-Basic
class CTestPlayer : public Character
{

	sf::Sprite sprite;
public:

	void SetSprite(sf::Sprite s) { this->sprite = s; }

	sf::Sprite GetSprite()const { return sprite; }

	void SetSpriteTexture(sf::Texture & texture);

	//Size and Location will also be used to define size of the sprite
	//Scales image inside of this funtion
	//AND does the same in the Init
	CTestPlayer(sf::Texture&texture, sf::ConvexShape CollisionShape, sf::Vector2f Size, sf::Vector2f Location, std::string path = "./../");

	virtual void Init(std::string path)override;
	virtual void InitPhysBody(std::string path, b2World &world)override;
	
	~CTestPlayer();
};

