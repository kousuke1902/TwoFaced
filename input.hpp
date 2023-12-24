#pragma once
#include <Siv3D.hpp>

//プレイヤーインプット関連の基本クラス
class PlayerInput
{
private:

	Vec2 Vector;//移動ベクトル
	bool Fire;//射撃フラグ
	bool Change;//モード変更フラグ


public:

	//移動ベクトルの取得
	Vec2 readVector()
	{
		return Vector;
	}

	//射撃フラグの状態の取得
	bool readFire()
	{
		return Fire;
	}

	//モード変更状態の取得
	bool readChange()
	{
		return Change;
	}

	//移動ベクトルを算出する
	Vec2 MoveVectorLogic()
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
		return KeyV.down() || XInput(0).buttonB.down();
	}

	//更新
	int Update()
	{
		Vector = MoveVectorLogic();
		Fire = pressFire();
		Change = downModechange();

		return 0;
	}

};
