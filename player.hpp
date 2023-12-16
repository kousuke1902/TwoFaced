#pragma once
#include <Siv3D.hpp>
#include "character.hpp"

//プレイヤーが操作するキャラクターに関する継承クラス
class Player : public Character
{

protected:

	
	bool Mode;//2モードの状態フラグ
	double Inherence;//キャラクター固有値
	double shotCoolTime2;//キャラクター二つ目の武器の発射間隔
	double shotCoolTimer2;//キャラクター二つ目の武器のクールタイムタイマー


public:

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
		Mode =! Mode;
		return 0;
	}

	//キャラクター固有値上書き
	int writeInherence(double x)
	{
		Inherence = x;
		return 0;
	}

	//キャラクター固有値操作
	int AddInherence(double x)
	{
		if (Inherence < x)Inherence = 0;
		else Inherence += x;
		return 0;
	}

	//二つ目の武器の発砲の有無
	bool fire2()
	{
		if (shotCoolTimer2 <= 0.0)
		{
			shotCoolTimer2 += shotCoolTime2;
			return true;

		}

		else return false;

	}

	//発射クールタイム処理
	int countshotCoolTimer(double deltatime)
	{
		shotCoolTimer = Max((shotCoolTimer - deltatime), 0.0);
		shotCoolTimer2 = Max((shotCoolTimer2 - deltatime), 0.0);
		return 0;
	}



};
