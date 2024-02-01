#pragma once
#include <Siv3D.hpp>
#include "SceneData.hpp"
#include "input.hpp"

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

	}

	// 描画関数
	void draw() const override
	{
		ClearPrint();
		font(Evalute).drawAt(300, 400);
		font(U"残耐久値 : {:.2f}%"_fmt(Score)).drawAt(300, 500);
	}

};
