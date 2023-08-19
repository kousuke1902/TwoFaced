#pragma once
# include <Siv3D.hpp>

//プレイヤーインプット関連の基本クラス
class Input
{

public:


	//キーボード入力でのプレイヤーの移動ベクトルを取得する
	Vec2 KeyInputMoveVector()
	{
		Vec2 x;
		bool Right = KeyD.pressed(), Left = KeyA.pressed(), Down = KeyS.pressed(), Up = KeyW.pressed();

		x = Vec2(Right - Left, Down - Up).setLength(1.0);


		return x;
	}


};
