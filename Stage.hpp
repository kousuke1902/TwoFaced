#pragma once
#include <Siv3D.hpp>
#include "SceneData.hpp"
#include "input.hpp"
#include "PlayerManager.hpp"
#include "EnemyManager.hpp"
#include "BulletManager.hpp"
#include "GoalRule.hpp"
#include "StageInformation.hpp"

//ステージに関する処理
class Stage : public App::Scene
{

private:

	PlayerInput input;//プレイヤーインプット
	PlayerManager playermanager;//プレイヤー処理
	EnemyManager enemymanager;//エネミー処理
	BulletManager bulletmanager;//弾処理
	GameRule *gamerule;//ステージクリア，ゲームオーバー判定
	//EnemyStartUpInformation startup;//エネミーのスポーン情報


public:

	Stage(const InitData& init) : IScene{ init }
	{
		//テスト
		//StageInformation(U"test.csv", gamerule, startup);

	}


	//更新処理
	void update()override
	{

		ClearPrint();
		Print << U"mode:" << playermanager.PlayerMode();

		//入力状態の更新
		input.Update();

		//処理フレーム間の経過時間
		const double deltatime = Scene::DeltaTime();

		//プレイヤー処理
		playermanager.Update(&bulletmanager, &input, deltatime);

		//エネミー処理
		//エネミーの更新
		enemymanager.Update(&bulletmanager, playermanager.PlayerPos(), deltatime);
		//エネミーのスポーン
		/*if (!startup.spawntimes.empty())
		{


		}*/

		//弾処理
		bulletmanager.Update(deltatime);



	}

	//描画処理
	void draw() const override
	{



	}

};
