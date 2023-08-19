# pragma once
# include <Siv3D.hpp>
# include "player.hpp"

//右に盾を持ち左にチェーンガンを装備したロボット
//プレイヤー操作キャラEsquireのクラス
class Esquire : public Player
{

public:

	Esquire(Vec2 pos, int life, double speed, double shotcooltime, double inherence)
	{
		writePos(pos);
		writeLife(life);
		writeSpeed(speed);
		writeshotCoolTime(shotcooltime);
		WriteInherence(inherence);

	};

	int Update()
	{
		//移動処理


		//攻撃処理

		//切り替え処理

		//固有値操作


		return 0;
	}

};
