#pragma once
#include "bullet.hpp"

//直進弾
class StraightB : public Bullet
{
private:

	//直進
	Vec2 straight(double deltatime)
	{
		return Vec2(Speed * deltatime, 0);
	}


public:
	//動作の更新
	int Update(double deltatime)
	{
		movePos(straight(deltatime));

		return 0;
	}

};
