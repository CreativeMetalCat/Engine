#include "Actor.h"



void Actor::AddChildRaw(Actor * a)
{
	std::shared_ptr<Actor>ptr(a);
	this->Children.push_back(ptr);
}

void Actor::AddChild(std::shared_ptr<Actor> a)
{
	this->Children.push_back(a);
}

Actor * Actor::GetChild(unsigned int index)
{
	if (index < this->Children.size())
	{
		return  &(*this->Children.at(index));
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<Actor> Actor::GetChildAsSharedPtr(unsigned int index)
{
	if (index < this->Children.size() - 1 && index >= 0)
	{
		return  this->Children.at(index);
	}
	else
	{
		return nullptr;
	}
	
}


void Actor::RegisterClassLUA(lua_State *&L)
{
	using namespace luabridge;
	try
	{
		//Register Actor in lua
		getGlobalNamespace(L)
			.beginClass<Actor>("Actor")
			.addConstructor<void(*) (sf::Vector2f)>()
			.addProperty("Location", &Actor::GetActorLocation, &Actor::SetActorLocation)
			.addProperty("PhysBodyInitialized",&Actor::GetPhysBodyInitialized,&Actor::SetPhysBodyInitialized)
			.addProperty("AreaId",&Actor::GetAreaId,&Actor::SetAreaId)
			.addFunction("AddChildRaw", &Actor::AddChildRaw)
			.addFunction("GetChild", &Actor::GetChild)
			.endClass();
	}
	catch(LuaException e)
	{
		std::cout << "Failed to register class in LUA" << std::endl;
	}

	catch (std::exception e)
	{
		std::cout << "Failed to register class in LUA " << e.what() << std::endl;
	}
}

void Actor::OnBeginCollision(std::shared_ptr<Object> otherActor, b2Fixture * fixtureA, b2Fixture * fixtureB, std::string PATH)
{
	using namespace luabridge;
	lua_State* L = luaL_newstate();
	std::string d = (PATH + "scripts/actor.lua");
	try
	{

		luaL_dofile(L, d.c_str());
		luaL_openlibs(L);

		lua_pcall(L, 0, 0, 0);

		//Register this class in lua
		this->RegisterClassLUA(L);

		//register other actor's class
		otherActor->RegisterClassLUA(L);

		//Register b2Fixture in lua
		getGlobalNamespace(L)
			.beginClass<b2Fixture>("b2Fixture")
			.endClass();

		LuaRef LUAOnBeginCollision = getGlobal(L, "OnBeginCollision");
		if (LUAOnBeginCollision.isFunction())
		{
			LUAOnBeginCollision(this, &(*otherActor), fixtureA, fixtureB);
		}
	}
	catch (LuaException e)
	{
		std::cout << e.what() << std::endl;
	}

	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}
}

void Actor::OnEndCollision(std::shared_ptr<Actor> otherActor, b2Fixture * fixtureA, b2Fixture * fixtureB, std::string PATH)
{
	using namespace luabridge;
	lua_State* L = luaL_newstate();
	std::string d = (PATH + "scripts/actor.lua");
	try
	{

		luaL_dofile(L, d.c_str());
		luaL_openlibs(L);

		lua_pcall(L, 0, 0, 0);

		//Register Actor in lua
		Actor::RegisterClassLUA(L);

		//register other actor's class
		otherActor->RegisterClassLUA(L);

		//Register b2Fixture in lua
		getGlobalNamespace(L)
			.beginClass<b2Fixture>("b2Fixture")
			.endClass();


		LuaRef LUAOnEndCollision = getGlobal(L, "OnEndCollision");
		if (LUAOnEndCollision.isFunction())
		{
			LUAOnEndCollision(this, &(*otherActor), fixtureA, fixtureB);
		}
	}
	catch (LuaException e)
	{
		std::cout << e.what() << std::endl;
	}

}

Actor::Actor(sf::Vector2f Location):Location(Location)
{
	
}


Actor::~Actor()
{
}
