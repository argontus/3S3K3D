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
#include <windows.h>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPredInstance, LPSTR lpCmdLine, int nShowCmd)
{
    GameProgram gameProgram;

    return gameProgram.execute();
}
#endif
