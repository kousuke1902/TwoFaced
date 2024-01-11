#pragma once
#include <Siv3D.hpp>
#include "GoalRule.hpp"
#include "EnemyStartUpInformation.hpp"
#include "straight.hpp"
#include "wait.hpp"
#include "kill.hpp"

//ステージ情報の読み込み
class StageInformation
{
private:

	//GameRule* gamerule;//ゲームルール


public:

	StageInformation(FilePath csvpath ,GameRule* gamerule,EnemyStartUpInformation startup)
	{
		const CSV csv{ csvpath };

		//ゲームルールの確認
		if (csv[0][0] == U"Goal")
		{
			gamerule = new GoalRule(Parse<double>(csv[0][1]));

		}

		else gamerule = new GoalRule(10.0);

		//エネミーリスト読み込み
		for (size_t row = 1; row < csv.rows(); ++row)
		{
			//スポーン時間読み込み
			//startup.spawntimes << Parse<double*>(csv[row][0]);

			//エネミーキャラクター読み込み
			
			if (csv[row][1] == U"glockdrone")
			{
				
				//startup.name << EnemyName::glockdrone;
			}

			//初期スポーン座標
			//startup.spawnPos << Parse<Vec2*>(csv[row][2]);

			//移動命令
			Array<MoveCommand*> bufcommand;
			bufcommand.clear();

			for (size_t column = 3; column < csv.columns(row); ++column)
			{
				//直進
				if (csv[row][column] == U"straight")
				{
					//bufcommand << new Straight(Parse<Vec2>(csv[row][column + 1]));
					++column;
				}
				//待機
				else if (csv[row][column] == U"wait")
				{
					//bufcommand << new Wait(Parse<double>(csv[row][column + 1]));
					++column;
				}
				//削除
				else if (csv[row][column] == U"kill")
				{
					//bufcommand << new Kill;

				}
			}

			startup.movecomands << bufcommand;
		}
	}


};
