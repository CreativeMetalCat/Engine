#include "SolidBlock.h"

void CSolidBlock::SetSpriteTexture(sf::Texture & texture)
{

}

void CSolidBlock::Init(std::string path)
{

	sf::Vector2f scale;

	if (this->sprite.getTexture()->getSize().x != 0) { scale.x = Size.x / this->sprite.getTexture()->getSize().x; }

	if (this->sprite.getTexture()->getSize().y != 0) { scale.y = Size.y / this->sprite.getTexture()->getSize().y; }

	this->sprite.setScale(scale);
	this->sprite.setPosition(this->GetActorLocation());
}

void CSolidBlock::InitPhysBody(std::string path, b2World & world)
{

	b2BodyDef defP;
	defP.type = b2BodyType::b2_staticBody;
	defP.position.Set(Location.x + Size.x / 2, Location.y + Size.y / 2);

	this->Body = world.CreateBody(&defP);

	b2PolygonShape shape;
	if (CollisionShape.getPointCount() > 0)
	{
		shape.m_count = CollisionShape.getPointCount();
		for (int i = 0; i < CollisionShape.getPointCount(); i++)
		{
			shape.m_vertices[i].Set(CollisionShape.getPoint(i).x, CollisionShape.getPoint(i).y);
		}

	}


	b2FixtureDef TriggerFixtureP;
	TriggerFixtureP.density = 1.f;
	TriggerFixtureP.shape = &shape;
	TriggerFixtureP.density = 1.f;

	TriggerFixtureP.isSensor = false;

	this->Body->CreateFixture(&TriggerFixtureP);
	this->Body->SetUserData(this);
}

void CSolidBlock::Draw(sf::RenderWindow & window)
{
	window.draw(sprite);
}

CSolidBlock::CSolidBlock(sf::Texture&texture, sf::ConvexShape CollisionShape, sf::Vector2f Size, sf::Vector2f Location, std::string path ):CActor(Location,path),Size(Size),CollisionShape(CollisionShape)
{
	this->sprite = sf::Sprite(texture);
	//this->sprite.setScale(scale);
}




CSolidBlock::~CSolidBlock()
{
}
