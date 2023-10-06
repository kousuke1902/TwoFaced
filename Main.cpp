﻿#include <Siv3D.hpp> // OpenSiv3D v0.6.10
#include "input.hpp"
#include "PlayerManager.hpp"
#include "BulletManager.hpp"

void Main()
{
	// 背景の色を設定する | Set the background color
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });

	static PlayerInput input;
	//Player player;
	auto player = Esquire(Vec2(100, 100));
	BulletManager bulletmanager;
	

	while (System::Update())
	{
		Vec2 y = player.readPos();
		ClearPrint();
		Print << y;
		Print << U"mode:" << player.readMode();

		const double deltatime = Scene::DeltaTime();

		//プレイヤー処理
		//移動処理

		//射撃


		//処理フレーム間の経過時間
		

		player.Update(input, deltatime);

		Circle{ y, 4 }.draw(Palette::White);

	}
}

