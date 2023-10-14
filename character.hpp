#pragma once
#include <Siv3D.hpp>
#include "BulletManager.hpp"

//ゲーム内のあらゆるキャラクターの基本クラス
class Character
{

protected:

	Vec2 Pos;//座標
	int Life;//体力
	double Speed;//移動速度
	double shotCoolTime;//弾発射のクールタイム
	double shotCoolTimer;//弾発射のクールタイムタイマー
	const Texture image;//キャラクターテクスチャ

public:

	//座標取得
	Vec2 readPos()
	{
		return Pos;
	}

	//体力取得
	int readLife()
	{
		return Life;
	}

	//移動速度取得
	double readspeed()
	{
		return Speed;
	}

	//発射間隔
	double readshotCoolTime()
	{
		return shotCoolTime;
	}


	//発射クールタイムタイマー
	double readshotCoolTimer()
	{
		return shotCoolTimer;
	}

	//座標上書き
	int writePos(Vec2 x)
	{
		Pos = x;
		return 0;
	}

	//体力上書き
	int writeLife(int x)
	{
		Life = x;
		return 0;
	}

	//移動速度上書き
	int writeSpeed(double x)
	{
		Speed = x;
		return 0;
	}

	//発射間隔上書き
	int writeshotCoolTime(double x)
	{
		shotCoolTime = x;
		return 0;
	}

	//発射クールタイムタイマー
	int writeshotCoolTimer(double x)
	{
		shotCoolTimer = x;
		return 0;
	}

	//キャラクターの移動操作
	int movePos(Vec2 move, double deltaTime)
	{
		Pos.moveBy(move * Speed * deltaTime);
		return 0;
	}

	//発砲の有無
	bool fire()
	{
		if (shotCoolTimer <= 0.0)
		{
			shotCoolTimer += shotCoolTime;
			return true;

		}

		else return false;
		
	}

	//弾の生成
	virtual int createBullet(BulletManager* bulletmanager)
	{
		bulletmanager->CreateStraight(Pos, 100, 50, Vec2(0.0, 1.0));

		return 0;
	}

	//発射クールタイム処理
	int countshotCoolTimer(double deltatime)
	{
		shotCoolTimer = Max((shotCoolTimer - deltatime), 0.0);
		return 0;
	}


	//描画
	int draw()
	{

		return 0;
	}

};
