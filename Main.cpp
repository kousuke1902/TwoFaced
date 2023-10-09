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

		//処理フレーム間の経過時間
		const double deltatime = Scene::DeltaTime();

		//プレイヤー処理
		playermanager.Update(bulletmanager, input, deltatime);


		


	}
}

