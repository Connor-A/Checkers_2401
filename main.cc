/*****************************************************************************
	This file is used to test the checkers class.

	Author: Connor Abla
****************************************************************************/


#include "Checkers.h"
#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;
int main()
{
	Checkers game1;

	int Winner;

	Winner = game1.play();

	if(Winner == 0)

		cout << "Congratulations Human! You win!\n";

	else if (Winner == 2)
		cout << "Puny Human, I have bested you\n";

	return 0;
}