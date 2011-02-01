/*
 * main.cpp
 *
 *  Created on: Jan 24, 2011
 *      Author: marant
 */
#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include "include/core/GameProgram.h"

/* Our program's entry point */
int main(int argc, char *argv[])
{
	GameProgram gameProgram;

    return gameProgram.execute();
}
