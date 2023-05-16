#include "Ball.h"

Ball::Ball() 
{
	m_x = SCREEN_WIDTH / 2 - m_width / 2;
	m_y = SCREEN_HEIGHT / 2 - m_height / 2;
	m_rect = { static_cast<int>(m_x), static_cast<int>(m_y), m_width, m_height };

	auto randomNumber = createUniformPseudoRandomNumberGenerator()
}

const SDL_Rect* Ball::getRect() const
{
	const SDL_Rect* pointer = &m_rect;
	return pointer;
}

void Ball::move(Clock* clock, Paddle* left, Paddle* right)
{
	m_x += m_VelX * clock->getDelta();
	m_rect.x += m_VelX * clock->getDelta();
	m_y += m_VelY * clock->getDelta();
	m_rect.y += m_VelY * clock->getDelta();

	if (m_y <= 0 || m_y >= SCREEN_HEIGHT - m_height)
		m_VelY *= -1;

	if (contactLeftPaddle(left) || contactRightPaddle(right))
		m_VelX *= -1;

	if (m_x + m_width < 0 || m_x > SCREEN_WIDTH)
	{
		m_x = SCREEN_WIDTH / 2 - m_width / 2;
		m_y = SCREEN_HEIGHT / 2 - m_height / 2;
		m_rect.x = m_x;
		m_rect.y = m_y;
	}
}

bool Ball::contactLeftPaddle(Paddle* left) const
{
	if (m_x > left->getX() + left->getWidth())
		return false;

	if (m_y < left->getY())
		return false;

	if (m_y > left->getY() + left->getHeight())
		return false;

	if (m_x < left->getX() + 5)
		return false;

	return true;
}

bool Ball::contactRightPaddle(Paddle* right) const
{
	if (m_x + m_width < right->getX())
		return false;

	if (m_y < right->getY())
		return false;

	if (m_y > right->getY() + right->getHeight())
		return false;

	if (m_x + m_width > right->getX() + 5)
		return false;

	return true;
}

