#include "PhysicalObject.h"



void PhysicalObject::Init(std::string PATH)
{
	using namespace luabridge;

	//load data from LUA file

	lua_State* L = luaL_newstate();
	
	//Unless Init was overriden data is supossed to be loaded from this file
	std::string d = (PATH + "scripts/MaterialTypes.lua");

	try
	{	
		luaL_dofile(L, d.c_str());
		luaL_openlibs(L);

		lua_pcall(L, 0, 0, 0);

		LuaRef table = getGlobal(L, this->GetMaterialName().c_str());
		if (!table.isNil())
		{
			std::cout << table["LightMassMovementSoundName"] << " " << table["BigMassMovementSoundName"] << " " << table["AmoutOfBulletImpactSounds"] << std::endl;
		}
		else
		{
			//handle error
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

PhysicalObject::PhysicalObject(sf::Vector2f position,std::string MaterialName): Actor(position),MaterialName(MaterialName)
{
	
}


PhysicalObject::~PhysicalObject()
{
}
