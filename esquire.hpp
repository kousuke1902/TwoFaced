# pragma once
# include <Siv3D.hpp>
# include "player.hpp"

//右に盾を持ち左にチェーンガンを装備したロボット
// 
//プレイヤー操作キャラEsquireのクラス
class Esquire : public Player
{

public:

	Esquire(Vec2 pos)
	{
		Pos = pos;
		Life = 100;
		Speed = 200;
		shotCoolTime = 1.0;
		shotCoolTimer = 0.0;
		Mode = false;
		Inherence = 100;

	};

	//処理のアップデート
	int Update()
	{
		//移動処理


		//攻撃処理

		//切り替え処理

		//固有値操作


		return 0;
	}

};
