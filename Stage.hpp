﻿#pragma once
#include <Siv3D.hpp>
#include "SceneData.hpp"
#include "input.hpp"
#include "PlayerManager.hpp"
#include "EnemyManager.hpp"
#include "BulletManager.hpp"

//ステージに関する処理
class Stage : public App::Scene
{

private:

	PlayerInput input;
	PlayerManager playermanager;
	EnemyManager enemymanager;
	BulletManager bulletmanager;



public:

	Stage(const InitData& init) : IScene{ init }
	{
		//テスト
		Array<Vec2> movecommandtest = { Vec2(50, 50), Vec2(200, 300), Vec2(600, -10) };
		enemymanager.EnemySpawn(Vec2(50, 50), EnemyName::glockdronenomove);
		enemymanager.EnemySpawn(Vec2(400, 50), EnemyName::glockdrone, movecommandtest);

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
		enemymanager.Update(&bulletmanager, playermanager.PlayerPos(), deltatime);

		//弾処理
		bulletmanager.Update(deltatime);



	}

	//描画処理
	void draw() const override
	{



	}

};
