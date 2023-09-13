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



};
