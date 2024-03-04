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


};
