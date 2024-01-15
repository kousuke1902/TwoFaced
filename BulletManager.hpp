﻿#pragma once
#include <Siv3D.hpp>
#include "bullet.hpp"
#include "waveB.hpp"
//弾の処理に関するマネージャー

class BulletManager
{
private:

	Array<Bullet*> playerbullets, enemybullets, strongbullets;

public:

	BulletManager()
	{

		playerbullets.clear();
		enemybullets.clear();
		strongbullets.clear();
	}

	//弾数
	size_t readPlayerBulletsize()
	{
		return playerbullets.size();

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

	//プレイヤー直進弾の生成
	int CreateStraightP(Vec2 pos, Vec2 vector, double speed, double lifespan, double damage, int imgtype)
	{
		playerbullets << new Bullet(pos, vector, speed, lifespan, damage, imgtype);
		return 0;
	}

	//エネミー直進弾の生成
	int CreateStraightE(Vec2 pos, Vec2 vector, double speed, double lifespan, double damage, int imgtype)
	{
		enemybullets << new Bullet(pos, vector, speed, lifespan, damage, imgtype);
		return 0;
	}

	//全体攻撃直進弾の生成
	int CreateStraightS(Vec2 pos, Vec2 vector, double speed, double lifespan, double damage, int imgtype)
	{
		strongbullets << new Bullet(pos, vector, speed, lifespan, damage, imgtype);
		return 0;
	}

	//情報の更新
	int Update(double deltatime)
	{

		//プレイヤー弾の生存確認
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
				++it;

			}
		}

		//エネミー弾の生存確認
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
				++it;

			}
		}

		//全体攻撃弾の生存確認
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
				++it;

			}
		}

		//プレイヤー弾
		for (auto& bullet : playerbullets)
		{
			//弾の移動
			bullet->movePos(deltatime);
			//描画
			bullet->readHitBox().draw(Palette::Blue);
		}

		//エネミー弾
		for (auto& bullet : enemybullets)
		{
			//弾の移動
			bullet->movePos(deltatime);
			//描画
			bullet->readHitBox().draw(Palette::Red);
		}

		//全体攻撃弾
		for (auto& bullet : strongbullets)
		{
			//弾の移動
			bullet->movePos(deltatime);
			//描画
			bullet->readHitBox().draw(Palette::Gold);
		}

		return 0;
	}

};
