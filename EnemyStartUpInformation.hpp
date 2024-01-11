#pragma once
#include <Siv3D.hpp>
#include "EnemyManager.hpp"
#include "movecommand.hpp"

struct EnemyStartUpInformation
{
	
	Array<double*> spawntimes;//エネミーのスポーン時間
	Array<Vec2*> spawnPos;//エネミーの初期スポーン座標
	Array<EnemyName> name;//スポーンするエネミーの名称
	Array<Array<MoveCommand*>> movecomands;//行動命令の列挙

};
