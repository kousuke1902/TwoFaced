# include <Siv3D.hpp>
#include "spawndata.hpp"

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
		if (SimpleGUI::Button(U"ロード", Vec2{ 1010, 10 }))
		{
			Optional<FilePath> check = Dialog::OpenFile({ FileFilter::CSV() });
			//パスの確認
			if (check)
			{
				path = check;
				csv = CSV{ *path };

				if (csv)
				{
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
		if (SimpleGUI::Button(U"セーブ", Vec2{ 1120, 10 }))
		{
			Optional<FilePath> check = Dialog::OpenFile({ FileFilter::CSV() });
			//パスの確認
			if (check)
			{
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
		if (SimpleGUI::Button(U"上書き", Vec2{ 1230, 10 }))
		{
			if (path)
			{
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

		}

		//ファイルネーム
		if (path)font(FileSystem::FileName(*path)).draw(1010, 60);

		//表示情報
		font(U"ステージルール:", cleartype).draw(1010, 90);
		font(U"設定時間:", stagetime).draw(1010, 110);

		//画面上での軌跡の表示
		if (spawndatas)
		{
			//スポーン座標の表示
			Vec2 SpawnPos = spawndatas[enemynum].readSpawnPos() + Vec2{ 100.0, 100.0 };
			Circle{ SpawnPos, 5.0}.draw(Palette::Red);

			//一つ前の座標の記録
			Vec2 backPos = SpawnPos;

			//軌跡の描画
			size_t count_max = spawndatas[enemynum].commands.size();
			for (size_t count = 0; count < count_max; ++count)
			{
				String command = spawndatas[enemynum].commands[count].readType();
				Vec2 Pos = spawndatas[enemynum].commands[count].readParamater();

				//直進
				if (command == U"straight")
				{
					Vec2 forwardPos = Pos + Vec2{ 100.0, 100.0 };
					Line{ backPos, forwardPos }.draw(Palette::Darkorange);
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


				//行動一覧表示
				if (SimpleGUI::Button(command, Vec2{ 1010, 200 + 100 * count }, 100))
				{
					if (command == U"straight") spawndatas[enemynum].commands[count].setType(U"wait");
					else if (command == U"wait") spawndatas[enemynum].commands[count].setType(U"kill");
					else if (command == U"kill") spawndatas[enemynum].commands[count].setType(U"straight");

				}

			}

			//他軌跡の閲覧の為の選択処理
			if (0 < enemynum && KeyLeft.down()) --enemynum;
			else if (enemynum < spawndatas.size() - 1 && KeyRight.down()) ++enemynum;



		}

		

	}


}

