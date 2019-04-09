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
#include <SFML/Graphics.hpp>


#define CLASS_OBJECT 1

#ifndef DEPRECATED_WARING
#define DEPRECATED_WARING __declspec(deprecated)
#endif // !DEPRECATED_WARING


#ifndef DEPRECATED_ERROR
//Depending on compiler this will act as error or warning ( in vs 2015 it is error while vs 2017 it is warning)
#define DEPRECATED_ERROR [[deprecated]]
#endif // !DEPRECATED_ERROR


//base of the base
class CObject
{
protected:
	
public:
	std::string path;
	//ID of parent for checking
	//default is CObject
	static const int ParentClassID = CLASS_OBJECT;

	//ID of class for Casting
	//ID MUST be defined in the beggining of the file with class
	//default is CObject
	static const int ClassID = CLASS_OBJECT;

	
	int GetClassID()const { return ClassID; }

	//Made for easier usage
	//Uses dynamic_cast as of now
	template<class T = CObject*> T As()
	{
		return dynamic_cast<T>(this);
	}

	//Create LUA class from this for usage in LUA
	static void RegisterClassLUA(lua_State *&L);

	virtual void Init(std::string path){}

	virtual void Update(sf::Time) {}
	CObject(std::string path);
	~CObject();
};


