#pragma once
#include <Siv3D.hpp>
#include "esquire.hpp"

//プレイヤー操作キャラクターに関するマネージャー

class PlayerManager
{

private:

	Player* player;

public:

	//キャラクターセット
	int SetEsquire(Vec2 pos)
	{
		player = new Esquire(pos);

		return 0;
	}

	//更新
	int Update(double deltatime)
	{


		return 0;
	}

};
