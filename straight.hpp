#pragma once
#include <Siv3D.hpp>
#include "movecommand.hpp"

//直進移動
class Straight : public MoveCommand
{
protected:



public:

	Straight(Vec2 settargetPos) : MoveCommand(settargetPos)
	{


	}

	Straight(Vec2 settargetPos, Vec2 setstartPos) : MoveCommand(settargetPos)
	{

		moveVector = Vec2(targetPos - setstartPos).setLength(1.0);
	}

	//命令開始前の設定
	int setup(Vec2 setstartPos)override
	{
		moveVector = Vec2(targetPos - setstartPos).setLength(1.0);
		return 1;
	}

	//この命令で行う行動
	Vec2 moveAction(Vec2 playerPos, double deltatime)override
	{
		return moveVector * deltatime;
	}


};
