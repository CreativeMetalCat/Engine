#include "Object.h"


void Object::RegisterClassLUA(lua_State *&L)
{
	using namespace luabridge;
	try
	{
	//Register Actor in lua
	getGlobalNamespace(L)
		.beginClass<Object>("Object")
		.addFunction("GetClassID", &Object::GetClassID)
		.addFunction("Init", &Object::Init)
		.endClass();
	}
	catch (LuaException e)
	{
		std::cout << "Failed to register class in LUA" << std::endl;
	}
	catch (std::exception e)
	{
		std::cout << "Failed to register class in LUA " << e.what() <<std::endl;
	}
}

Object::Object(std::string path):path(path)
{
}


Object::~Object()
{
}
