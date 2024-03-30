#include <Siv3D.hpp>
#include "SceneData.hpp"
#include "Title.hpp"
#include "StageSelect.hpp"
#include "Stage.hpp"
#include "Result.hpp"

void Main()
{

	Window::Resize(1000, 800);

	
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });
	App manager;

	manager.add<Title>(State::Title);
	manager.add<StageSelect>(State::StageSelect);
	manager.add<Stage>(State::Stage);
	manager.add<Result>(State::Result);

	manager.init(State::StageSelect);

	while (System::Update())
	{
		if (not manager.update())break;
		

	}
}

