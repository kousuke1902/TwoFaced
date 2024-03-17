#include <Siv3D.hpp>
#include "spawndata.hpp"

#define TASK_SPACE 130
#define TASK_FIRST_COLUMNS 410
#define TASK_SECOND_COLUMNS 450
#define TASK_THIRD_COLUMNS 490

void Main()
{
	Window::Resize(1400, 1000);
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });

	CSV csv;//ステージファイルの読み込み
	Optional<FilePath> path;//ファイルパス
	Array<Spawndata> spawndatas;//ステージ内敵情報
	String stagename = U"None";//ステージ名
	String cleartype = U"None";//クリア種類
	double stagetime = 0.0;//ステージ時間
	size_t enemynum = 0;//エネミーの切り替え用の数
	size_t target_cursor = 0;//変更を加えるポイントの番号
	Font font{ 20 };

	spawndatas.clear();


	while (System::Update())
	{
		ClearPrint();

		//コンソール
		Rect(1000, 0, 400, 1000).draw(Palette::Black);

		//実際の画面
		Rect(100, 100, 800, 800).drawFrame(1.0, Palette::Orangered);

		//CSV内データの読み込み
		if (SimpleGUI::Button(U"ロード", Vec2{ 1010, 10 }, 100))
		{
			Optional<FilePath> check = Dialog::OpenFile({ FileFilter::CSV() });
			//パスの確認
			if (check)
			{
				path = check;
				csv = CSV{ *path };

				if (csv)
				{
					//初期化
					spawndatas.clear();
					//ステージ情報
					cleartype = csv[0][0];
					stagetime = Parse<double>(csv[0][1]);
				
					//行ごとに読み込み
					for (size_t row = 1; row < csv.rows(); ++row)
					{
						//スポーン時間読み込み
						double spawntime = Parse<double>(csv[row][0]);

						//エネミーキャラクター読み込み
						String name = csv[row][1];

						//初期スポーン座標
						Vec2 startPos = Parse<Vec2>(csv[row][2]);

						//移動命令
						Array<MoveCommand> bufcommand;
						bufcommand.clear();

						//命令読み込み
						for (size_t column = 3; column < csv.columns(row); ++column)
						{
							//直進
							if (csv[row][column] == U"straight")
							{
								bufcommand << MoveCommand(U"straight",  Parse<Vec2>(csv[row][column + 1]));
								++column;
							}
							//待機
							else if (csv[row][column] == U"wait")
							{
								bufcommand << MoveCommand(U"wait", Vec2(Parse<double>(csv[row][column + 1]), 0.0));
								++column;
							}
							//削除
							else if (csv[row][column] == U"kill")
							{
								bufcommand << MoveCommand(U"kill", Vec2(0.0, 0.0));

							}
						}

						spawndatas << Spawndata(spawntime, name, startPos, bufcommand);
					}
				}
				//初期化
				enemynum = 0;
			}
		}

		//CSVへ書き込み
		if (SimpleGUI::Button(U"セーブ", Vec2{ 1120, 10 }, 100))
		{
			Optional<FilePath> check = Dialog::SaveFile({ FileFilter::CSV() });
			//パスの確認
			if (check)
			{
				spawndatas.sort_by([](const Spawndata& a, const Spawndata& b) {return (a.spawntime < b.spawntime); });
				//保存処理
				CSV savecsv;
				path = check;

				//ステージ情報
				savecsv.writeRow(cleartype, stagetime);

				size_t max_rows = spawndatas.size();

				for (size_t rows = 0; rows < max_rows; ++rows)
				{
					//スポーン情報
					//スポーン時間
					savecsv.write(spawndatas[rows].readSpawntime());
					//エネミー名
					savecsv.write(spawndatas[rows].readName());
					//スポーン座標
					savecsv.write(spawndatas[rows].readSpawnPos());

					//移動命令
					size_t max_columns = spawndatas[rows].commands.size();
					for (size_t columns = 0; columns < max_columns; ++columns)
					{			
						//命令情報
						String type = spawndatas[rows].commands[columns].readType();

						//直進
						if (spawndatas[rows].commands[columns].readType() == U"straight")
						{
							savecsv.write(type);
							savecsv.write(spawndatas[rows].commands[columns].readParamater());
						}
						//待機
						else if (spawndatas[rows].commands[columns].readType() == U"wait")
						{
							savecsv.write(type);
							savecsv.write(spawndatas[rows].commands[columns].readParamater().x);
						}
						//削除
						else if (spawndatas[rows].commands[columns].readType() == U"kill")
						{
							savecsv.write(type);
						}
						
					}

					savecsv.newLine();	
				}

			savecsv.save(*path);
			}

		}

		//CSVへ上書き
		if (SimpleGUI::Button(U"上書き", Vec2{ 1230, 10 }, 100, path.has_value()))
		{
				spawndatas.sort_by([](const Spawndata& a, const Spawndata& b) {return (a.spawntime < b.spawntime); });
				//保存処理
				CSV savecsv;

				//ステージ情報
				savecsv.writeRow(cleartype, stagetime);
				size_t max_rows = spawndatas.size();

				for (size_t rows = 0; rows < max_rows; ++rows)
				{
					//スポーン情報
					//スポーン時間
					savecsv.write(spawndatas[rows].readSpawntime());
					//エネミー名
					savecsv.write(spawndatas[rows].readName());
					//スポーン座標
					savecsv.write(spawndatas[rows].readSpawnPos());

					//移動命令
					size_t max_columns = spawndatas[rows].commands.size();

					for (size_t columns = 0; columns < max_columns; ++columns)
					{
						//命令情報
						String type = spawndatas[rows].commands[columns].readType();
						//直進

						if (spawndatas[rows].commands[columns].readType() == U"straight")
						{
							savecsv.write(type);
							savecsv.write(spawndatas[rows].commands[columns].readParamater());
						}
						//待機
						else if (spawndatas[rows].commands[columns].readType() == U"wait")
						{
							savecsv.write(type);
							savecsv.write(spawndatas[rows].commands[columns].readParamater().x);
						}
						//削除
						else if (spawndatas[rows].commands[columns].readType() == U"kill")
						{
							savecsv.write(type);
						}
					}

					savecsv.newLine();
				}

			savecsv.save(*path);

		}

		//ファイルネーム
		if (path)font(FileSystem::FileName(*path)).draw(1010, 50);

		//ステージルール操作
		font(U"ステージルール:", cleartype).draw(1010, 80);

		//表示時間操作
		font(U"設定時間").draw(1010, 105);
		font(stagetime).draw(1175, 140);
		if (SimpleGUI::Button(U"- 60", Vec2{ 1010, 135 }, 50)) stagetime -= 60;
		if (SimpleGUI::Button(U"-10", Vec2{ 1065, 135 }, 50)) stagetime -= 10;
		if (SimpleGUI::Button(U"-1", Vec2{ 1120, 135 }, 50)) stagetime -= 1;
		if (SimpleGUI::Button(U"1", Vec2{ 1240, 135 }, 50)) stagetime += 1;
		if (SimpleGUI::Button(U"10", Vec2{ 1295, 135 }, 50)) stagetime += 10;
		if (SimpleGUI::Button(U"60", Vec2{ 1350, 135 }, 50)) stagetime += 60;

		//先頭への行動追加
		if (SimpleGUI::Button(U"+", Vec2{ 1010, 175 }, 20, !spawndatas.empty()))	spawndatas[enemynum].commands.push_front(MoveCommand());

		//エネミーの追加
		if (SimpleGUI::Button(U"Enemy+", Vec2{ 1040, 175 }, 80))
		{
			spawndatas << Spawndata(0, U"glockdrone", Vec2{ 400.0, -100.0 });
			enemynum = spawndatas.size() - 1;
		}
		//エネミーの削除
		if (SimpleGUI::Button(U"Enemy-", Vec2{ 1130, 175 }, 80, !spawndatas.empty()))
		{
			auto it = spawndatas.begin() + enemynum;
			spawndatas.erase(it);
			if (enemynum > spawndatas.size()) enemynum = spawndatas.size() - 1;
			
		}
		//エネミーのクリア
		if (SimpleGUI::Button(U"Clear", Vec2{ 1220, 175 }, 80))
		{
			spawndatas.clear();
			enemynum = 0;
		}

		//エネミー番号表示
		font(enemynum).draw(1310, 175);

		//画面上での軌跡の表示
		if (spawndatas)
		{
			//スポーン座標の表示
			Vec2 SpawnPos = spawndatas[enemynum].readSpawnPos() + Vec2{ 100.0, 100.0 };
			Circle{ SpawnPos, 5.0}.draw(Palette::Red);

			//スポーン座標の操作
			font(U"スポーン座標").draw(1010, 215);
			font(spawndatas[enemynum].readSpawnPos().x).draw(1180, 245);
			font(spawndatas[enemynum].readSpawnPos().y).draw(1180, 285);

			//x座標
			if (SimpleGUI::Button(U"-100", Vec2{ 1010, 245 }, 50)) spawndatas[enemynum].addSpaownPosX(-100.0);
			if (SimpleGUI::Button(U"-10", Vec2{ 1065, 245 }, 50)) spawndatas[enemynum].addSpaownPosX(-10.0);
			if (SimpleGUI::Button(U"-1", Vec2{ 1120, 245 }, 50)) spawndatas[enemynum].addSpaownPosX(-1.0);
			if (SimpleGUI::Button(U"1", Vec2{ 1230, 245 }, 50)) spawndatas[enemynum].addSpaownPosX(1.0);
			if (SimpleGUI::Button(U"10", Vec2{ 1285, 245 }, 50)) spawndatas[enemynum].addSpaownPosX(10.0);
			if (SimpleGUI::Button(U"100", Vec2{ 1340, 245 }, 50)) spawndatas[enemynum].addSpaownPosX(100.0);

			//y座標
			if (SimpleGUI::Button(U"-100", Vec2{ 1010, 285 }, 50)) spawndatas[enemynum].addSpaownPosY(-100.0);
			if (SimpleGUI::Button(U"-10", Vec2{ 1065, 285 }, 50)) spawndatas[enemynum].addSpaownPosY(-10.0);
			if (SimpleGUI::Button(U"-1", Vec2{ 1120, 285 }, 50)) spawndatas[enemynum].addSpaownPosY(-1.0);
			if (SimpleGUI::Button(U"1", Vec2{ 1230, 285 }, 50)) spawndatas[enemynum].addSpaownPosY(1.0);
			if (SimpleGUI::Button(U"10", Vec2{ 1285, 285 }, 50)) spawndatas[enemynum].addSpaownPosY(10.0);
			if (SimpleGUI::Button(U"100", Vec2{ 1340, 285 }, 50)) spawndatas[enemynum].addSpaownPosY(100.0);

			//スポーン時間の操作
			font(U"スポーン時間").draw(1010, 320);
			font(spawndatas[enemynum].spawntime).draw(1180, 355);

			if (SimpleGUI::Button(U"- 60", Vec2{ 1010, 350 }, 50)) spawndatas[enemynum].spawntime -= 60;
			if (SimpleGUI::Button(U"-10", Vec2{ 1065, 350 }, 50)) spawndatas[enemynum].spawntime -= 10;
			if (SimpleGUI::Button(U"-1", Vec2{ 1120, 350 }, 50)) spawndatas[enemynum].spawntime -= 1;
			if (SimpleGUI::Button(U"1", Vec2{ 1240, 350 }, 50)) spawndatas[enemynum].spawntime += 1;
			if (SimpleGUI::Button(U"10", Vec2{ 1295, 350 }, 50)) spawndatas[enemynum].spawntime += 10;
			if (SimpleGUI::Button(U"60", Vec2{ 1350, 350 }, 50)) spawndatas[enemynum].spawntime += 60;

			//一つ前の座標の記録
			Vec2 backPos = SpawnPos;

			//各要素の処理
			size_t max_size = spawndatas[enemynum].commands.size();

			//各項の処理
			for (size_t count = 0; count < max_size; ++count)
			{
				String command = spawndatas[enemynum].commands[count].readType();
				Vec2 Pos = spawndatas[enemynum].commands[count].readParamater();

				//経路描画処理
				//直進
				if (command == U"straight")
				{
					Vec2 forwardPos = Pos + Vec2{ 100.0, 100.0 };
					Line{ backPos, forwardPos }.draw(Palette::Darkorange);
					Circle{ forwardPos, 2.0 }.draw(Palette::Darkorange);
					backPos = forwardPos;
				}

				//待機
				else if (command == U"wait")
				{
					Circle{ backPos, 5.0 }.draw(Palette::Slateblue);
				}

				//削除
				else if (command == U"kill")
				{
					RectF{ Arg::center(backPos), 5.0 }.draw(Palette::Yellow);
				}

			}

			//操作端末処理
			//表示最大数以下のチェック
			size_t count_max = max_size - target_cursor * 4;
			if (count_max > 3) count_max = 4;

			//追加削除の為のポインタ
			auto begin_it = spawndatas[enemynum].commands.begin();
			auto it = begin_it + target_cursor * 4;

			//各項の処理
			for (size_t count = 0; count < count_max; ++count)
			{

				//命令番号
				font(count + target_cursor * 4).draw(Vec2{ 1010, TASK_FIRST_COLUMNS + TASK_SPACE * count });

				//行動一覧表示
				String command = spawndatas[enemynum].commands[count + target_cursor * 4].readType();
				if (SimpleGUI::Button(command, Vec2{ 1100, TASK_FIRST_COLUMNS + TASK_SPACE * count }, 100))
				{
					if (command == U"straight") spawndatas[enemynum].commands[count + target_cursor * 4].setType(U"wait");
					else if (command == U"wait") spawndatas[enemynum].commands[count + target_cursor * 4].setType(U"kill");
					else if (command == U"kill") spawndatas[enemynum].commands[count + target_cursor * 4].setType(U"straight");

				}

				//前後入れ替え
				//下へ移動
				if (SimpleGUI::Button(U"▼", Vec2{ 1060, TASK_FIRST_COLUMNS + TASK_SPACE * count }, 30, count + target_cursor * 4 != max_size - 1))
				{
					MoveCommand buf_command = spawndatas[enemynum].commands[count + target_cursor * 4];
					spawndatas[enemynum].commands[count + target_cursor * 4] = spawndatas[enemynum].commands[count + target_cursor * 4 + 1];
					spawndatas[enemynum].commands[count + target_cursor * 4 + 1] = buf_command;
				}

				//上へ移動
				if (SimpleGUI::Button(U"▲", Vec2{ 1210, TASK_FIRST_COLUMNS + TASK_SPACE * count }, 30, it != begin_it))
				{
					MoveCommand buf_command = spawndatas[enemynum].commands[count + target_cursor * 4];
					spawndatas[enemynum].commands[count + target_cursor * 4] = spawndatas[enemynum].commands[count + target_cursor * 4 - 1];
					spawndatas[enemynum].commands[count + target_cursor * 4 - 1] = buf_command;
				}

				//追加
				if (SimpleGUI::Button(U"+", Vec2{ 1250, TASK_FIRST_COLUMNS + TASK_SPACE * count }, 20))
				{
					spawndatas[enemynum].commands.insert(++it, MoveCommand());
					break;
				}

				//削除
				if (SimpleGUI::Button(U"-", Vec2{ 1275, TASK_FIRST_COLUMNS + TASK_SPACE * count }, 20))
				{
					spawndatas[enemynum].commands.erase(it);
					break;
				}

				else ++it;

				//座標表示
				font(spawndatas[enemynum].commands[count + target_cursor * 4].readParamater().x).draw(1180, TASK_SECOND_COLUMNS + TASK_SPACE * count);
				font(spawndatas[enemynum].commands[count + target_cursor * 4].readParamater().y).draw(1180, TASK_THIRD_COLUMNS + TASK_SPACE * count);

				//座標操作
				//x座標
				if (SimpleGUI::Button(U"-100", Vec2{ 1010, TASK_SECOND_COLUMNS + TASK_SPACE * count }, 50)) spawndatas[enemynum].commands[count + target_cursor * 4].addParamaterX(-100.0);
				if (SimpleGUI::Button(U"-10", Vec2{ 1065, TASK_SECOND_COLUMNS + TASK_SPACE * count }, 50)) spawndatas[enemynum].commands[count + target_cursor * 4].addParamaterX(-10.0);
				if (SimpleGUI::Button(U"-1", Vec2{ 1120, TASK_SECOND_COLUMNS + TASK_SPACE * count }, 50)) spawndatas[enemynum].commands[count + target_cursor * 4].addParamaterX(-1.0);
				if (SimpleGUI::Button(U"1", Vec2{ 1230, TASK_SECOND_COLUMNS + TASK_SPACE * count }, 50)) spawndatas[enemynum].commands[count + target_cursor * 4].addParamaterX(1.0);
				if (SimpleGUI::Button(U"10", Vec2{ 1285, TASK_SECOND_COLUMNS + TASK_SPACE * count }, 50)) spawndatas[enemynum].commands[count + target_cursor * 4].addParamaterX(10.0);
				if (SimpleGUI::Button(U"100", Vec2{ 1340, TASK_SECOND_COLUMNS + TASK_SPACE * count }, 50)) spawndatas[enemynum].commands[count + target_cursor * 4].addParamaterX(100.0);

				//y座標
				if (SimpleGUI::Button(U"-100", Vec2{ 1010, TASK_THIRD_COLUMNS + TASK_SPACE * count }, 50)) spawndatas[enemynum].commands[count + target_cursor * 4].addParamaterY(-100.0);
				if (SimpleGUI::Button(U"-10", Vec2{ 1065, TASK_THIRD_COLUMNS + TASK_SPACE * count }, 50)) spawndatas[enemynum].commands[count + target_cursor * 4].addParamaterY(-10.0);
				if (SimpleGUI::Button(U"-1", Vec2{ 1120, TASK_THIRD_COLUMNS + TASK_SPACE * count }, 50)) spawndatas[enemynum].commands[count + target_cursor * 4].addParamaterY(-1.0);
				if (SimpleGUI::Button(U"1", Vec2{ 1230, TASK_THIRD_COLUMNS + TASK_SPACE * count }, 50)) spawndatas[enemynum].commands[count + target_cursor * 4].addParamaterY(1.0);
				if (SimpleGUI::Button(U"10", Vec2{ 1285, TASK_THIRD_COLUMNS + TASK_SPACE * count }, 50)) spawndatas[enemynum].commands[count + target_cursor * 4].addParamaterY(10.0);
				if (SimpleGUI::Button(U"100", Vec2{ 1340, TASK_THIRD_COLUMNS + TASK_SPACE * count }, 50)) spawndatas[enemynum].commands[count + target_cursor * 4].addParamaterY(100.0);

			}
			

			//他経路の閲覧の為の選択処理
			if (0 < enemynum && (KeyLeft.down() || KeyA.down()) )
			{
				--enemynum;
				target_cursor = 0;
			}
			else if (enemynum < spawndatas.size() - 1 && (KeyRight.down() || KeyD.down()) )
			{
				++enemynum;
				target_cursor = 0;
			} 

			//行動のページ送り
			if (0 < target_cursor && (KeyUp.down() || KeyW.down()) )--target_cursor;
			else if (target_cursor < max_size / 4 && (KeyDown.down() || KeyS.down()) ) ++target_cursor;

		}

		

	}


}

