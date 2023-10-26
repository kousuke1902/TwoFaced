#pragma once
#include <Siv3D.hpp>
#include "bullet.hpp"
#include "waveB.hpp"

//弾の処理に関するマネージャー

class BulletManager
{
private:

	Array<Bullet*> bullets;

public:

	BulletManager()
	{

		bullets.clear();
	}

	//直進弾の生成
	int CreateStraight(Vec2 pos, Vec2 vector, double speed, double lifespan, double damage, int imgtype)
	{
		Bullet* bullet = new Bullet(pos, vector, speed, lifespan, damage, imgtype);
		bullets << bullet;

		return 0;
	}

	//弾数
	size_t readBulletsize()
	{
		return bullets.size();

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

		//描画
		for (auto& bullet : bullets)
		{
			Circle(bullet->readPos(), 2.0).draw(Palette::Red);
		}

		return 0;
	}

};
