#pragma onece
#include <Siv3D.hpp>
#include "character.hpp"

class Enemy : public Character
{

protected:

	Array<int*> AttackCommand;//攻撃命令
	Array<Vec2> MoveCommand;//移動命令

public:


	//異動命令を閲覧する
	Array<Vec2> ShowMoveCommand()
	{
		return MoveCommand;
	}

};
