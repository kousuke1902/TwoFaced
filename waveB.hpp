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

	WaveB(Vec2 pos, double w, double h, Vec2 vector, double speed, double lifespan, double damage, Texture img) : Bullet(pos, w, h, vector, speed, lifespan, damage, img)
	{

	}

};
