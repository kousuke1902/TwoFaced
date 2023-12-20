#pragma once
#include <Siv3D.hpp>

//プレイヤーインプット関連の基本クラス
class PlayerInput
{
private:


public:


	//キーボード入力でのプレイヤーの移動ベクトルを取得する
	Vec2 KeyInputMoveVector()
	{
		
		return Vec2(KeyD.pressed() - KeyA.pressed(), KeyS.pressed() - KeyW.pressed()).setLength(1.0);

	}

	//移動ベクトルを算出する
	Vec2 MoveVector()
	{



	}

	//射撃ボタン検知
	bool pressFire()
	{
		return KeySpace.pressed() || XInput(0).buttonA.pressed();
	}

	//切り替えボタン検知
	bool downModechange()
	{
		return KeyV.down() || XInput(0).buttonB.pressed();
	}


};
