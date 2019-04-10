#include "PhysicalMaterial.h"



void PhysicalMaterial::RegisterClassLUA(lua_State *& L)
{
	using namespace luabridge;

	try
	{
		getGlobalNamespace(L)
			.beginClass<PhysicalMaterial>("PhysicalMaterial")
			.addProperty("BigMassMovementSoundName", &PhysicalMaterial::GetBigMassMovementSoundName, &PhysicalMaterial::SetBigMassMovementSoundName)
			.addProperty("LightMassMovementSoundName", &PhysicalMaterial::GetLightMassMovementSoundName, &PhysicalMaterial::SetLightMassMovementSoundName)
			.addProperty("Name", &PhysicalMaterial::GetName, &PhysicalMaterial::SetName)
			.addProperty("AmoutOfImpactSounds",&PhysicalMaterial::GetAmoutOfImpactSounds,&PhysicalMaterial::SetAmoutOfImpactSounds)
			.addProperty("AmoutOfBulletImpactSounds", &PhysicalMaterial::GetAmoutOfBulletImpactSounds, &PhysicalMaterial::SetAmoutOfBulletImpactSounds)
			.addFunction("GetClassID", &PhysicalMaterial::GetClassID)
			.endClass();
	}
	catch (LuaException e)
	{
		std::cout << "Failed to register class in LUA" << std::endl;
	}
	catch (std::exception e)
	{
		std::cout << "Failed to register class in LUA " << e.what() << std::endl;
	}

}

void PhysicalMaterial::Init(std::string PATH)
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

		LuaRef table = getGlobal(L, name.c_str());
		if (!table.isNil())
		{
			std::cout << table["LightMassMovementSoundName"] << " " << table["BigMassMovementSoundName"] << " " << table["AmoutOfBulletImpactSounds"] << std::endl;
			if (!table["LightMassMovementSoundName"].isNil() && table["LightMassMovementSoundName"].isString())
			{
				this->SetLightMassMovementSoundName(table["LightMassMovementSoundName"].cast<std::string>());
			}
			if (!table["BigMassMovementSoundName"].isNil() && table["BigMassMovementSoundName"].isString())
			{
				this->SetBigMassMovementSoundName(table["BigMassMovementSoundName"].cast<std::string>());
			}
			if (!table["AmoutOfBulletImpactSounds"].isNil() && table["AmoutOfBulletImpactSounds"].isNumber())
			{
				this->AmoutOfBulletImpactSounds = table["AmoutOfBulletImpactSounds"].cast<int>();
			}
			if (!table["AmoutOfImpactSounds"].isNil() && table["AmoutOfImpactSounds"].isNumber())
			{
				this->AmoutOfImpactSounds = table["AmoutOfImpactSounds"].cast<int>();
			}
			LuaRef bulletSounds = table["BulletImpactSounds"];
			if (!bulletSounds.isNil() && bulletSounds.isTable())
			{
				for (int i = 1; i <= this->GetAmoutOfBulletImpactSounds(); i++)
				{
					BulletImpactSounds.push_back(bulletSounds[i].cast<std::string>());
				}
			}
			LuaRef ImpactSound = table["ImpactSounds"];
			if (!ImpactSound.isNil() && ImpactSound.isTable())
			{
				for (int i = 1; i <= this->GetAmoutOfImpactSounds(); i++)
				{
					ImpactSounds.push_back(ImpactSound[i].cast<std::string>());
				}
			}
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

PhysicalMaterial::PhysicalMaterial(std::string name, std::string path):CObject(path),name(name)
{

}


PhysicalMaterial::~PhysicalMaterial()
{
}
