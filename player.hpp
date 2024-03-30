#pragma once
#include <Siv3D.hpp>
#include "character.hpp"

//プレイヤーが操作するキャラクターに関する継承クラス
class Player : public Character
{

protected:

	
	bool Mode;//2モードの状態フラグ
	double Inherence;//キャラクター固有値
	double MaxInherence;//最大キャラクター固有値
	double shotCoolTime2;//キャラクター二つ目の武器の発射間隔
	double shotCoolTimer2;//キャラクター二つ目の武器のクールタイムタイマー
	double ModechangeCoolTime;//モード切替の変更間隔
	double ModechangeCoolTimer;//モード切替のクールタイムタイマー
	Texture image2;//キャラクターテクスチャ

public:

	Player(Vec2 pos, double boxsize, double life, double speed, double setcooltime, double setcooltime2, double inherence, double setmodetime) : Character(pos, boxsize, life, speed, setcooltime)
	{
		Mode = false;
		Inherence = inherence;
		MaxInherence = inherence;
		shotCoolTime2 = setcooltime2;
		shotCoolTimer2 = 0.0;
		ModechangeCoolTime = setmodetime;
		ModechangeCoolTimer = 0.0;
	}

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

	//モードチェンジの変更間隔の取得
	double readModechangeCooltime()
	{
		return ModechangeCoolTime;
	}

	//モード切替のクールタイムタイマーの取得
	double readModechangeCoolTimer()
	{
		return ModechangeCoolTimer;
	}

	//モード切替の有無
	bool Modechange()
	{
		if (ModechangeCoolTimer <= 0.0)return true;
		else return false;
	}

	//モード切り替え
	int switchMode()
	{
		ModechangeCoolTimer = ModechangeCoolTime;
		Mode = !Mode;
		return 0;
	}

	//キャラクター固有値上書き
	int writeInherence(double x)
	{
		Inherence = x;
		return 0;
	}

	//キャラクター固有値操作
	virtual int AddInherence(double deltatime)
	{
		Inherence += 1.0 * deltatime;
		return 0;
	}

	//発射クールタイムタイマーの更新
	int setshotCoolTimer() override
	{
		shotCoolTimer = shotCoolTime;
		shotCoolTimer2 = shotCoolTime2;
		return 0;
	}

	//発砲の有無
	bool fire() const override
	{
		if (Mode == false)
		{
			if (shotCoolTimer <= 0.0)return true;
		}

		else if (Mode == true)
		{
			if (shotCoolTimer2 <= 0.0)return true;
		}

		return false;
	}

	//二つ目の武器の発砲の有無
	bool fire2()
	{
		if (shotCoolTimer2 <= 0.0)return true;
		else return false;
	}

	//発射クールタイム処理
	int countshotCoolTimer(double deltatime) override
	{
		shotCoolTimer = Max((shotCoolTimer - deltatime), 0.0);
		shotCoolTimer2 = Max((shotCoolTimer2 - deltatime), 0.0);
		return 0;
	}

	//モード切替クールタイム処理
	int countModechangeCoolTimer(double deltatime)
	{
		ModechangeCoolTimer = Max((ModechangeCoolTimer - deltatime), 0.0);
		return 0;
	}

	//描画と切り替え
	int draw() override
	{
		if(Mode == false)image.drawAt(readPos());
		else if(Mode == true)image2.drawAt(readPos());
		return 1;
	}

};
