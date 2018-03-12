// Card Assignment.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "game.h"
#include "smartPointer.h"

int main()
{
	//invoke the function that controls the game logic
	smartPointer<CGame> myGame = new CGame;
	myGame->gameManager();

	std::cout << std::endl << std::endl;
	std::cout << "End of program. press ENTER to close.";
	std::cin.get();
	return 0;
}

