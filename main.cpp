/**
 * @file main.cpp
 * @author Marko Silokunnas
 *
 * Entry point of the program.
 */
#include "include/core/GameProgram.h"

/* Our program's entry point */
int main(int argc, char *argv[])
{
	GameProgram gameProgram;

    return gameProgram.execute();
}
