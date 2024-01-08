#pragma once
#include <Siv3D.hpp>
#include "character.hpp"
#include "straight.hpp"
#include "wait.hpp"
#include "kill.hpp"

class Enemy : public Character
{

protected:

	Array<MoveCommand*> movecommand;//移動命令

public:

	Enemy(Vec2 pos, double boxsize, double life, double speed, double setcooltime) : Character(pos, boxsize, life, speed, setcooltime)
	{
		movecommand.clear();

	}

	Enemy(Vec2 pos, double boxsize, double life, double speed, double setcooltime, Array<MoveCommand*> setmovecommand) : Character(pos, boxsize, life, speed, setcooltime)
	{
		movecommand = setmovecommand;

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
			if (movecommand.front()->checkFlag(HitBox.center()))
			{
				movecommand.pop_front();

				if (!movecommand.empty())
				{
					if (movecommand.front()->readType() == MoveType::kill) Life = 0;
					else movecommand.front()->setup(HitBox.center());
				}
			}

			else movePos(movecommand.front()->moveAction(playerPos, deltatime), deltatime);
			

		}
		return 0;
	}

};
