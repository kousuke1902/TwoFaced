#pragma once
#include <Siv3D.hpp>
#include "SceneData.hpp"
#include "input.hpp"
#include "PlayerManager.hpp"
#include "EnemyManager.hpp"
#include "BulletManager.hpp"
#include "GoalRule.hpp"


//ステージに関する処理
class Stage : public App::Scene
{

private:

	PlayerInput input;//プレイヤーインプット
	PlayerManager playermanager;//プレイヤー処理
	EnemyManager enemymanager;//エネミー処理
	BulletManager bulletmanager;//弾処理
	GameRule* gamerule;//ステージクリア，ゲームオーバー判定
	Array<EnemyStartUpInformation*> startup;//エネミーの初期設定情報
	FilePath stagefile;//ステージのファイル情報
	bool PauseFlag;//ポーズメニューの状態
	Font font;//表示
	int cursol;//メニューのカーソル位置
	double downtime;//カーソル入力時間
	double warningTime;//作戦領域離脱時間

	Texture Attackimg;//攻の文字画像
	Texture Defenceimg;//守の文字画像
	Texture Lifeimg;//体の文字画像
	Texture Inherenceimg;//力の文字画像
	Texture Cooltimeimg;//待の文字画像
	Texture CursorR;//カーソル右
	Texture CursorL;//カーソル左

	//ゲームルールを設定する
	int setGameRule(CSV csv)
	{
		//ゲームルールの確認
		if (csv[0][0] == U"Goal")
		{
			gamerule = new GoalRule(Parse<double>(csv[0][1]));

		}

		else gamerule = new GoalRule(10.0);

		return 0;
	}

	//エネミーを読み込む
	int loadspawnEnemies(CSV csv)
	{

		//行ごとに読み込み
		for (size_t row = 1; row < csv.rows(); ++row)
		{
			//スポーン時間読み込み
			double spawntime = Parse<double>(csv[row][0]);

			//エネミーキャラクター読み込み
			int enemyID;

			if (csv[row][1] == U"glockdrone")
			{

				enemyID = (int)EnemyName::glockdrone;
			}
			else enemyID = (int)EnemyName::glockdronenomove;

			//初期スポーン座標
			Vec2 startPos = Parse<Vec2>(csv[row][2]);

			//移動命令
			Array<MoveCommand*> bufcommand;
			bufcommand.clear();

			//命令読み込み
			for (size_t column = 3; column < csv.columns(row); ++column)
			{
				//直進
				if (csv[row][column] == U"straight")
				{
					bufcommand << new Straight(Parse<Vec2>(csv[row][column + 1]));
					++column;
				}
				//待機
				else if (csv[row][column] == U"wait")
				{
					bufcommand << new Wait(Parse<double>(csv[row][column + 1]));
					++column;
				}
				//削除
				else if (csv[row][column] == U"kill")
				{
					bufcommand << new Kill;

				}
			}

			startup << new EnemyStartUpInformation(spawntime, enemyID, startPos, bufcommand);

		}

		return 0;
	}

public:

	Stage(const InitData& init) : IScene{ init }
	{
		stagefile = getData().Stagepath;
		CSV csv{ stagefile };
		setGameRule(csv);
		loadspawnEnemies(csv);
		PauseFlag = false;
		font = Font{ 40 };
		cursol = 0;
		downtime = 0.0;
		warningTime = 10.0;

		Attackimg = Texture{ Image{ U"img/ko.png"}.scaled(0.6) };
		Defenceimg = Texture{ Image{ U"img/shu.png"}.scaled(0.6) };
		Lifeimg = Texture{ Image{ U"img/tai.png"}.scaled(0.15) };
		Inherenceimg = Texture{ Image{ U"img/ryoku.png"}.scaled(0.15) };
		Cooltimeimg = Texture{ Image{ U"img/machi.png"}.scaled(0.15) };
		CursorR = Texture{ Image{ U"img/cursorR.png"}.scaled(0.15) };
		CursorL = Texture{ Image{ U"img/cursorR.png"}.scaled(0.15).mirrored() };
	}

