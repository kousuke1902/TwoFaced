#pragma once
#include <Siv3D.hpp>
#include "EnemyManager.hpp"
#include "movecommand.hpp"

class EnemyStartUpInformation
{
private:

	double spawntime;//エネミーのスポーン時間
	int enemyID;//スポーンするエネミーの名称
	Vec2 spawnPos;//エネミーの初期スポーン座標
	Array<MoveCommand*> movecomands;//行動命令の列挙

public:

	EnemyStartUpInformation(double setspawntime, int setID, Vec2 setspawnPos,  Array<MoveCommand*> setmovecommands)
	{
		spawntime = setspawntime;
		enemyID = setID;
		spawnPos = setspawnPos;
		movecomands = setmovecommands;
	}

	//スポーン時間の閲覧
	double readSpawnTime()
	{
		return spawntime;
	}

	//スポーンエネミーの閲覧
	int readID()
	{
		return enemyID;
	}

	//スポーン座標の閲覧
	Vec2 readspawnPos()
	{
		return spawnPos;
	}

	//行動命令の閲覧
	Array<MoveCommand*> readMoveCommands()
	{
		return movecomands;
	}
};
