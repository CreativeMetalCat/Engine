#pragma once
#include "Object.h"
#include "Sprite.h"

#include <Box2D.h>

#define CLASS_ACTOR 2

//Base of all objects that can be placed in the scene
class Actor : public Object
{

protected:	
	sf::Vector2f Location;	

	std::vector<std::shared_ptr<Actor>> Children;

public:
	//Physical body of the actor
	std::shared_ptr<b2Body>Body;

	//returns copy of the Array
	//Made primarly for the LUA
	std::vector<std::shared_ptr<Actor>> GetChildren()const { return Children; }
	
	//Add child to array
	//Made primarly for the LUA
	void AddChildRaw(Actor*a);

	//Add child to array
	//Made primarly for the LUA
	void AddChild(std::shared_ptr<Actor> a);

	//Get child by index
	//Made primarly for the LUA
	Actor* GetChild(unsigned int index);

	//Get child by index
	std::shared_ptr<Actor> GetChildAsSharedPtr(unsigned int index);

	//ID of parent for checking
	//default is Object
	static const int ParentClassID = CLASS_OBJECT;

	//ID of class for Casting
	//ID MUST be defined in the beggining of the file with class
	//default is Object
	static const int ClassID = CLASS_ACTOR;

	sf::Vector2f GetActorLocation() const { return Location; }

	void SetActorLocation(sf::Vector2f l) { Location = l; }

	//void SetActorLocation(float x, float y) { Location.x = x; Location.y = y; }

	virtual void Draw(sf::RenderWindow&window)
	{

	}

	//Create LUA class from this for usage in LUA
	static void RegisterClassLUA(lua_State *&L);

	Actor(sf::Vector2f Location);
	~Actor();
};

