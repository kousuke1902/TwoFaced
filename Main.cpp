#include <Siv3D.hpp> // OpenSiv3D v0.6.10
#include "input.hpp"
#include "PlayerManager.hpp"
#include "BulletManager.hpp"

void Main()
{
	// 背景の色を設定する | Set the background color
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });

	static PlayerInput input;
	//Player player;
	PlayerManager playermanager;
	BulletManager bulletmanager;
	

	while (System::Update())
	{
		ClearPrint();

		//処理フレーム間の経過時間
		const double deltatime = Scene::DeltaTime();

		//プレイヤー処理
		playermanager.Update(bulletmanager, input, deltatime);

		//弾処理
		bulletmanager.Update(deltatime);
		bulletmanager.CreateStraight(Vec2(300, 400), 10, 5, Vec2(0.0, -1.0));
		Print << bulletmanager.readBulletsize();

	}
}

