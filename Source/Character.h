#pragma once
#include "Actor.h"

//base class for the Charaters,that defines basic movement using Box2D's physics and LUA as well as basic collision
class Character : public CActor
{
protected:
	sf::Vector2f MaxVelocity = sf::Vector2f(500, 500);

	//LUA script file that will be used for movement
	//it is not obligatory to use LUA script
	std::string MovementScriptFileName="character.lua";

	sf::Vector2f Size;

	
public:

	bool IsMovingX = false;

	bool IsMovingY = false;

	

	sf::ConvexShape CollisionShape;

	//LUA script file that will be used for movement
	//it is not obligatory to use LUA script
	void SetMovementScriptFileName(std::string f) { MovementScriptFileName = f; }

	//LUA script file that will be used for movement
	//it is not obligatory to use LUA script
	std::string GetMovementScriptFileName()const { return MovementScriptFileName; }

	sf::Vector2f GetMaxVelocity()const { return MaxVelocity; }

	void SetMaxVelocity(sf::Vector2f v) { this->MaxVelocity = v; }

	sf::Vector2f GetLinearVelocity()const
	{
		return sf::Vector2f(Body->GetLinearVelocity().x, Body->GetLinearVelocity().y);
	}

	void ApplyLinearImpulse(b2Vec2 vel)
	{
		Body->ApplyLinearImpulseToCenter(vel,true);
		//Body->SetLinearVelocity(vel);
	}
	inline void MoveX(float value);

	DEPRECATED_ERROR inline void MoveY(float value);

	virtual void Init(std::string path);
	virtual void InitPhysBody(std::string path,b2World &world);

	//Create LUA class from this for usage in LUA
	static void RegisterClassLUA(lua_State *&L);

	void Update(sf::Time dt);
	Character(sf::ConvexShape CollisionShape, sf::Vector2f Size, sf::Vector2f Location, std::string path="./../");
	~Character();
};

