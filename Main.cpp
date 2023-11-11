#include <Siv3D.hpp> // OpenSiv3D v0.6.10
#include "input.hpp"
#include "PlayerManager.hpp"
#include "EnemyManager.hpp"
#include "BulletManager.hpp"

void Main()
{
	// 背景の色を設定する | Set the background color
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });

	static PlayerInput input;
	PlayerManager playermanager;
	EnemyManager enemymanager;
	BulletManager playerbullets, enemiesbullets, storongbullets;

	enemymanager.EnemySpawn(Vec2(50, 50), 0);
	enemymanager.EnemySpawn(Vec2(450, 50), 0);

	while (System::Update())
	{
		ClearPrint();

		//処理フレーム間の経過時間
		const double deltatime = Scene::DeltaTime();

		//プレイヤー処理
		playermanager.Update(&playerbullets, input, deltatime);

		//エネミー処理
		enemymanager.Update(&enemiesbullets, playermanager.PlayerPos(), deltatime);

		//弾処理
		playerbullets.Update(deltatime);
		enemiesbullets.Update(deltatime);
		storongbullets.Update(deltatime);


	}
}

