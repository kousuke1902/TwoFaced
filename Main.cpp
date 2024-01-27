#include <Siv3D.hpp>
#include "SceneData.hpp"
#include "Title.hpp"
#include "Stage.hpp"
#include "Result.hpp"

void Main()
{
	// 背景の色を設定する | Set the background color
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });
	App manager;

	manager.add<Title>(State::Title);
	manager.add<Stage>(State::Stage);
	manager.add<Result>(State::Result);

	manager.init(State::Stage);

	while (System::Update())
	{
		if (not manager.update())break;
		

	}
}

