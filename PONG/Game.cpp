#include "Game.h"

bool Game::init(const char* title, int width, int height)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		std::cout << "SDL could not initialize. Error: " << SDL_GetError() << '\n';
		return false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
			std::cout << "Warning: linear texture filtering not enabled.\n";
	}

	if (!(IMG_Init(IMG_INIT_PNG)))
	{
		std::cout << "SDL_Image could not initialize. Error: " << IMG_GetError() << '\n';
		return false;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "SDL_Mixer could not initialize. Error: " << Mix_GetError() << '\n';
		return false;
	}

	m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

	if (m_window == nullptr)
	{
		std::cout << "Window could not be created. SDL Error: " << SDL_GetError() << '\n';
		return false;
	}
	else
	{
		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		if (m_renderer == nullptr)
		{
			std::cout << "Renderer could not be created. SDL Error: " << SDL_GetError() << '\n';
			return false;
		}
	}

	m_leftPaddle = new Paddle(1);
	m_rightPaddle = new Paddle(2);
	m_ball = new Ball;
	m_ballTexture = loadTexture("Resources/Dot.bmp");
	if (m_ballTexture == nullptr)
		std::cout << "Could not load texture\n";

	m_clock = new Clock;

	return true;
}

void Game::gameLoop()
{
	while (isRunning)
	{
		m_clock->tick();
		handleEvent();
		update();
		draw();
	}
}

void Game::shutdown()
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	m_renderer = nullptr;
	m_window = nullptr;

	delete m_leftPaddle;
	delete m_rightPaddle;
	m_leftPaddle = nullptr;
	m_rightPaddle = nullptr;

	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* Game::loadTexture(const char* path)
{
	SDL_Texture* texture{ nullptr };

	SDL_Surface* loadedSurface = IMG_Load(path);
	if (loadedSurface == nullptr)
		std::cout << "Unable to load image " << path << "! SDL_Image Error:" << IMG_GetError() << '\n';
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		texture = SDL_CreateTextureFromSurface(m_renderer, loadedSurface);
		if (texture == nullptr)
			std::cout << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << '\n';

		SDL_FreeSurface(loadedSurface);
	}

	return texture;
}

void Game::handleEvent()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			isRunning = false;

		if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_w:
				m_leftPaddle->changeVel(-PADDLE_SPEED);
				break;
			case SDLK_s:
				m_leftPaddle->changeVel(PADDLE_SPEED);
				break;
			case SDLK_UP:
				m_rightPaddle->changeVel(-PADDLE_SPEED);
				break;
			case SDLK_DOWN:
				m_rightPaddle->changeVel(PADDLE_SPEED);
				break;
			}

		}
		if (event.type == SDL_KEYUP && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_w:
				m_leftPaddle->changeVel(PADDLE_SPEED);
				break;
			case SDLK_s:
				m_leftPaddle->changeVel(-PADDLE_SPEED);
				break;
			case SDLK_UP:
				m_rightPaddle->changeVel(PADDLE_SPEED);
				break;
			case SDLK_DOWN:
				m_rightPaddle->changeVel(-PADDLE_SPEED);
				break;
			}
		}
	}
}

void Game::update()
{
	m_leftPaddle->move();
	m_rightPaddle->move();
	m_ball->move(m_clock, m_leftPaddle, m_rightPaddle);
}

void Game::draw()
{
	SDL_SetRenderDrawColor(m_renderer, 40, 40, 40, 0xFF);
	SDL_RenderClear(m_renderer);

	SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(m_renderer, m_leftPaddle->getRect());
	SDL_RenderFillRect(m_renderer, m_rightPaddle->getRect());

	SDL_RenderCopy(m_renderer, m_ballTexture, NULL, m_ball->getRect());

	SDL_RenderPresent(m_renderer);
}