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

	Esquire(Vec2 pos) : Player(pos, 10.0, 100.0, 200.0, 0.2, 0.0, 100.0, 2.0)
	{
		image = Texture{ Image{ U"img/player0.png"}.scaled(0.2) };
		image2 = Texture{ Image{ U"img/player1.png"}.scaled(0.2) };
	};

	int AddInherence(double deltatime) override
	{
		Inherence += 1.0 * deltatime;
		Inherence = Min(MaxInherence, Inherence);
		Inherence = Max(Inherence, 0.0);
		return 0;
	}

	//弾生成
	int createBullet(BulletManager* bulletmanager, Vec2 targetpos) override
	{
		if (Inherence > 0.2)
		{
			Inherence -= 0.2;
			//レフトサイドとライトサイドでの出力の違い
			if (Mode == false)
			{
				bulletmanager->CreateStraightP(HitBox.center(), 5.0, 5.0, Vec2(Random(-0.1, 0.1), -1.0), 400.0, 6.0, 1.0, 0);
			}
			else if (Mode == true)
			{
				bulletmanager->CreateDefence(HitBox.center() + Vec2(0.0, -10.0), 40.0, 5.0, Vec2(0.0, 0.0), 0.0, 0.008, 0.0, 0);

			}

		}


		return 0;
	}

};
