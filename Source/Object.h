#pragma once
#include <iostream>
#include <memory>

extern "C"
{
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}
#include <LuaBridge/LuaBridge.h>

//#include "MainFuncLib.h"

#define CLASS_OBJECT 1

//base of the base
class Object
{
protected:
	
public:

	//ID of parent for checking
	//default is Object
	static const int ParentClassID = CLASS_OBJECT;

	//ID of class for Casting
	//ID MUST be defined in the beggining of the file with class
	//default is Object
	static const int ClassID = CLASS_OBJECT;

	
	int GetClassID()const { return ClassID; }

	//Made for easier usage
	//Uses dynamic_cast as of now
	template<class T = Object*> T As()
	{
		return dynamic_cast<T>(this);
	}

	//Create LUA class from this for usage in LUA
	static void RegisterClassLUA(lua_State *&L);

	virtual void Init(){}

	Object();
	~Object();
};


