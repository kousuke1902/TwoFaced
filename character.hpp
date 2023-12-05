#pragma once
#include <Siv3D.hpp>
#include "BulletManager.hpp"

//ゲーム内のあらゆるキャラクターの基本クラス
class Character
{

protected:

	RectF HitBox;//当たり判定
	double Life;//体力
	double Speed;//移動速度
	double shotCoolTime;//弾発射のクールタイム
	double shotCoolTimer;//弾発射のクールタイムタイマー
	const Texture image;//キャラクターテクスチャ


public:

	//座標取得
	Vec2 readPos()
	{
		return HitBox.center();
	}

	//当たり判定取得
	RectF readHitBox()
	{
		return HitBox;;	
	}

	//体力取得
	double readLife()
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
		HitBox.setCenter(x);
		return 0;
	}

	//当たり判定上書き
	int writeHitBox(Vec2 x, Vec2 w)
	{
		HitBox = RectF(Arg::center(x), w);
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
	int movePos(Vec2 vec, double deltaTime)
	{
		HitBox.moveBy(vec * Speed * deltaTime);
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
	virtual int createBullet(BulletManager* bulletmanager, Vec2 enemypos)
	{
		bulletmanager->CreateStraightP(HitBox.center(), Vec2(0.0, 1.0), 100.0, 50.0, 1.0, 0);

		return 0;
	}

	//発射クールタイム処理
	int countshotCoolTimer(double deltatime)
	{
		shotCoolTimer = Max((shotCoolTimer - deltatime), 0.0);
		return 0;
	}

	//ダメージ処理
	int HitDamage(double x)
	{
		Life -= x;
		return 0;
	}

	//描画
	int draw()
	{

		return 0;
	}

};
