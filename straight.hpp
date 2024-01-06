#pragma once
#include <Siv3D.hpp>
#include "movecommand.hpp"

//直進移動
class Straight : public MoveCommand
{
public:

	Straight(Vec2 setPos) : MoveCommand(setPos)
	{


	}

	//移動ベクトル
	Vec2 moveVector(Vec2 nowPos, Vec2 playerPos, double deltatime)override
	{
		Flagcheck(nowPos);
		return Vec2(targetPos - nowPos).setLength(1.0);
	}


};
