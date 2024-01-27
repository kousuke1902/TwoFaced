#pragma once
//シーンで使用するデータセット

enum class State
{

	Title,
	StageSelect,
	Stage,
	Result
};

struct GameData
{
	Optional<int> PlayerIndex;//選択キャラ	
	Optional<FilePath> Stagepath;//選択されたステージファイルパス
	double ResultLife = 0.0;//リザルトで使用するライフ

};

using App = SceneManager<State, GameData>;
