#pragma once
#include <Siv3D.hpp>
#include "movecommand.hpp"

class Wait : public MoveCommand
{

private:
	double sec;

public:

	Wait(double setsec) : MoveCommand(MoveType::wait)
	{

		sec = setsec;
	}

	bool checkFlag(Vec2 nowPos = Vec2(0.0, 0.0))override
	{
		if (sec <= 0.0)return true;
		return false;
	}

	//この命令で行う行動
	Vec2 moveAction(Vec2 playerPos, double deltatime)override
	{
		sec -= deltatime;
		return Vec2(0.0, 0.0);
	}

};
