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

	PlayerInput()
	{
		Vector.clear();
		Fire = false;
		Change = false;
	}

	//移動ベクトルの取得
	Vec2 readVector() const
	{
		return Vector;
	}

	//射撃フラグの状態の取得
	bool readFire() const
	{
		return Fire;
	}

	//モード変更状態の取得
	bool readChange() const
	{
		return Change;
	}

	//移動ベクトルを算出する
	Vec2 MoveVectorLogic()
	{
		Vec2 GamePadThumbInput(XInput(0).leftThumbX, -XInput(0).leftThumbY);
		Vec2 GamePadPovInput(XInput(0).buttonRight.pressed() - XInput(0).buttonLeft.pressed(), XInput(0).buttonDown.pressed() - XInput(0).buttonUp.pressed());
		//スティックの個体差やわずかなブレで動くのを塞ぐ為に小さい値をカットする
		//切り捨てる以上であればゲームパッドのインプットを優先する
		if (GamePadThumbInput.length() >= 0.05)return GamePadThumbInput;
		else if(GamePadPovInput.length() == 1.0) return GamePadPovInput.setLength(1.0);
		else return Vec2(KeyD.pressed() - KeyA.pressed(), KeyS.pressed() - KeyW.pressed()).setLength(1.0);
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
