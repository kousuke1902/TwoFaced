#pragma once
#include <Siv3D.hpp>
#include "EnemyManager.hpp"

//ルール一覧
enum class RuleName
{
	Goal,
	AllDelete,
	BossDelete,
	Defence

};

//ステージのクリアルールの基本
class GameRule
{

protected:

	double Time;//ステージを起動してからの時間
	Array<EnemyName> EnemyCount;//撃破エネミー数

public:

	GameRule()
	{
		Time = 0.0;
		EnemyCount.clear();
	}

	//撃破エネミーの追加
	int AddEnemyCount(EnemyName x)
	{
		EnemyCount.push_back(x);
		return 0;
	}


	//ステージクリア判定
	virtual bool Clear()
	{
		return true;

	}

	//ゲームオーバー判定
	virtual bool GameOver()
	{
		return false;

	}



};
