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
	Texture title;//タイトルロゴ
	Texture o;//タイトルロゴOの字

public:

	Title(const InitData& init) : IScene{ init }
	{
		font = Font{ FontMethod::MSDF , 48 };
		title = Texture{ Image{ U"img/Title.png"}.scaled(0.7) };
		int rand = Random(2);
		if (rand == 0)o = Texture{ Image{ U"img/player0.png"}.scaled(0.5) };
		else if (rand == 1)o = Texture{ Image{ U"img/player1.png"}.scaled(0.5) };
		else if (rand == 2)o = Texture{ Image{ U"img/cursorR.png"}.scaled(0.5) };

	}

	void update() override
	{
		if (input.pressFire())
		{
			changeScene(State::StageSelect);

		}
		title.drawAt(500.0, 300.0);
		o.drawAt(470.0, 220.0);
		font(U"Push Shot Buttom").drawAt(500, 600, HSV{ 0.0, 0.0, 0.0, Periodic::Sine0_1(5s) });

	}

	void draw() const override
	{


	}

};
