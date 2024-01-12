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
	CSV csv;//読み込みファイル

public:

	StageInformation(FilePath csvpath ,GameRule* gamerule,EnemyStartUpInformation startup)
	{
		csv = CSV{ csvpath };



		


	}

	//ゲームルールを設定する
	int setGameRule(GameRule* gamerule)
	{
		//ゲームルールの確認
		if (csv[0][0] == U"Goal")
		{
			gamerule = new GoalRule(Parse<double>(csv[0][1]));

		}

		else gamerule = new GoalRule(10.0);

		return 0;
	}

	//エネミーを読み込む
	int loadspawnEnemies(Array<EnemyStartUpInformation*> startup)
	{

		//行ごとに読み込み
		for (size_t row = 1; row < csv.rows(); ++row)
		{
			//スポーン時間読み込み
			double spawntime = Parse<double>(csv[row][0]);

			//エネミーキャラクター読み込み
			EnemyName name;

			if (csv[row][1] == U"glockdrone")
			{

				name = EnemyName::glockdrone;
			}
			else name = EnemyName::glockdronenomove;

			//初期スポーン座標
			Vec2 startPos = Parse<Vec2>(csv[row][2]);

			//移動命令
			Array<MoveCommand*> bufcommand;
			bufcommand.clear();

			//命令読み込み
			for (size_t column = 3; column < csv.columns(row); ++column)
			{
				//直進
				if (csv[row][column] == U"straight")
				{
					bufcommand << new Straight(Parse<Vec2>(csv[row][column + 1]));
					++column;
				}
				//待機
				else if (csv[row][column] == U"wait")
				{
					bufcommand << new Wait(Parse<double>(csv[row][column + 1]));
					++column;
				}
				//削除
				else if (csv[row][column] == U"kill")
				{
					bufcommand << new Kill;

				}
			}

			startup << new EnemyStartUpInformation(spawntime, name, startPos, bufcommand);

		}

		return 0;
	}

};
