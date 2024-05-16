#pragma once
#include <Siv3D.hpp>
#include "SceneData.hpp"
#include "input.hpp"

//リザルト画面
class Result : public App::Scene
{

private:
	PlayerInput input;
	Font font;//描画文字
	double Score;//スコア
	Texture Evalute; 

public:

	Result(const InitData& init): IScene{ init }
	{
		font = Font{ FontMethod::MSDF , 48 };
		Score = getData().ResultLife;
		if (Score >= 90)Evalute = Texture { Image{ Resource(U"img/yu.png") }.scaled(0.8) };
		else if (Score >= 75)Evalute = Texture{ Image{ Resource(U"img/ryo.png") }.scaled(0.8) };
		else if (Score >= 50)Evalute = Texture{ Image{ Resource(U"img/ka.png") }.scaled(0.8) };
		else Evalute = Texture{ Image{ Resource(U"img/fuka.png") }.scaled(0.8) };
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
		RoundRect{ Arg::center(500.0, 390.0), 640.0, 460.0, 5.0 }.draw(Palette::White).drawFrame(5.0, Palette::Black);
		font(U"評価").drawAt(500.0, 200.0, Palette::Black);
		Evalute.drawAt(500.0, 350.0);
		font(U"残り体力").drawAt(500.0, 530.0, Palette::Black);
		font(U"{:.2f} % "_fmt(Score)).drawAt(500, 580, Palette::Black);

		//font(U"Aボタン/Spaceキーでステージセレクトへ").drawAt(250, 750, Palette::Black);
		//font(U"Bボタン/Vキーでリトライ").drawAt(700, 750, Palette::Black);
	}

};
