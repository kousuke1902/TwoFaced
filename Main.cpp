# include <Siv3D.hpp> // OpenSiv3D v0.6.10
# include "player.hpp"

void Main()
{
	// 背景の色を設定する | Set the background color
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });

	

	Player player;

	player.writePos(Vec2(50, 50));

	while (System::Update())
	{
		ClearPrint();
		//Print << player.KeyInputMoveVector();

		//処理フレーム間の経過時間
		const double deltatime = Scene::DeltaTime();

		//player.movePos(KeyD.pressed(), KeyA.pressed(), KeyS.pressed(), KeyW.pressed(), deltatime);


		//Circle{ player.readPos(), 4 }.draw(Palette::White);

	}
}

