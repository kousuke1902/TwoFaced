#pragma once
#include <Siv3D.hpp>
#include "enemy.hpp"

//グロックを搭載したドローン兵器
class GlockDrone : public Enemy
{
private:




public:

	//弾生成
	int createBullet(BulletManager* bulletmanager, Vec2 enemypos)override
	{
		bulletmanager->CreateStraight(Pos, Vec2(0.0, 1.0), 100.0, 50.0, 1.0, 0);

		return 0;
	}


};
