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

	//選択キャラ
	Optional<int> PlayerIndex;

	//選択されたステージ
	Optional<int> Stage;



};

using App = SceneManager<State, GameData>;
