#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "Game.h"
#include "Utils.h"

int main(int argc, char* args[])
{
	Game game;

	if (game.init("Pong", SCREEN_WIDTH, SCREEN_HEIGHT))
	{
		game.gameLoop();
	}

	game.shutdown();

	return 0;
}