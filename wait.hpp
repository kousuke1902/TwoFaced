#pragma once
#include <Siv3D.hpp>
#include "movecommand.hpp"

class Wait : public MoveCommand
{

private:
	double sec;

public:

	Wait(double setsec)
	{

		sec = setsec;
	}

	//移動ベクトル
	Vec2 moveVector(Vec2 nowPos, Vec2 playerPos, double deltatime)override
	{
		sec -= deltatime;
		if (sec <= 0.0)deleteFlag = true;
		return Vec2(0.0, 0.0);
	}

};
