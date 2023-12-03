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

	//更新
	int Update(BulletManager* bulletmanager, PlayerInput input, double deltatime)
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

		//ダメージ処理

		//描画
		player->readHitBox().draw();

		return 0;
	}

};
