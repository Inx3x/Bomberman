#pragma once
#include "Headers.h"

class CollisionManager
{
public:
	static bool CollisionRact(const Transform& _Temp, const Transform& _Dest)
	{
		if (_Temp.Position.x + _Temp.Scale.x > _Dest.Position.x && 
			_Temp.Position.y + _Temp.Scale.y > _Dest.Position.y &&
			_Dest.Position.x + _Dest.Scale.x > _Temp.Position.x &&
			_Dest.Position.y + _Dest.Scale.y > _Temp.Position.y)
		{
			return true;
		}
		return false;
	}
};