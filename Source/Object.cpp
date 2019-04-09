#include "Object.h"


void CObject::RegisterClassLUA(lua_State *&L)
{
	using namespace luabridge;
	try
	{
	//Register CActor in lua
	getGlobalNamespace(L)
		.beginClass<CObject>("CObject")
		.addFunction("GetClassID", &CObject::GetClassID)
		.addFunction("Init", &CObject::Init)
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

CObject::CObject(std::string path):path(path)
{
}


CObject::~CObject()
{
}
