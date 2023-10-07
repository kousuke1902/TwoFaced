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
		Pos = pos;
		Life = 100;
		Speed = 200;
		shotCoolTime = 1.0;
		shotCoolTimer = 0.0;
		Mode = false;
		Inherence = 100;

	};

	//弾生成
	int createBullet(BulletManager* bulletmanager) override
	{
		bulletmanager->CreateStraight(Pos, 100, 50, Vec2(0, -1.0));

		return 0;
	}

};
