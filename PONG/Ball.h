#pragma once
#include <SDL.h>
#include <iostream>
#include "Utils.h"
#include "Paddle.h"
#include "RandomNumber.h"
#include "Clock.h"

class Ball
{
public:
	Ball();

	const SDL_Rect* getRect() const;
	void move(Clock* clock, Paddle* left, Paddle* right);
	bool contactLeftPaddle(Paddle* left) const;
	bool contactRightPaddle(Paddle* right) const;

private:
	float m_x, m_y;
	int m_VelX, m_VelY;
	const int m_width{ 20 };
	const int m_height{ 20 };
	const int m_speed{ BALL_SPEED };
	SDL_Rect m_rect;
};