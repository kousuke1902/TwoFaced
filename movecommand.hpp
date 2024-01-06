#pragma once
#include <Siv3D.hpp>

enum class MoveType
{
	straight,
	sin,
	curve,
	stalker,
	wait,
	kill

};

//エネミーの移動制御
class MoveCommand
{
protected:

	Vec2 targetPos;//目標座標
	bool deleteFlag;//行動削除フラグ

	int Flagcheck(Vec2 nowPos)
	{
		if (abs(Vec2(targetPos - nowPos).length()) <= 1.0)deleteFlag = true;
		return 0;
	}

public:

	MoveCommand()
	{
		targetPos = Vec2(0.0, 0.0);
		deleteFlag = false;

	}

	MoveCommand(Vec2 setPos)
	{
		targetPos = setPos;
		deleteFlag = false;
	}

	//行動削除フラグの閲覧
	bool readFlag()
	{

		return deleteFlag;
	}

	//移動ベクトル
	virtual Vec2 moveVector(Vec2 nowPos, Vec2 playerPos, double deltatime)
	{
		
		
		return targetPos;

	}

};
