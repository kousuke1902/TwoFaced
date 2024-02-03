#pragma once
#include <Siv3D.hpp>
#include "SceneData.hpp"
#include "input.hpp"

//リザルト画面
class Result : public App::Scene
{

private:
	PlayerInput input;
	Font font;
	double Score;
	String Evalute;

public:

	Result(const InitData& init): IScene{ init }
	{
		font = Font{ FontMethod::MSDF , 48 };
		Score = getData().ResultLife / 100.0 * 100;
		if (Score >= 90)Evalute = U"Advanced";
		else if (Score >= 80)Evalute = U"Basic";
		else if (Score >= 70)Evalute = U"Check";
		else if (Score >= 60)Evalute = U"Delayed";
		else if (Score >= 50)Evalute = U"Error";
		else Evalute = U"Fatal";
	}

	// 更新関数
	void update() override
	{

		if (input.pressFire())
		{
			changeScene(State::StageSelect);
		}
		else if (input.downModechange())
		{
			changeScene(State::Stage);
		}

	}

	// 描画関数
	void draw() const override
	{
		ClearPrint();
		font(U"実戦試験評価").drawAt(300, 100);
		font(Evalute).drawAt(300, 200);
		font(U"残耐久値 : {:.2f}%"_fmt(Score)).drawAt(300, 300);
	}

};
