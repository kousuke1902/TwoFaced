#pragma once
#include <Siv3D.hpp>
#include "bullet.hpp"

class DefenceB : public Bullet
{

public:

	DefenceB(Vec2 pos, double w, double h, Vec2 vector, double speed, double lifespan, double damage, Texture img) : Bullet(pos, w, h, vector, speed, lifespan, damage, img)
	{


	}

	//時間的寿命の削り取り
	int reduceLifeSpan()
	{
		return 0;
	}

};
