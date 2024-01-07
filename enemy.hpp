#pragma once
#include <Siv3D.hpp>
#include "character.hpp"
#include "Straight.hpp"

class Enemy : public Character
{

protected:

	Array<MoveCommand*> movecommand;//移動命令

public:


	Enemy()
	{
		movecommand.clear();

	}

	//移動命令を閲覧する
	Array<MoveCommand*> readMoveCommand()
	{
		return movecommand;
	}

	//移動命令を書き込む
	int writeMoveCommand(MoveCommand* command)
	{
		movecommand << command;
		return 0;

	}
	//移動命令を書き込む
	int writeMoveCommand(Array<MoveCommand*> commands)
	{
		for (int it = 0; it < commands.size(); ++it)movecommand.push_back(commands[it]);
		return 1;
	}

	//移動命令のリストを上書き
	int overwriteMoveCommand(Array<MoveCommand*> commands)
	{
		movecommand.clear();
		movecommand = commands;
		return 0;
	}

	//エネミー移動
	int moveEnemy(Vec2 playerPos, double deltatime)
	{
		if (!movecommand.empty())
		{
			MoveCommand* command = movecommand.front();
			if(command->readFlag()) movecommand.pop_front();
			movePos(command->moveVector(HitBox.center(), playerPos, deltatime), deltatime);
			

		}
		return 0;
	}

};
