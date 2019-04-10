#pragma once


#ifndef CLASS_OBJECT
#include "Object.h"
#endif // !CLASS_OBJECT

#ifndef BOX2D_H
#include <Box2D.h>
#endif

#ifndef  LUABRIDGE_VERSION
extern "C"
{
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}
#include <LuaBridge/LuaBridge.h>
#endif // ! LUABRIDGE_VERSION

#define CLASS_PHYSCIAL_MATERIAL 3

class PhysicalMaterial :public CObject
{



	//For random
	int AmoutOfBulletImpactSounds = 0;

	std::vector<std::string>BulletImpactSounds;

	//For random
	int AmoutOfImpactSounds = 0;

	std::vector<std::string>ImpactSounds;

	//Name of LUA table
	std::string name;

	std::string BigMassMovementSoundName = "";

	std::string LightMassMovementSoundName = "";
public:

	// ID of class for Casting
	//ID MUST be defined in the beggining of the file with class
	//default is CObject
	static const int ClassID = CLASS_PHYSCIAL_MATERIAL;


	int GetClassID()const { return ClassID; }

	//Name of LUA table
	void SetName(std::string name) { this->name = name; }

	//Name of LUA table
	std::string GetName()const { return name; }


	void SetLightMassMovementSoundName(std::string n) { LightMassMovementSoundName = n; }

	std::string GetLightMassMovementSoundName()const { return LightMassMovementSoundName; }


	void SetBigMassMovementSoundName(std::string n) { BigMassMovementSoundName = n; }

	std::string GetBigMassMovementSoundName()const { return BigMassMovementSoundName; }

	void SetAmoutOfBulletImpactSounds(int a) { AmoutOfBulletImpactSounds = a; }

	int GetAmoutOfBulletImpactSounds()const { return AmoutOfBulletImpactSounds; }

	int GetAmoutOfImpactSounds()const { return AmoutOfImpactSounds; }

	void SetAmoutOfImpactSounds(int a) { AmoutOfImpactSounds = a; }

	static void RegisterClassLUA(lua_State *&L);

	virtual void Init(std::string PATH);

	PhysicalMaterial(std::string name, std::string path);
	~PhysicalMaterial();
};

