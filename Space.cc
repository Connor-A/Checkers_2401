/*************************************************************************************************************
	This is the implenation file for the Space class. It only conatins the larger functions of space

	Author: Connor Abla
**************************************************************************************************************/

#include "Space.h"
#include "colors.h"
#include <iostream>


void space::output() const
{ 
	if(isRed())
	{
		std::cout << B_RED << "       ";
	}
	else
	{
		if(has_piece)
		{
			if(is_king)
			{
				if(team1)
					std::cout << B_BLACK << CYAN << " <=" << BLUE << "#" << CYAN << "=> " << WHITE;
				else
					std::cout << B_BLACK << MAGENTA << " <=" << RED << "#" << MAGENTA << "=> " << WHITE;
			}
			else
			{	
				if(team1)
					std::cout << B_BLACK << CYAN << " <===> " << WHITE;
				else
					std::cout << B_BLACK << MAGENTA << " <===> " << WHITE;
			}
		}
		else
			std::cout << B_BLACK << "       ";
	}

	cout << B_BLACK;
}

bool space::isempty() const
		{
			if(has_piece == true)
				return false;
			else
				return true;
		}