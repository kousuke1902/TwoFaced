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

	Esquire(Vec2 pos) : Player(pos, 10.0, 100.0, 200.0, 0.5, 1.0, 100.0, 2.0)
	{

	};

	//弾生成
	int createBullet(BulletManager* bulletmanager, Vec2 targetpos) override
	{
		//レフトサイドとライトサイドでの出力の違い
		if (Mode == false)
		{
			bulletmanager->CreateStraightP(HitBox.center(), 5.0, 5.0,Vec2(Random(-0.1, 0.1), -1.0), 100.0, 6.0, 1.0, 0);
		}
		else
		{
			
		}

		return 0;
	}

};
