#pragma once
#include "Object.h"
#include "Sprite.h"

#ifndef BOX2D_H
#include <Box2D.h>
#endif

#define CLASS_ACTOR 2

//Base of all objects that can be placed in the scene
class Actor : public Object
{

protected:	
	sf::Vector2f Location;	

	std::vector<std::shared_ptr<Actor>> Children;

	//is set manually or by some function in children class
	//unnessesary if alternative already exists
	bool physBodyInitialized = false;

	//it's id that is usually assinged by layer on the map 
	//needed for the optimization
	int area_id = 0;
public:
	void SetAreaId(int id) { area_id = id; }

	int GetAreaId()const { return area_id; }

	
	bool GetPhysBodyInitialized()const { return physBodyInitialized; }
	
	void SetPhysBodyInitialized(bool is) { physBodyInitialized = is; }

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

	//PATH - Path to main folder and usually used to access scripts
	//Defined by window.lua
	virtual void OnBeginCollision(std::shared_ptr<Object> otherActor, b2Fixture *fixtureA, b2Fixture *fixtureB, std::string PATH);

	//PATH - Path to main folder and usually used to access scripts
	//Defined by window.lua
	virtual void OnEndCollision(std::shared_ptr<Actor> otherActor, b2Fixture *fixtureA, b2Fixture *fixtureB, std::string PATH);

	Actor(sf::Vector2f Location);
	~Actor();
};

