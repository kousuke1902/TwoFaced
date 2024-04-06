#pragma once
#include <Siv3D.hpp>
#include "player.hpp"
#include "input.hpp"

//右に盾を持ち左にチェーンガンを装備したロボット
// 
//プレイヤー操作キャラEsquireのクラス
class Esquire : public Player
{
private:

	bool EchargeFlag;

public:

	Esquire(Vec2 pos) : Player(pos, 47.0, 100.0, 200.0, 0.1, 0.0, 100.0, 2.0)
	{
		image = Texture{ Image{ U"img/player0.png"}.scaled(0.2) };
		image2 = Texture{ Image{ U"img/player1.png"}.scaled(0.2) };
		EchargeFlag = false;
		bulletimage = Texture{ Image{ U"img/bulletE.png"}.scaled(0.1) };
	};

	int AddInherence(double deltatime) override
	{
		//緊急チャージ確認
		if (Inherence <= 0.1)EchargeFlag = true;
		else if (EchargeFlag == true && Inherence == 100.0)EchargeFlag = false;

		if(EchargeFlag == true)Inherence += 8.0 * deltatime;
		else Inherence += 4.0 * deltatime;
		Inherence = Min(MaxInherence, Inherence);

		return 0;
	}

	//弾生成
	int createBullet(BulletManager* bulletmanager, Vec2 targetpos) override
	{
		if (Inherence > 0.2 && EchargeFlag == false)
		{
			Inherence -= 0.2;
			//レフトサイドとライトサイドでの出力の違い
			if (Mode == false)
			{
				bulletmanager->CreateStraightP(HitBox.center() + Vec2(0.0, -25.0), 23.0, 15.0, Vec2(Random(-0.1, 0.1), -1.0), 400.0, 6.0, 1.0, bulletimage);
			}
			else if (Mode == true)
			{
				bulletmanager->CreateDefence(HitBox.center() + Vec2(0.0, -30.0), 70.0, 5.0, Vec2(0.0, 0.0), 0.0, 0.008, 0.0, bulletimage);

			}

		}

		Inherence = Max(Inherence, 0.0);

		return 0;
	}

};
