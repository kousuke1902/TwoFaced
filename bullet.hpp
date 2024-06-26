﻿#pragma once
#include <Siv3D.hpp>


//弾の基本クラス
class Bullet
{
protected:

	RectF HitBox;//当たり判定
	Vec2 Vector;//弾の向き
	double Speed;//弾の速度
	double LifeSpan;//弾の時間的寿命
	double Damage;//与えるダメージ
	Texture Img;//弾の画像の種類

public:

	Bullet(Vec2 pos, double w, double h, Vec2 vector, double speed, double lifespan, double damage, Texture img)
	{
		HitBox = RectF(Arg::center(pos), w, h);
		Vector = vector.setLength(1.0);
		Speed = speed;
		LifeSpan = lifespan;
		Damage = damage;
		Img = img;
	}


	//座標取得
	Vec2 readPos()
	{
		return HitBox.center();
	}

	//当たり判定取得
	RectF readHitBox()
	{
		return HitBox;
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

	//ダメージ取得
	double readDamage()
	{
		return Damage;
	}

	//時間的寿命の削り取り
	virtual int reduceLifeSpan()
	{
		LifeSpan = 0;
		return 0;
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
		HitBox.moveBy(Vector * Speed * deltatime);

		return 0;
	}

	//弾の描画
	virtual int draw()
	{
		double theta = Atan2(Vector.y, Vector.x) + 90_deg;
		Img.rotated(theta).drawAt(HitBox.center());
		//HitBox.rotated(theta).draw(Palette::Red);
		return 0;
	}

};
