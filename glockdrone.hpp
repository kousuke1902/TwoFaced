#pragma once
#include <Siv3D.hpp>
#include "enemy.hpp"

//グロックを搭載したドローン兵器
class GlockDrone : public Enemy
{
private:




public:

	GlockDrone(Vec2 pos) : Enemy(pos, 49.0, 20.0, 300.0, 1.0)
	{
		image = Texture{ U"img/drone.png" };
	}

	GlockDrone(Vec2 pos, Array<MoveCommand*> setmovecommand) : Enemy(pos, 52.0, 20.0, 300.0, 1.0, setmovecommand)
	{
		image = Texture{ Image{ U"img/drone.png"}.scaled(0.2) };
	}

	//弾生成
	int createBullet(BulletManager* bulletmanager, Vec2 enemypos)override
	{

		bulletmanager->CreateStraightE(HitBox.center(), 5, 5, enemypos - HitBox.center(), 100.0, 8.0, 1.0, 0);

		return 0;
	}


};
