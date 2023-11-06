#pragma onece
#include <Siv3D.hpp>
#include "character.hpp"

class Enemy : public Character
{

protected:

	Array<int*> AttackCommand;//攻撃命令
	Array<Vec2> MoveCommand;//移動命令

public:


	//移動命令を閲覧する
	Array<Vec2> showMoveCommand()
	{
		return MoveCommand;
	}

	//移動命令を書き込む
	int writeMoveCommand(Vec2 command)
	{
		MoveCommand << command;
		return 0;

	}

	int writeMoveCommand(Array<Vec2> command)
	{
		for (int32 it = 0; it < command.size(); ++it)MoveCommand.push_back(command[it]);
		return 1;
	}

	//移動命令のリストを上書き
	int overwriteMoveCommand(Array<Vec2> command)
	{
		MoveCommand = command;
		return 0;
	}


};
