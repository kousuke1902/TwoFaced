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

	double Timer;//ステージを起動してからの時間
	Array<EnemyName> EnemyCount;//撃破エネミー数

public:

	GameRule()
	{
		Timer = 0.0;
		EnemyCount.clear();
	}


	//経過時間の閲覧
	double readTimer()
	{
		return Timer;
	}

	//時間の加算
	int addTimer(double deltatime)
	{
		Timer += deltatime;
		return 0;
	}

	//撃破エネミーの追加
	int AddEnemyCount(EnemyName x)
	{
		EnemyCount << x;
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
