﻿#pragma once
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
	RectF PlayerHitBox()
	{
		return player->readHitBox();
	}

	//プレイヤーのモード状態
	bool PlayerMode()
	{
		return player->readMode();
	}

	//生死フラグ
	bool deadFlag()
	{
		return player->deadFlag();
	}

	//ダメージ付与
	int HitDamage(double x)
	{
		player->HitDamage(x);
		return 0;
	}

	//体力の閲覧
	double PlayerLife()
	{
		return player->readLife();
	}

	//固有値の閲覧
	double PlayerInherence()
	{
		return player->readInherence();
	}

	//モード切替時間間隔
	double PlayerModeCoolTime()
	{
		return player->readModechangeCooltime();
	}

	//モード切替クールタイマー
	double PlayerModeCoolTimer()
	{
		return player->readModechangeCoolTimer();
	}

	//更新
	int Update(BulletManager* bulletmanager, PlayerInput *input, double deltatime)
	{
		//生存判定
		if (!player->deadFlag())
		{
			//移動処理
			player->movePos(input->readVector() * deltatime);

			//攻撃処理
			if (input->readFire() && player->fire())
			{
				player->setshotCoolTimer();
				player->createBullet(bulletmanager, Vec2(0.0, 0.0));

			}

			player->countshotCoolTimer(deltatime);

			//切り替え処理
			if (input->readChange() && player->Modechange()) player->switchMode();
			player->countModechangeCoolTimer(deltatime);

			//固有値操作
			player->AddInherence(deltatime);

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

			//防御弾
			for (auto& bullet : bulletmanager->readDefenceBullets())
			{
				if (bullet->readHitBox().intersects(player->readHitBox()))
				{
					player->HitDamage(bullet->readDamage());
					bullet->reduceLifeSpan();
				}
			}

			//描画
			//player->readHitBox().draw();
			player->draw();
		}

		return 0;
	}

};
