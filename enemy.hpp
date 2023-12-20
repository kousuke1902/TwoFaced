#pragma once
#include <Siv3D.hpp>
#include "character.hpp"

class Enemy : public Character
{

protected:

	Array<int*> AttackCommand;//攻撃命令
	Array<Vec2> MoveCommand;//移動命令

public:


	//移動命令を閲覧する
	Array<Vec2> readMoveCommand()
	{
		return MoveCommand;
	}

	//移動命令を書き込む
	int writeMoveCommand(Vec2 command)
	{
		MoveCommand << command;
		return 0;

	}
	//移動命令を書き込む
	int writeMoveCommand(Array<Vec2> commands)
	{
		for (int it = 0; it < commands.size(); ++it)MoveCommand.push_back(commands[it]);
		return 1;
	}

	//移動命令のリストを上書き
	int overwriteMoveCommand(Array<Vec2> commands)
	{
		MoveCommand.clear();
		MoveCommand = commands;
		return 0;
	}

	//エネミー移動
	int moveEnemy(double deltatime)
	{
		if (!MoveCommand.empty())
		{
			Vec2 vector = MoveCommand.front() - HitBox.center();
			if(Abs(vector.length()) <= 1.0) MoveCommand.pop_front();
			movePos(vector.setLength(1.0), deltatime);

		}
		return 0;
	}

};
