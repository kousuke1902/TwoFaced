﻿#pragma once
#include <Siv3D.hpp>
#include "enemy.hpp"

//グロックを搭載したドローン兵器
class GlockDrone : public Enemy
{
private:




public:

	GlockDrone(Vec2 pos)
	{
		HitBox = RectF(Arg::center(pos), 10);
		Life = 20;
		Speed = 300;
		shotCoolTime = 2.0;
		shotCoolTimer = 0.0;
	}

	GlockDrone(Vec2 pos, Array<Vec2> movecommand)
	{
		HitBox = RectF(Arg::center(pos), 10);
		Life = 20;
		Speed = 300;
		shotCoolTime = 2.0;
		shotCoolTimer = 0.0;
		MoveCommand = movecommand;
	}

	//弾生成
	int createBullet(BulletManager* bulletmanager, Vec2 enemypos)override
	{

		bulletmanager->CreateStraight(HitBox.center(), enemypos - HitBox.center(), 100.0, 8.0, BulletType::enemy, 1.0, 0);

		return 0;
	}


};
