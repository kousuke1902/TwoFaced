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

	PlayerManager(Vec2 pos)
	{
		player = new Esquire(pos);

	}

	//キャラクターセット
	int SetEsquire(Vec2 pos)
	{
		player = new Esquire(pos);

		return 0;
	}

	//更新
	int Update(BulletManager* bulletmanager ,double deltatime)
	{
		//移動処理


		//攻撃処理

		//切り替え処理


		//固有値操作



		return 0;
	}

};
