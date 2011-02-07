/**
 * @file main.cpp
 * @author Marko Silokunnas
 *
 * Entry point of the program.
 */

#include "include/core/gameprogram.h"
#include <SDL/SDL.h>

#ifdef __linux__
int main(int argc, char *argv[])
{
	GameProgram gameProgram;

    return gameProgram.execute();
}
#endif

#ifdef WIN32

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    GameProgram gameProgram;

    return gameProgram.execute();
}

#endif
