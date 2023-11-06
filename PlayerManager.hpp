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


		//描画
		Circle(player->readPos(), 4.0).draw(Palette::Black);

		return 0;
	}

};
