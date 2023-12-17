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
	BulletManager bulletmanager;
	Array<Vec2> movecommandtest = { Vec2(50, 50), Vec2(200, 300) };

	enemymanager.EnemySpawn(Vec2(50, 50), EnemyName::glockdronenomove);
	enemymanager.EnemySpawn(Vec2(400, 50), EnemyName::glockdrone, movecommandtest);

	while (System::Update())
	{
		ClearPrint();
		Print << U"in update" << enemymanager.readEnemy(1)->readMoveCommand();

		//処理フレーム間の経過時間
		const double deltatime = Scene::DeltaTime();

		//プレイヤー処理
		playermanager.Update(&bulletmanager, input, deltatime);

		//エネミー処理
		enemymanager.Update(&bulletmanager, playermanager.PlayerPos(), deltatime);

		//弾処理
		bulletmanager.Update(deltatime);


	}
}

