#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include "Paddle.h"
#include "Ball.h"
#include "Clock.h"

class Game
{
public:
	bool init(const char* title, int width, int height);
	void gameLoop();
	void shutdown();
	SDL_Texture* loadTexture(const char* path);

private:
	void handleEvent();
	void update();
	void draw();

	bool isRunning{ true };

	SDL_Window* m_window{ nullptr };
	SDL_Renderer* m_renderer{ nullptr };
	Paddle* m_leftPaddle{ nullptr };
	Paddle* m_rightPaddle{ nullptr };
	Ball* m_ball{ nullptr };
	SDL_Texture* m_ballTexture{ nullptr };
	Clock* m_clock;
};