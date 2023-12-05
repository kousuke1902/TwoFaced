#pragma once
#include <Siv3D.hpp>
#include "player.hpp"
#include "input.hpp"

//右に盾を持ち左にチェーンガンを装備したロボット
// 
//プレイヤー操作キャラEsquireのクラス
class Esquire : public Player
{

public:

	Esquire(Vec2 pos)
	{
		HitBox = RectF(Arg::center(pos), 10);
		Life = 100.0;
		Speed = 200.0;
		shotCoolTime = 1.0;
		shotCoolTimer = 0.0;
		Mode = false;
		Inherence = 100.0;
	};

	//弾生成
	int createBullet(BulletManager* bulletmanager, Vec2 enemypos) override
	{
		bulletmanager->CreateStraightP(HitBox.center(), Vec2(0, -1.0), 100.0, 6.0, 1.0, 0);
		return 0;
	}

};
