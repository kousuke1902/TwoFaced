#pragma once
#include <Siv3D.hpp>
#include "bullet.hpp"
#include "waveB.hpp"
#include "defenceB.hpp"

//弾の処理に関するマネージャー

class BulletManager
{
private:

	Array<Bullet*> playerbullets;
	Array<Bullet*> enemybullets;
	Array<Bullet*> strongbullets;
	Array<Bullet*> defencebullets;

public:

	BulletManager()
	{
		playerbullets.clear();
		enemybullets.clear();
		strongbullets.clear();
		defencebullets.clear();
	}

	//プレイヤー弾の情報取得
	Array<Bullet*> readPlayerBullets()
	{
		return playerbullets;
	}

	//エネミー弾の情報取得
	Array<Bullet*> readEnemyBullets()
	{
		return enemybullets;
	}

	//全体攻撃弾の情報取得
	Array<Bullet*> readStrongBullets()
	{
		return strongbullets;
	}

	//防御弾の情報取得
	Array<Bullet*> readDefenceBullets()
	{
		return defencebullets;
	}

	//プレイヤー直進弾の生成
	int CreateStraightP(Vec2 pos, double w, double h, Vec2 vector, double speed, double lifespan, double damage, int imgtype)
	{
		playerbullets << new Bullet(pos, w, h, vector, speed, lifespan, damage, imgtype);
		return 0;
	}

	//エネミー直進弾の生成
	int CreateStraightE(Vec2 pos, double w, double h, Vec2 vector, double speed, double lifespan, double damage, int imgtype)
	{
		enemybullets << new Bullet(pos, w, h, vector, speed, lifespan, damage, imgtype);
		return 0;
	}

	//全体攻撃直進弾の生成
	int CreateStraightS(Vec2 pos, double w, double h, Vec2 vector, double speed, double lifespan, double damage, int imgtype)
	{
		strongbullets << new Bullet(pos, w, h, vector, speed, lifespan, damage, imgtype);
		return 0;
	}

	//防御弾生成
	int CreateDefence(Vec2 pos, double w, double h, Vec2 vector, double speed, double lifespan, double damage, int imgtype)
	{
		defencebullets << new DefenceB(pos, w, h, vector, speed, lifespan, damage, imgtype);
		return 0;
	}

	//情報の更新
	int Update(double deltatime)
	{

		//プレイヤー弾の確認
		for (auto it = playerbullets.begin(); it != playerbullets.end();)
		{
			Bullet* bullet = *it;

			//寿命を迎えた
			if (bullet->Lifecheck(deltatime))
			{
				delete bullet;
				it = playerbullets.erase(it);
			}
			else
			{
				//弾の移動
				bullet->movePos(deltatime);
				//描画
				bullet->readHitBox().draw(Palette::Blue);

				++it;
			}
		}

		//エネミー弾の確認
		for (auto it = enemybullets.begin(); it != enemybullets.end();)
		{
			Bullet* bullet = *it;

			//寿命を迎えた
			if (bullet->Lifecheck(deltatime))
			{
				delete bullet;
				it = enemybullets.erase(it);
			}
			else
			{
				//弾の移動
				bullet->movePos(deltatime);
				//描画
				bullet->readHitBox().draw(Palette::Red);

				++it;
			}
		}

		//全体攻撃弾の確認
		for (auto it = strongbullets.begin(); it != strongbullets.end();)
		{
			Bullet* bullet = *it;

			//寿命を迎えた
			if (bullet->Lifecheck(deltatime))
			{
				delete bullet;
				it = strongbullets.erase(it);
			}
			else
			{
				//弾の移動
				bullet->movePos(deltatime);
				//描画
				bullet->readHitBox().draw(Palette::Red);

				++it;
			}
		}

		//防御弾の確認
		for (auto it = defencebullets.begin(); it != defencebullets.end();)
		{
			Bullet* bullet = *it;

			//寿命を迎えた
			if (bullet->Lifecheck(deltatime))
			{
				delete bullet;
				it = defencebullets.erase(it);
			}
			else
			{
				//弾の移動
				bullet->movePos(deltatime);
				//描画
				bullet->readHitBox().draw(Palette::Darkviolet);

				//弾同士の衝突確認
				//プレイヤー弾
				for (auto& players : playerbullets)
				{
					if (bullet->readHitBox().intersects(players->readHitBox())) players->reduceLifeSpan();

				}
				//エネミー弾
				for (auto& enemies : enemybullets)
				{
					if (bullet->readHitBox().intersects(enemies->readHitBox())) enemies->reduceLifeSpan();

				}
				//全体攻撃弾
				for (auto& strongs : strongbullets)
				{
					if (bullet->readHitBox().intersects(strongs->readHitBox())) strongs->reduceLifeSpan();
				}

				++it;
			}


		}

		return 0;
	}

};
