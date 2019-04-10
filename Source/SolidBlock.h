#pragma once
#include "Actor.h"

//Actor that has one texture(sprite) and static physical body
//Category: Basic
class CSolidBlock : public CActor
{
	sf::Sprite sprite;

	sf::Vector2f Size;


public:

	sf::ConvexShape CollisionShape;

	void SetSprite(sf::Sprite s) { this->sprite = s; }

	sf::Sprite GetSprite()const { return sprite; }

	void SetSpriteTexture(sf::Texture & texture);

	virtual void Init(std::string path)override;
	virtual void InitPhysBody(std::string path, b2World &world);

	void Draw(sf::RenderWindow&window)override;

	CSolidBlock(sf::Texture&texture, sf::ConvexShape CollisionShape, sf::Vector2f Size, sf::Vector2f Location, std::string path = "./../");
	~CSolidBlock();
};

