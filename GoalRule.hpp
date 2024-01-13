#pragma once
#include <Siv3D.hpp>
#include "GameRule.hpp"

//ゴール地点まで進んだらクリア
class GoalRule : public GameRule
{

private:

	double ClearTime;//クリア時間

public:
	
	GoalRule(double setTime)
	{
		ClearTime = setTime;

	}

	//ステージクリア判定
	bool Clear() override
	{
		if (Timer >= ClearTime)return true;
		else return false;


	}


};
