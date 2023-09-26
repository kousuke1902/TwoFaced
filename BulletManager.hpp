#pragma once
#include <Siv3D.hpp>
#include "bullet.hpp"
#include "waveB.hpp"

class BulletManager
{
private:

	Array<Bullet*> bullets;

public:

	//直進弾の生成
	int CreateStraight(Vec2 pos, double speed, double lifespan, Vec2 vector)
	{
		Bullet* bullet = new Bullet(pos, speed, lifespan, vector);
		bullets.push_back(bullet);

		return 0;
	}

	//情報の更新
	int Update(double deltatime)
	{

		//弾の移動
		for (auto& bullet : bullets)
		{
			bullet->movePos(deltatime);

		}

		//弾の衝突

		//弾の生存確認
		for (auto it = bullets.begin(); it != bullets.end();)
		{
			Bullet* bullet = *it;

			//寿命を迎えた
			if (bullet->Lifecheck(deltatime))
			{
				delete bullet;
				it = bullets.erase(it);
			}
			else
			{
				++it;

			}
		}

		


	}

};
