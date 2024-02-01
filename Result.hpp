﻿#pragma once
#include <Siv3D.hpp>
#include "SceneData.hpp"
#include "input.hpp"

class Result : public App::Scene
{

private:
	PlayerInput input;
	Font font;

public:

	Result(const InitData& init): IScene{ init }
	{
		font = Font{ FontMethod::MSDF , 48 };
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
		Print << getData().ResultLife;
		font(U"Score: {}"_fmt(getData().ResultLife)).drawAt(300, 40);

	}

};
