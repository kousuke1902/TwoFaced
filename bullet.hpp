#pragma once
#include <Siv3D.hpp>

//弾の基本クラス
class Bullet
{
private:

	Vec2 Pos;//弾の座標
	double Speed;//弾の速度
	double LifeSpan;//弾の時間的寿命

public:

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

};
