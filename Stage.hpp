#pragma once
#include <Siv3D.hpp>
#include "SceneData.hpp"
#include "input.hpp"
#include "PlayerManager.hpp"
#include "EnemyManager.hpp"
#include "BulletManager.hpp"
#include "GoalRule.hpp"


//ステージに関する処理
class Stage : public App::Scene
{

private:

	PlayerInput input;//プレイヤーインプット
	PlayerManager playermanager;//プレイヤー処理
	EnemyManager enemymanager;//エネミー処理
	BulletManager bulletmanager;//弾処理
	GameRule* gamerule;//ステージクリア，ゲームオーバー判定
	Array<EnemyStartUpInformation*> startup;//エネミーの初期設定情報
	FilePath stagefile;//ステージのファイル情報

	//ゲームルールを設定する
	int setGameRule(CSV csv)
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
	int loadspawnEnemies(CSV csv)
	{

		//行ごとに読み込み
		for (size_t row = 1; row < csv.rows(); ++row)
		{
			//スポーン時間読み込み
			double spawntime = Parse<double>(csv[row][0]);

			//エネミーキャラクター読み込み
			int enemyID;

			if (csv[row][1] == U"glockdrone")
			{

				enemyID = (int)EnemyName::glockdrone;
			}
			else enemyID = (int)EnemyName::glockdronenomove;

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

			startup << new EnemyStartUpInformation(spawntime, enemyID, startPos, bufcommand);

		}

		return 0;
	}

public:

	Stage(const InitData& init) : IScene{ init }
	{
		//テスト
		stagefile = getData().Stagepath;
		CSV csv{ stagefile };
		setGameRule(csv);
		loadspawnEnemies(csv);
	
	}

	//更新処理
	void update()override
	{

		ClearPrint();

		//処理フレーム間の経過時間
		const double deltatime = Scene::DeltaTime();

		//クリア判定
		if (gamerule->Clear())
		{
			getData().ResultLife = playermanager.PlayerLife();
			changeScene(State::Result);
		}

		//ゲームオーバー判定
		if (gamerule->GameOver() || !playermanager.deadFlag())
		{


		}

		//入力状態の更新
		input.Update();

		//プレイヤー処理
		playermanager.Update(&bulletmanager, &input, deltatime);

		//エネミー処理
		//エネミーの更新
		enemymanager.Update(&bulletmanager, &playermanager, deltatime);
		//エネミーのスポーン
		if (!startup.empty())
		{
			//スポーン時間を超過
			if (gamerule->readTimer() > startup.front()->readSpawnTime())
			{
				enemymanager.EnemySpawn(startup.front());
				startup.pop_front();
			}

		}

		//弾処理
		bulletmanager.Update(deltatime);

		//時間経過
		gamerule->addTimer(deltatime);

	}

	//描画処理
	void draw() const override
	{



	}

};
