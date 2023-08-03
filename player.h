﻿# pragma once
# include <Siv3D.hpp>
# include "character.h"


class Player : public Character
{

private:

	
	bool Mode;//2モードの状態フラグ
	double Inherence;//キャラクター固有値



public:

	/*//ポジション，体力，移動速度，発射間隔の初期設定値
	Player(Vec2 pos, int life, double speed, double shotcooltime, double inherence)
	{
		writePos(pos);
		writeLife(life);
		writeSpeed(speed);
		writeshotCoolTime(shotcooltime);
		writeshotCoolTimer(0.0);
		Mode = false;
		Inherence = inherence;
	}
	*/

	//モード取得
	bool readMode()
	{
		return Mode;
	}

	//キャラクター固有値取得
	double readInherence()
	{
		return Inherence;
	}

	//モード切り替え
	int switchMode()
	{
		Mode != Mode;
		return 0;
	}

	//キャラクター固有値操作
	int writeInherence(double x)
	{
		if (Inherence < x)Inherence = 0;
		else Inherence += x;
		return 0;
	}

	//様々なアップデート
	int Update()
	{


		return 0;
	}

	//キーボード入力でのプレイヤーの移動ベクトルを取得する
	Vec2 KeyInputMoveVector()
	{
		Vec2 x;
		bool Right = KeyD.pressed(), Left = KeyA.pressed(), Down = KeyS.pressed(), Up = KeyW.pressed();

		x = Vec2( Right - Left, Down - Up);
		if ((Right || Left) && (Down || Up) == true) x = x * 0.7071;

		return x;
	}

};
