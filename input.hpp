#pragma once
# include <Siv3D.hpp>

//プレイヤーインプット関連の基本クラス
class PlayerInput
{
private:

	const size_t playerIndex = 0;



public:


	//キーボード入力でのプレイヤーの移動ベクトルを取得する
	Vec2 KeyInputMoveVector()
	{
		
		bool Right = KeyD.pressed(), Left = KeyA.pressed(), Down = KeyS.pressed(), Up = KeyW.pressed();

		return Vec2(Right - Left, Down - Up).setLength(1.0);

	}




};
