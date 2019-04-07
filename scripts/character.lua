--this file defines basic movement,collision ets. for all character based objects

--value should be used only for the direction
--e.g. -1 or 1
function Move(actor,value)

  local d = actor:GetLinearVelocity();

  local vel = d.x;


  local res =tonumber(actor.MaxVelocity.x)*value;

  local velChange=res-vel;


  local impulse = b2Vector();

  impulse.x=velChange*64;
  impulse.y=0;

  print(impulse.x);
  actor:ApplyLinearImpulse(impulse);
end

function OnBeginCollision (actor,otherActor,fixtureA,fixtureB)
  --Copy this function to your script and add actions
end

function OnEndCollision (actor,otherActor,fixtureA,fixtureB)
  --Copy this function to your script and add actions
end

--value should be used only for the direction
--e.g. -1 or 1
function MoveY (actor,value)
  --[[
  local vel = actor:GetBody:GetLinearVelocity.y;
  local res = actor.MaxVelocity.y*value;
  local velChange=res-vel;

  local impulse=b2Vector();
  impulse.y=velChange;
  impulse.x=0;
  impulse=actor:GetBody:ApplyImpulse(impulse);
  ]]--
end
