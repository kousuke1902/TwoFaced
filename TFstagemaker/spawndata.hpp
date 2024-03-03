#pragma once
#include <Siv3D.hpp>
#include "movecommand.hpp"

//csvの1行ごとに格納されているデータの格納と処理
class Spawndata
{
private:

	double spawntime;
	String name;
	Vec2 spawnPos;


public:

	Array<MoveCommand> commands;

	Spawndata(double settime, String setname, Vec2 setPos, Array<MoveCommand> setcommands)
	{
		spawntime = settime;
		name = setname;
		spawnPos = setPos;
		commands = setcommands;
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



};
