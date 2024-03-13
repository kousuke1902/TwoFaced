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

//行動命令の格納クラス
class MoveCommand
{
private:

	String type;//移動タイプ
	Vec2 Pos;//座標

public:

	MoveCommand(String settype, Vec2 setPos)
	{
		type = settype;
		Pos = setPos;
	}

	MoveCommand()
	{
		type = U"wait";
		Pos = Vec2{ 0.0,0.0 };
	}

	//移動タイプの閲覧
	String readType()
	{
		return type;
	}

	//移動タイプの設定
	int setType(String x)
	{
		type = x;
		return 0;
	}

	//パラメータの確認
	Vec2 readParamater()
	{
		return Pos;
	}

	//パラメータの設定
	int addParamaterX(double x)
	{
		Pos.x += x;
		return 0;
	}

	int addParamaterY(double x)
	{
		Pos.y += x;
		return 0;
	}

};
