#pragma once
#include <Siv3D.hpp>
#include "bullet.hpp"

//防御弾クラス
class DefenceB : public Bullet
{

public:

	DefenceB(Vec2 pos, double w, double h, double lifespan, double damage, int imgtype) : Bullet(pos, w, h, Vec2(0, 0), 0, lifespan, damage, imgtype)
	{

	}

};
