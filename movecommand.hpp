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
	Vec2 moveVector;//移動ベクトル
	MoveType Type;//行動種類



public:

	MoveCommand(MoveType setType)
	{
		targetPos = Vec2(0.0, 0.0);
		moveVector = Vec2(0.0, 0.0);
		Type = setType;

	}

	MoveCommand(Vec2 settargetPos, MoveType setType)
	{
		targetPos = settargetPos;
		moveVector = Vec2(0.0, 0.0);
		Type = setType;
	}

	//行動方法の閲覧
	MoveType readType()
	{
		return Type;
	}

	//行動削除フラグの確認
	virtual bool checkFlag(Vec2 nowPos)
	{
		if (abs(Vec2(targetPos - nowPos).length()) <= 1.0)return true;
		return false;
	}

	//命令開始前の設定
	virtual int setup(Vec2 setstartPos)
	{

		return 0;
	}

	//この命令で行う行動
	virtual Vec2 moveAction(Vec2 playerPos, double deltatime)
	{
		
		
		return Vec2(0.0, 0.0);

	}

};
