#pragma once
#include <Siv3D.hpp>
#include "glockdrone.hpp"
#include "PlayerManager.hpp"
#include "BulletManager.hpp"

class EnemyManager
{

private:

	Array<Enemy*> enemies;

public:

	EnemyManager()
	{

		enemies.clear();
	}

	int EnemySpawn(Vec2 pos, int enemynum)
	{
		if (enemynum == 0)
		{

			Enemy* enemy = new GlockDrone(pos);
			return 0;

		}

	}

};
