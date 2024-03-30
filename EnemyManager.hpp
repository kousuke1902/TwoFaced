#pragma once
#include <Siv3D.hpp>
#include "glockdrone.hpp"
#include "PlayerManager.hpp"
#include "BulletManager.hpp"
#include "EnemyStartUpInformation.hpp"

enum class EnemyName
{
	glockdronenomove,
	glockdrone

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

	//敵の生成(テスト)
	int EnemySpawn(Vec2 pos, EnemyName enemyname)
	{
		//グロックドローン移動なし
		if (enemyname == EnemyName::glockdronenomove)
		{

			Enemy* enemy = new GlockDrone(pos);
			enemies << enemy;
			return 0;

		}

		return -1;
	}

	//敵の生成
	int EnemySpawn(Vec2 pos, EnemyName enemyname, Array<MoveCommand*> movecommand)
	{
		//グロックドローン移動なし
		if (enemyname == EnemyName::glockdronenomove)
		{			 
			enemies << new GlockDrone(pos);
			return 0;

		}
		//グロックドローン
		else if (enemyname == EnemyName::glockdrone)
		{
			enemies << new GlockDrone(pos, movecommand);
			return 1;

		}

		return -1;
	}

	//敵の生成
	int EnemySpawn(EnemyStartUpInformation* startup)
	{
		//グロックドローン移動なし
		if (startup->readID() == (int)EnemyName::glockdronenomove)
		{
			enemies << new GlockDrone(startup->readspawnPos());
			return 0;

		}
		//グロックドローン
		else if (startup->readID() == (int)EnemyName::glockdrone)
		{
			enemies << new GlockDrone(startup->readspawnPos(), startup->readMoveCommands());
			return 1;

		}

		return -1;
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
	int Update(BulletManager* bulletmanager, PlayerManager* player, double deltatime)
	{
		//敵の処理確認
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

				//判断処理

				//移動処理
				enemy->moveEnemy(player->PlayerHitBox().center(), deltatime);

				//攻撃処理
				if (enemy->fire())
				{
					enemy->setshotCoolTimer();
					enemy->createBullet(bulletmanager, player->PlayerHitBox().center());
				}

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

				//防御弾
				for (auto& bullet : bulletmanager->readDefenceBullets())
				{
					if (bullet->readHitBox().intersects(enemy->readHitBox()))
					{
						enemy->HitDamage(bullet->readDamage());
						bullet->reduceLifeSpan();
					}
				}

				//プレイヤー，エネミー接触
				if (enemy->readHitBox().intersects(player->PlayerHitBox().center()))
				{
					player->HitDamage(deltatime);
					enemy->HitDamage(deltatime);
				}

				//描画処理
				//enemy->readHitBox().draw();
				enemy->draw();
				++it;

			}
		}

		return 0;

	}

};
