#pragma once
#include "Object.h"
#include "Sprite.h"

#ifndef BOX2D_H
#include <Box2D.h>
#endif

#define CLASS_ACTOR 2

//Base of all objects that can be placed in the scene
class CActor : public CObject
{

protected:	
	sf::Vector2f Location;	

	std::vector<std::shared_ptr<CActor>> Children;

	//is set manually or by some function in children class
	//unnessesary if alternative already exists
	bool physBodyInitialized = false;

	//it's id that is usually assinged by layer on the map 
	//needed for the optimization
	int area_id = 0;

	//LUA file that will be used
	std::string CollisionScriptFileName;
public:
	//LUA file that will be used
	void SetCollisionScriptFileName(std::string CollisionScriptFileName) { this->CollisionScriptFileName = CollisionScriptFileName; }

	//LUA file that will be used
	std::string GetCollisionScriptFileName()const { return CollisionScriptFileName; }

	void SetAreaId(int id) { area_id = id; }

	int GetAreaId()const { return area_id; }

	
	bool GetPhysBodyInitialized()const { return physBodyInitialized; }
	
	void SetPhysBodyInitialized(bool is) { physBodyInitialized = is; }

	//Physical body of the CActor
	//find way use smart pointers right now it does not
	b2Body* Body = nullptr;

	//for the lua
	//not const for LUA
	b2Body* GetBody() { return Body; }

	//returns copy of the Array
	//Made primarly for the LUA
	std::vector<std::shared_ptr<CActor>> GetChildren()const { return Children; }
	
	//Add child to array
	//Made primarly for the LUA
	void AddChildRaw(CActor*a);

	//Add child to array
	//Made primarly for the LUA
	void AddChild(std::shared_ptr<CActor> a);

	//Get child by index
	//Made primarly for the LUA
	CActor* GetChild(unsigned int index);

	//Get child by index
	std::shared_ptr<CActor> GetChildAsSharedPtr(unsigned int index);

	//ID of parent for checking
	//default is CObject
	static const int ParentClassID = CLASS_OBJECT;

	//ID of class for Casting
	//ID MUST be defined in the beggining of the file with class
	//default is CObject
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
	virtual void OnBeginCollision(CActor* otherActor, b2Fixture *fixtureA, b2Fixture *fixtureB, std::string PATH);

	//PATH - Path to main folder and usually used to access scripts
	//Defined by window.lua
	virtual void OnEndCollision(CActor* otherActor, b2Fixture *fixtureA, b2Fixture *fixtureB, std::string PATH);

	CActor(sf::Vector2f Location, std::string path="./../");
	~CActor();
};

