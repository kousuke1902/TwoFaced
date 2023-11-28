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
	int createBullet(BulletManager* bulletmanager, Vec2 enemypos) override
	{
		bulletmanager->CreateStraight(Pos, Vec2(0, -1.0), 100.0, 6.0, BulletType::player, 1.0, 0);
		return 0;
	}

};
