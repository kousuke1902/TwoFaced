#pragma once
#include <Siv3D.hpp>
#include "SceneData.hpp"
#include "stagelist.hpp"
#include "input.hpp"

//ステージ選択画面
class StageSelect : public App::Scene
{

private:
	Array<StageList> stagelist;//ステージ一覧
	PlayerInput input;//入力
	double downtime;//入力時間
	int cursol;//カーソル位置
	Font font;//ステージ名表記

public:

	StageSelect(const InitData& init) : IScene{ init }
	{
		CSV csv{ U"stagelist.csv" };
		
		//CSVからステージ一覧情報の取り込み
		for (size_t row = 0; row < csv.rows(); ++row)
		{
			stagelist << StageList(csv[row][0], csv[row][1], csv[row][2], csv[row][3]);
		}

		downtime = 0.0;
		cursol = 0;
		font = Font{ 50 };
	}

	void update() override
	{
		
		//処理フレーム間の経過時間
		const double deltatime = Scene::DeltaTime();

		downtime -= deltatime;
		downtime = Max(0.0, downtime);

		//移動方向を検知してカーソル移動の検知を行う
		if (input.MoveVectorLogic().y > 0.5)
		{
			if (downtime == 0.0)
			{
				downtime = 1.0;
				cursol--;
			}
		}
		else if (input.MoveVectorLogic().y < -0.5)
		{
			if (downtime == 0.0)
			{
				downtime = 1.0;
				cursol++;
			}
		}
		else downtime = 0.0;

		//カーソル位置の超過検知
		if (cursol < 0)cursol = 0;
		else if (cursol > stagelist.size())cursol = stagelist.size();

		//テキストマーカー
		Rect{ -20, 90, 400, 50 }.draw(Palette::Royalblue);
		Rect{ 40, 200, 400, 50 }.draw(Palette::Royalblue);
		Rect{ 100, 310, 400, 50 }.draw(Palette::Royalblue);
		Rect{ 160, 420, 400, 50 }.draw(Palette::Royalblue);
		Rect{ 210, 530, 400, 50 }.draw(Palette::Royalblue);
		

	}

	void draw() const override
	{


	}

};
