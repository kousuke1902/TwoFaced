#pragma once
#include <Siv3D.hpp>
#include "EnemyManager.hpp"
#include "movecommand.hpp"

class EnemyStartUpInformation
{
private:

	double spawntime;//エネミーのスポーン時間
	Vec2 spawnPos;//エネミーの初期スポーン座標
	EnemyName name;//スポーンするエネミーの名称
	Array<MoveCommand*> movecomands;//行動命令の列挙

public:

	EnemyStartUpInformation(double setspawntime, EnemyName setname, Vec2 setspawnPos,  Array<MoveCommand*> setmovecommands)
	{
		spawntime = setspawntime;
		name = setname;
		spawnPos = setspawnPos;
		movecomands = setmovecommands;
	}

};
