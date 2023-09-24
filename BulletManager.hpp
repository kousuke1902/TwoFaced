#pragma once
#include <Siv3D.hpp>
#include "bullet.hpp"
#include "straightB.hpp"
#include "waveB.hpp"

class BulletManager
{
private:

	Array<Bullet*> bullets;

public:

	//直進弾の生成
	int CreateStraight(Vec2 pos, double speed, double lifespan, Vec2 vector)
	{


		return 0;
	}



};
