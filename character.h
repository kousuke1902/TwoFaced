# pragma once
# include <Siv3D.hpp>

class Character
{
private:

	Vec2 Pos;//座標
	int Life;//体力
	double Speed;//移動速度
	double shotCoolTime;//弾発射のクールタイム
	double shotCoolTimer;//弾発射のクールタイムタイマー
	const Texture image;//キャラクターテクスチャ

public:


	//キャラクター移動
	int movePos(bool right, bool left, bool down, bool up, double deltaTime)
	{
		const Vec2 move = Vec2{ (right - left),  (down - up)}.setLength(deltaTime * Speed);
		Pos.moveBy(move);
		
		return 0;
	}


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

	//描画
	int draw()
	{

		return 0;
	}

};
