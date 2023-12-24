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
		Vec2 KeyInput = Vec2(KeyD.pressed() - KeyA.pressed(), KeyS.pressed() - KeyW.pressed()).setLength(1.0);
		Vec2 GamePadInput(XInput(0).leftThumbX, -XInput(0).leftThumbY);

		//スティックの個体差やわずかなブレで動くのを塞ぐ為に小さい値をカットする
		//切り捨てる以上であればゲームパッドのインプットを優先する
		if (GamePadInput.length() < 0.05)GamePadInput.setLength(0.0);
		else  return GamePadInput;

		return KeyInput;
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
