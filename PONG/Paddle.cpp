#include "Paddle.h"

Paddle::Paddle(int id)
	: m_id{id}
{
	if (id == 1)
	{
		m_x = 10;
		m_y = SCREEN_HEIGHT / 2 - m_height / 2;
		m_rect = { static_cast<int>(m_x), static_cast<int>(m_y), m_width, m_height };
	}
	if (id == 2)
	{
		m_x = SCREEN_WIDTH - m_width - 10;
		m_y = SCREEN_HEIGHT / 2 - m_height / 2;
		m_rect = { static_cast<int>(m_x), static_cast<int>(m_y), m_width, m_height };
	}
}

const SDL_Rect* Paddle::getRect() const
{
	const SDL_Rect* point = &m_rect;
	return point;
}

void Paddle::changeVel(int speed)
{
	m_VelY += speed;
}

void Paddle::move()
{
	m_y += m_VelY;
	m_rect.y += m_VelY;

	if (m_y == 0 || m_y == SCREEN_HEIGHT - m_height)
	{
		m_y -= m_VelY;
		m_rect.y -= m_VelY;
	}
}
