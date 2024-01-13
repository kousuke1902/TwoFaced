#pragma once
#include <Siv3D.hpp>
#include "enemy.hpp"

//グロックを搭載したドローン兵器
class GlockDrone : public Enemy
{
private:




public:

	GlockDrone(Vec2 pos) : Enemy(pos, 10.0, 20.0, 300.0, 1.0)
	{

	}

	GlockDrone(Vec2 pos, Array<MoveCommand*> setmovecommand) : Enemy(pos, 10.0, 20.0, 300.0, 1.0, setmovecommand)
	{

	}

	//弾生成
	int createBullet(BulletManager* bulletmanager, Vec2 enemypos)override
	{

		bulletmanager->CreateStraightE(HitBox.center(), enemypos - HitBox.center(), 100.0, 8.0, 1.0, 0);

		return 0;
	}


};
