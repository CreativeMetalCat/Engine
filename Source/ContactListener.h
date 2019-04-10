#pragma once

#ifndef BOX2D_H
#include <Box2D.h>
#endif

#include "Actor.h"
class ContactListener : public b2ContactListener
{

private:

protected:

public:
	std::string path;
	void BeginContact(b2Contact*contact)
	{
		void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
		void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
		if (bodyUserDataA&&bodyUserDataB)
		{
			static_cast<CActor*>(bodyUserDataA)->OnBeginCollision(static_cast<CActor*>(bodyUserDataB), contact->GetFixtureA(), contact->GetFixtureB(), path);
			static_cast<CActor*>(bodyUserDataB)->OnBeginCollision(static_cast<CActor*>(bodyUserDataA), contact->GetFixtureA(), contact->GetFixtureB(), path);
		}
	}
	void EndContact(b2Contact*contact)
	{
		void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
		void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
		if (bodyUserDataA&&bodyUserDataB)
		{
			static_cast<CActor*>(bodyUserDataA)->OnEndCollision(static_cast<CActor*>(bodyUserDataB), contact->GetFixtureA(), contact->GetFixtureB(), path);
			static_cast<CActor*>(bodyUserDataB)->OnEndCollision(static_cast<CActor*>(bodyUserDataA), contact->GetFixtureA(), contact->GetFixtureB(), path);
		}
	}
};


