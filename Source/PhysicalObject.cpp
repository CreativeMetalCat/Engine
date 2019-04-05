#include "PhysicalObject.h"



void PhysicalObject::Init(std::string PATH)
{
	PhysMaterial->Init(PATH);
}

PhysicalObject::PhysicalObject(sf::Vector2f position,std::string MaterialName): Actor(position),MaterialName(MaterialName)
{
	PhysMaterial = std::make_shared<PhysicalMaterial>(MaterialName);
}


PhysicalObject::~PhysicalObject()
{
}
