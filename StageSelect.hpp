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
		font = Font{ 30 };
	}

	void update() override
	{
		
		//処理フレーム間の経過時間
		const double deltatime = Scene::DeltaTime();

		downtime = Max(0.0, downtime);

		//移動方向を検知してカーソル移動の検知を行う
		if (input.MoveVectorLogic().y > 0.5)
		{
			if (downtime == 0.0)
			{
				downtime = 1.0;
				cursol++;
			}
		}
		else if (input.MoveVectorLogic().y < -0.5)
		{
			if (downtime == 0.0)
			{
				downtime = 1.0;
				cursol--;
			}
		}
		else downtime = 0.0;

		//カーソル位置の超過検知
		if (cursol < 0)cursol = 0;
		else if (cursol > stagelist.size() - 1)cursol = stagelist.size() - 1;

		//テキストマーカー
		Rect{ -60, -30, 400, 50 }.draw(Palette::Royalblue);
		Rect{ -20, 90, 400, 50 }.draw(Palette::Royalblue);
		Rect{ 40, 200, 400, 50 }.draw(Palette::Royalblue);
		Rect{ 100, 310, 400, 50 }.draw(Palette::Royalblue);
		Rect{ 40, 420, 400, 50 }.draw(Palette::Royalblue);
		Rect{ -20, 530, 400, 50 }.draw(Palette::Royalblue);

		if (cursol - 3 >= 0)font(stagelist[cursol - 3].readNum() + U" : " + stagelist[cursol - 3].readName()).draw(-60, -44);
		if (cursol - 2 >= 0)font(stagelist[cursol - 2].readNum() + U" : " + stagelist[cursol - 2].readName()).draw(-10, 76);
		if (cursol - 1 >= 0)font(stagelist[cursol - 1].readNum() + U" : " + stagelist[cursol - 1].readName()).draw(40, 186);
		font(stagelist[cursol].readNum() + U" : " + stagelist[cursol].readName()).draw(100, 296);
		if (cursol + 1 < stagelist.size())font(stagelist[cursol + 1].readNum() + U" : " + stagelist[cursol + 1].readName()).draw(40, 406);
		if (cursol + 2 < stagelist.size())font(stagelist[cursol + 2].readNum() + U" : " + stagelist[cursol + 2].readName()).draw(-10, 516);

		downtime -= deltatime;

	}

	void draw() const override
	{


	}

};
