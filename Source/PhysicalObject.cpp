#include "PhysicalObject.h"



void PhysicalObject::Init(std::string PATH)
{
	PhysMaterial->Init(PATH);
}

PhysicalObject::PhysicalObject(sf::Vector2f position,std::string MaterialName, std::string path): Actor(position,path),MaterialName(MaterialName)
{
	PhysMaterial = std::make_shared<PhysicalMaterial>(MaterialName,path);
}


PhysicalObject::~PhysicalObject()
{
}
