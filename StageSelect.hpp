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
	Texture CursorR;//カーソル右
	Texture CursorL;//カーソル左

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

		CursorR = Texture{ Image{ U"img/cursorR.png"}.scaled(0.15) };
		CursorL = Texture{ Image{ U"img/cursorR.png"}.scaled(0.15).mirrored() };

	}

	void update() override
	{
		
		//処理フレーム間の経過時間
		const double deltatime = Scene::DeltaTime();

		downtime -= deltatime;
		downtime = Max(0.0, downtime);


		//ステージ選択決定
		if (input.pressFire())
		{
			getData().Stagepath = stagelist[cursol].readStagepath();
			changeScene(State::Stage);
		}

		//移動方向を検知してカーソル移動の検知を行う
		else if (input.MoveVectorLogic().y > 0.5)
		{
			if (downtime == 0.0)
			{
				downtime = 0.5;
				cursol++;
			}
		}
		else if (input.MoveVectorLogic().y < -0.5)
		{
			if (downtime == 0.0)
			{
				downtime = 0.5;
				cursol--;
			}
		}
		else downtime = 0.0;

		//カーソル位置の超過検知
		if (cursol < 0)cursol = stagelist.size() - 1;
		else if (cursol > stagelist.size() - 1)cursol = 0;

		for (int width = 0; width < 25; ++width)
		{
			Triangle{ 20.0 + 40 * width, 0.0, 80.0, 180_deg }.draw(Palette::Lavender);
			Triangle{ 20.0 + 40 * width, 800.0, 80.0 }.draw(Palette::Lavender);
		}
		

		//ステージセレクト
		RoundRect{ Arg::center(800.0, 50.0), 300.0, 50.0, 5.0 }.draw(Palette::Springgreen).drawFrame(5.0, Palette::Teal);
		font(U"ステージセレクト").drawAt(800.0, 50.0, Palette::Black);

		//テキストマーカー
		RoundRect{ Arg::center(250.0, 100.0), 550.0, 50.0, 5.0 }.draw(Palette::Royalblue).drawFrame(5.0, Palette::Mediumblue);
		RoundRect{ Arg::center(300.0, 200.0), 550.0, 50.0, 5.0 }.draw(Palette::Royalblue).drawFrame(5.0, Palette::Mediumblue);
		RoundRect{ Arg::center(350.0, 300.0), 550.0, 50.0, 5.0 }.draw(Palette::Royalblue).drawFrame(5.0, Palette::Mediumblue);
		RoundRect{ Arg::center(500.0, 400.0), 550.0, 50.0, 5.0 }.draw(Palette::Royalblue).drawFrame(5.0, Palette::Mediumblue);
		RoundRect{ Arg::center(350.0, 500.0), 550.0, 50.0, 5.0 }.draw(Palette::Royalblue).drawFrame(5.0, Palette::Mediumblue);
		RoundRect{ Arg::center(300.0, 600.0), 550.0, 50.0, 5.0 }.draw(Palette::Royalblue).drawFrame(5.0, Palette::Mediumblue);

		//ステージ名表示
		if (cursol - 3 >= 0)font(stagelist[cursol - 3].readNum() + U" : " + stagelist[cursol - 3].readName()).drawAt(250.0, 100.0, Palette::Black);
		if (cursol - 2 >= 0)font(stagelist[cursol - 2].readNum() + U" : " + stagelist[cursol - 2].readName()).drawAt(300.0, 200.0, Palette::Black);
		if (cursol - 1 >= 0)font(stagelist[cursol - 1].readNum() + U" : " + stagelist[cursol - 1].readName()).drawAt(350.0, 300.0, Palette::Black);
		font(stagelist[cursol].readNum() + U" : " + stagelist[cursol].readName()).drawAt(500.0, 400.0, Palette::Black);
		if (cursol + 1 < stagelist.size())font(stagelist[cursol + 1].readNum() + U" : " + stagelist[cursol + 1].readName()).drawAt(350.0, 500.0, Palette::Black);
		if (cursol + 2 < stagelist.size())font(stagelist[cursol + 2].readNum() + U" : " + stagelist[cursol + 2].readName()).drawAt(300.0, 600.0, Palette::Black);

		//カーソル
		CursorL.drawAt(190.0, 400.0);
		CursorR.drawAt(810.0, 400.0);

		//コメント
		//RoundRect{ Arg::center(650.0, 750.0), 550.0, 50.0, 5.0 }.draw(Palette::Azure).drawFrame(5.0, Palette::Lightsteelblue);
		Shape2D::RectBalloon(RectF{ Arg::center(650.0, 700.0), 550.0, 50.0 }, Vec2{ 850.0, 780.0 }, 0.2).draw(Palette::Azure).drawFrame(5.0, Palette::Lightsteelblue);
		font(stagelist[cursol].readComment()).drawAt(650.0, 700.0, Palette::Black);
	}

	void draw() const override
	{


	}

};
