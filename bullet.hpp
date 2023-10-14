﻿#pragma once
#include <Siv3D.hpp>

//弾の基本クラス
class Bullet
{
protected:

	Vec2 Pos;//弾の座標
	double Speed;//弾の速度
	double LifeSpan;//弾の時間的寿命
	Vec2 Vector;//弾の向き


public:

	Bullet(Vec2 pos, double speed, double lifespan, Vec2 vector)
	{
		Pos = pos;
		Speed = speed;
		LifeSpan = lifespan;
		Vector = vector;
	}

	//座標取得
	Vec2 readPos()
	{
		return Pos;
	}

	//弾のスピード取得
	double readSpeed()
	{
		return Speed;
	}

	//時間的寿命の取得
	double readLifeSpan()
	{
		return LifeSpan;
	}

	//向きの取得
	Vec2 readVector()
	{
		return Vector;
	}

	//寿命確認
	bool Lifecheck(double deltatime)
	{
		LifeSpan -= deltatime;

		if (LifeSpan <= 0)return true;
		else return false;

	}

	//弾の移動
	virtual int movePos(double deltatime)
	{
		Pos.moveBy(Vector * Speed * deltatime);

		return 0;
	}

};
