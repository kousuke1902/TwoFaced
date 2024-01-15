#pragma once
#include <Siv3D.hpp>
#include "SceneData.hpp"

class Result : public App::Scene
{

public:

	Result(const InitData& init): IScene{ init }
	{

	}

	// 更新関数
	void update() override
	{



	}

	// 描画関数
	void draw() const override
	{
		Print << getData().ResultLife;
		FontAsset(U"ScoreFont")(U"Score: {}"_fmt(getData().ResultLife)).draw(40, 40);

	}

};
