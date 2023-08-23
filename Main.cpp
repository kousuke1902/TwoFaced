# include <Siv3D.hpp> // OpenSiv3D v0.6.10
# include "input.hpp"
# include "player.hpp"
# include "esquire.hpp"

void Main()
{
	// 背景の色を設定する | Set the background color
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });

	static PlayerInput input;
	Player player;

	player.writePos(Vec2(50, 50));
	player.writeSpeed(100);

	while (System::Update())
	{
		Vec2 x = input.KeyInputMoveVector();
		Vec2 y = player.readPos();
		ClearPrint();
		Print << x;
		Print << y;

		//処理フレーム間の経過時間
		const double deltatime = Scene::DeltaTime();

		player.movePos(x, deltatime);

		Circle{ y, 4 }.draw(Palette::White);

	}
}

