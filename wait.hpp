#pragma once
#include <Siv3D.hpp>
#include "movecommand.hpp"

class Wait : public MoveCommand
{

public:

	Wait(double setsec) : MoveCommand(MoveType::wait)
	{

		targetPos = Vec2{ setsec, 0.0 };
	}

	bool checkFlag(Vec2 nowPos = Vec2(0.0, 0.0))override
	{
		if (targetPos.x <= 0.0)return true;
		return false;
	}

	//この命令で行う行動
	Vec2 moveAction(Vec2 playerPos, double deltatime)override
	{
		targetPos.x -= deltatime;
		return Vec2(0.0, 0.0);
	}

};
