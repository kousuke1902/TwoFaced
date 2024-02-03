#pragma once
#include <Siv3D.hpp>
#include "SceneData.hpp"
#include "input.hpp"

//タイトル画面
class Title : public App::Scene
{
private:
	Font font;
	PlayerInput input;

public:

	Title(const InitData& init) : IScene{ init }
	{
		font = Font{ FontMethod::MSDF , 48 };

	}

	void update() override
	{
		if (input.pressFire())
		{
			changeScene(State::StageSelect);

		}
		font(U"Two Faced").drawAt(300, 200);
		font(U"Push Shot Buttom").drawAt(300, 500);

	}

	void draw() const override
	{


	}

};
