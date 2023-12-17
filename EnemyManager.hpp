#pragma once
#include <Siv3D.hpp>
#include "glockdrone.hpp"
#include "PlayerManager.hpp"
#include "BulletManager.hpp"

enum class EnemyName
{
	glockdronenomove, glockdrone

};

class EnemyManager
{

private:

	Array<Enemy*> enemies;

public:

	EnemyManager()
	{

		enemies.clear();
	}

	//敵の生成
	int EnemySpawn(Vec2 pos, EnemyName enemyname, Array<Vec2> movecommand = { Vec2(100.0, 100.0) } )
	{
		//グロックドローン移動なし
		if (enemyname == EnemyName::glockdronenomove)
		{

			Enemy* enemy = new GlockDrone(pos);
			enemies << enemy;
			return 0;

		}
		//グロックドローン
		else if (enemyname == EnemyName::glockdrone)
		{
			Enemy* enemy = new GlockDrone(pos, movecommand);
			enemies << enemy;
			return 1;

		}

	}

	//エネミーの総数
	size_t EnemiesSize()
	{

		return enemies.size();
	}

	//エネミーの情報取得
	Enemy* readEnemy(size_t place)
	{
		if (enemies.size() > place)
		{
			return enemies[place];
		}
		return NULL;
	}



	//更新
	int Update(BulletManager* bulletmanager, Vec2 playerpos, double deltatime)
	{
		//敵の生存確認
		for (auto it = enemies.begin(); it != enemies.end();)
		{
			
			Enemy* enemy = *it;

			//生存フラグの確認
			if (enemy->deadFlag())
			{
				delete enemy;
				it = enemies.erase(it);
			}
			else
			{
				++it;

			}
		}

		for (auto& enemy : enemies)
		{
			//判断処理

			//移動処理
			enemy->moveEnemy(deltatime);

			//攻撃処理
			if (enemy->fire())enemy->createBullet(bulletmanager, playerpos);
			enemy->countshotCoolTimer(deltatime);

			//当たり判定処理
			//プレイヤー弾
			for (auto& bullet : bulletmanager->readPlayerBullets())
			{
				if (bullet->readHitBox().intersects(enemy->readHitBox()))
				{
					enemy->HitDamage(bullet->readDamage());
					bullet->reduceLifeSpan();
				}
			}

			//全体攻撃弾
			for (auto& bullet : bulletmanager->readStrongBullets())
			{
				if (bullet->readHitBox().intersects(enemy->readHitBox()))
				{
					enemy->HitDamage(bullet->readDamage());
					bullet->reduceLifeSpan();
				}
			}

			//描画処理
			Circle(enemy->readPos(), 4.0).draw(Palette::Red);

		}

		return 0;

	}

};
