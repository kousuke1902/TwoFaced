#pragma once
#include "bullet.hpp"

//
class WaveB : public Bullet
{

private:

	//ウェイブ
	Vec2 wave(double deltatime)
	{
		return Vec2(Speed * deltatime, Sin(LifeSpan));

	}

public:

	WaveB(Vec2 pos, Vec2 vector, double speed, double lifespan, double damage, int imgtype) : Bullet(pos, vector, speed, lifespan, damage, imgtype)
	{

	}

};
