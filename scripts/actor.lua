--Using this with Physal Body created may cause unexpected behaviour
function SetActorLocation (actor,location)
  actor.Location=location;
end

--Example of movement that can be done in lua
--Using this with Physical body created may cause unexpected behaviour
function MoveX (actor,value)
  local x = actor.Location.x;
  local vect= Vector2();
  vect.x=x + value;
  vect.y=actor.Location.y;
    SetActorLocation(actor,vect);
end

--Example of movement that can be done in lua
--Using this with Physical body created may cause unexpected behaviour
function MoveY (actor,value)
  local y = actor.Location.y;
  local vect = Vector2();
  vect.y=y + value;
  vect.x=actor.Location.x;
    SetActorLocation(actor,vect);
end

function AddChild (parent,child)
  parent:AddChildRaw(child);
end

function GetChild (parent,index)
local child = parent:GetChild(index);
return child;
end
