#pragma once
#include <SDL.h>
#include "Utils.h"

class Paddle
{
public:
	Paddle(int id);

	const SDL_Rect* getRect() const;
	const float getX() const { return m_x; }
	const float getY() const { return m_y; }
	const int getWidth() const { return m_width; }
	const int getHeight() const { return m_height; }
	void changeVel(int speed);
	void move();

private:
	int m_id;
	float m_x, m_y;
	int m_VelY{};
	int m_width{ 10 };
	int m_height{ 70 };
	SDL_Rect m_rect;
};