	//更新処理
	void update()override
	{

		ClearPrint();

		//処理フレーム間の経過時間
		const double deltatime = Scene::DeltaTime();

		//ポーズがOFFの状態であることの確認
		if (!PauseFlag)
		{
			//ポーズボタン確認
			if (input.downStartbottan())PauseFlag = true;
			
			//クリア，ゲームオーバー判定
			if (gamerule->Clear() || gamerule->GameOver() || playermanager.deadFlag())
			{
				getData().ResultLife = playermanager.PlayerLife();
				changeScene(State::Result);
			}

			//入力状態の更新
			input.Update();

			//プレイヤー処理
			playermanager.Update(&bulletmanager, &input, deltatime);
			

			//エネミー処理
			//エネミーの更新
			enemymanager.Update(&bulletmanager, &playermanager, deltatime);
			//エネミーのスポーン
			if (!startup.empty())
			{
				//スポーン時間を超過
				if (gamerule->readTimer() > startup.front()->readSpawnTime())
				{
					enemymanager.EnemySpawn(startup.front());
					startup.pop_front();
				}
			}


			//弾処理
			bulletmanager.Update(deltatime);

			//ステージの範囲外へ出たか確認
			if (!Rect(0, 0, 800, 800).intersects(playermanager.PlayerHitBox()))
			{
				warningTime -= deltatime;

				Rect(0, 0, 800, 800).draw(Color(200, 0, 0, 100));
				font(U"中に戻って").drawAt(400, 300);
				font(U"{:.1f}"_fmt(warningTime)).drawAt(400, 350);
			}



			//時間経過
			gamerule->addTimer(deltatime);

			
		}

		//ポーズメニュー表示
		else
		{
			//入力時間
			downtime -= deltatime;
			downtime = Max(0.0, downtime);

			//ポーズボタン確認
			if (input.downStartbottan())
			{
				PauseFlag = false;
				cursol = 0;
			}
			//決定ボタン
			else if (input.pressFire())
			{
				if (cursol == 0)PauseFlag = false;
				else if (cursol == 1)changeScene(State::Stage);
				else if (cursol == 2)changeScene(State::StageSelect);
			}

			//キャンセルボタン
			else if (input.downModechange())
			{
				PauseFlag = false;
				cursol = 0;
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
			if (cursol < 0)cursol = 2;
			else if (cursol > 2)cursol = 0;

			//表示
			RoundRect{ Arg::center(400.0, 365.0), 600.0, 440.0, 5.0 }.draw(Palette::Gainsboro).drawFrame(5.0, Palette::Dimgray);
			font(U"Pause").drawAt(400, 200, Palette::Black);
			font(U"続ける").drawAt(400, 330, Palette::Black);
			font(U"最初から").drawAt(400, 430, Palette::Black);
			font(U"ステージ選択に戻る").drawAt(400, 530, Palette::Black);

			CursorL.drawAt(180, cursol * 100 + 330);
			CursorR.drawAt(620, cursol * 100 + 330);

		}

		//パラメータ表示
		double PlayerLife = playermanager.PlayerLife();
		double PlayerInherence = playermanager.PlayerInherence();
		double PlayerModeCoolTime = 1.0 - playermanager.PlayerModeCoolTimer() / playermanager.PlayerModeCoolTime();
		Rect(800, 0, 200, 800).draw(Palette::Black);

		//モード
		if (playermanager.PlayerMode())
		{
			//font(U"レフトサイド").draw(810, 300);
			RoundRect{ Arg::center(900, 150), 180, 180, 5 }.draw(Palette::Skyblue).drawFrame(5, Palette::Blue);
			Defenceimg.drawAt(900, 155);
		}
		else
		{
			//font(U"ライトサイド").draw(810, 300);
			RoundRect{ Arg::center(900, 150), 180, 180, 5 }.draw(Palette::Coral).drawFrame(5, Palette::Red);
			Attackimg.drawAt(900, 150);
		}

		//体力バー
		RoundRect{ Arg::center(835.0, 330.0), 55.0, 55.0, 5.0 }.draw(Palette::Lightgreen).drawFrame(3, Palette::Green);
		Lifeimg.drawAt(835.0, 330.0);
		RoundRect{ Arg::center(835.0, 570.0), 55.0, 410.0, 5.0 }.draw(Palette::Darkgreen);
		RoundRect(815.0, 770.0 - 4.0 * PlayerLife, 40.0, 4.0 * PlayerLife, 5.0).draw(Palette::Lime);
		//エネルギーバー
		RoundRect{ Arg::center(900.0, 330.0), 55.0, 55.0, 5.0 }.draw(Palette::Tomato).drawFrame(3, Palette::Crimson);
		Inherenceimg.drawAt(900.0, 330);
		RoundRect{ Arg::center(900.0, 570.0), 55.0, 410.0, 5.0 }.draw(Palette::Crimson);
		RoundRect(880.0, 770.0 - 4.0 * PlayerInherence, 40.0, 4.0 * PlayerInherence, 5.0).draw(Palette::Tomato);
		//モード切替インターバル
		RoundRect{ Arg::center(965.0, 330.0), 55.0, 55.0, 5.0 }.draw(Palette::Orchid).drawFrame(3, Palette::Darkslateblue);
		Cooltimeimg.drawAt(965.0, 330.0);
		RoundRect{ Arg::center(965.0, 570.0), 55.0, 410.0, 5.0 }.draw(Palette::Darkslateblue);
		RoundRect(945.0, 770.0 - 400.0 * PlayerModeCoolTime, 40.0, 400.0 * PlayerModeCoolTime, 5.0).draw(Palette::Orchid);

	}


};
