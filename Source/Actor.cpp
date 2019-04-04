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

Actor::Actor(sf::Vector2f Location):Location(Location)
{
	
}


Actor::~Actor()
{
}
