#pragma once
#include <Siv3D.hpp>
#include "movecommand.hpp"

//csvの1行ごとに格納されているデータの格納と処理
class Spawndata
{
private:
		
	String name;
	Vec2 spawnPos;


public:
	double spawntime;
	Array<MoveCommand> commands;

	Spawndata(double settime, String setname, Vec2 setPos, Array<MoveCommand> setcommands)
	{
		spawntime = settime;
		name = setname;
		spawnPos = setPos;
		commands = setcommands;
	}

	Spawndata(double settime, String setname, Vec2 setPos)
	{
		spawntime = settime;
		name = setname;
		spawnPos = setPos;
		commands << MoveCommand();
	}

	//スポーン時間の閲覧
	double readSpawntime()
	{
		return spawntime;
	}

	//エネミー名の閲覧
	String readName()
	{
		return name;
	}

	//スポーン座標の閲覧
	Vec2 readSpawnPos()
	{
		return spawnPos;
	}

	//スポーン座標xの操作
	int addSpaownPosX(double x)
	{
		spawnPos.x += x;
		return 0;
	}

	//スポーン座標yの操作
	int addSpaownPosY(double x)
	{
		spawnPos.y += x;
		return 0;
	}
};
