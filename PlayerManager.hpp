#pragma once
#include <Siv3D.hpp>
#include "input.hpp"
#include "esquire.hpp"

//プレイヤー操作キャラクターに関するマネージャー

class PlayerManager
{

private:

	Player* player;

public:

	PlayerManager()
	{
		player = new Esquire(Vec2(300, 400));

	}

	//キャラクターセット
	int SetEsquire(Vec2 pos)
	{
		player = new Esquire(pos);

		return 0;
	}

	//プレイヤー座標
	Vec2 PlayerPos()
	{
		return player->readPos();
	}

	bool deadFlag()
	{
		return player->deadFlag();
	}

	//更新
	int Update(BulletManager* bulletmanager, PlayerInput input, double deltatime)
	{
		//生存判定
		if (!player->deadFlag())
		{
			//移動処理
			player->movePos(input.KeyInputMoveVector(), deltatime);

			//攻撃処理
			if (input.pressFire() && player->fire())
			{
				player->createBullet(bulletmanager, Vec2(0.0, 0.0));

			}

			player->countshotCoolTimer(deltatime);

			//切り替え処理


			//固有値操作

			//当たり判定処理
			//エネミー弾
			for (auto& bullet : bulletmanager->readEnemyBullets())
			{
				if (bullet->readHitBox().intersects(player->readHitBox()))
				{
					player->HitDamage(bullet->readDamage());
					bullet->reduceLifeSpan();
				}
			}

			//全体攻撃弾
			for (auto& bullet : bulletmanager->readStrongBullets())
			{
				if (bullet->readHitBox().intersects(player->readHitBox()))
				{
					player->HitDamage(bullet->readDamage());
					bullet->reduceLifeSpan();
				}
			}

			//描画
			player->readHitBox().draw();
		}

		return 0;
	}

};
