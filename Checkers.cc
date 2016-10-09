/***************************************************************************************************************
	This it the implementation file for the checkers class.

	Author: Connor Abla
****************************************************************************************************************/

#include "Checkers.h"
#include "game.h"
#include <iostream>
#include "colors.h"

using namespace std;

void Checkers::restart()
{
	for(int x = 0; x < 3; x++)
		for(int y = 0; y < 8; y++)
		{
			if(x % 2 == 0)
			{
				if(y % 2 == 0)
					Board[x][y].reset_empty();
				else
					Board[x][y].reset_player1();
			}
			if(x % 2 == 1)
			{
				if(y % 2 == 0)
					Board[x][y].reset_player1();
				else
					Board[x][y].reset_empty();
			}
		}

	for(int x = 3; x < 5; x++)
		for(int y = 0; y < 8; y++)
			Board[x][y].reset_empty();

	for(int x = 5; x < 8; x++)
		for(int y = 0; y < 8; y++)
		{
			if(x % 2 == 0)
			{
				if(y % 2 == 0)
					Board[x][y].reset_empty();
				else
					Board[x][y].reset_player2();
			}
			if(x % 2 == 1)
			{
				if(y % 2 == 0)
					Board[x][y].reset_player2();
				else
					Board[x][y].reset_empty();
			}
		}

	for(int x = 0; x < 8; x++)
		for(int y = 0; y < 8; y++)
		{
			if(x % 2 == 0)
			{
				if(y % 2 == 0)
					Board[x][y].setRed();
				else 
					Board[x][y].setBlack();
			}
			if(x % 2 == 1)
			{
				if(y % 2 == 0)
					Board[x][y].setBlack();
				else 
					Board[x][y].setRed();
			}
		}

	return;
}

bool Checkers::is_legal(const string& move) const
{
	int x1, x2, y1, y2;
	x1 = (int)move[0] - (int)'A';
	x2 = (int)move[2] - (int)'A';
	y1 = (int)move[1] - (int)'1';
	y2 = (int)move[3] - (int)'1';

	if((x1 >= 0 && x1 < 8) && (x2 >= 0 && x2 < 8) && (y1 >= 0 && y1 < 8) && (y2 >= 0 && y2 < 8))
	{
		if(Board[x2][y2].isempty() == false)
			return false;

		else if(Board[x1][y1].get_team() && moves_completed() % 2 == 0)
			return Legal_Player(x1,x2,y1,y2);

		else if(!Board[x1][y1].get_team() && moves_completed() % 2 == 1)
			return Legal_Opponent(x1,x2,y1,y2);
	}
	else
		return false;
}

bool Checkers::Legal_Opponent(const int& x1, const int& x2, const int& y1, const int& y2) const
{
	if(Board[x1][y2].isKing())
	{
		if((x2 == x1 + 2) && (y2 == y1 + 2))
		{
			if(Board[x1+1][y1+1].get_team() == true && !(Board[x1+1][y1+1].isempty()))
				return true;
		}
		else if((x2 == x1 + 2) && (y2 == y1 - 2))
		{
			if(Board[x1+1][y1-1].get_team() == true && !(Board[x1+1][y1-1].isempty()))
				return true;
		}

		else if((x2 == x1 + 1) && (y2 == y1 + 1 || y2 == y1 - 1) && force_jump() == true)
			return true;
	}

	else
	{
		if((x2 == x1 - 2) && (y2 == y1 + 2))
		{
			if(Board[x1-1][y1+1].get_team() == true && !(Board[x1-1][y1+1].isempty()))
				return true;
		}
		else if((x2 == x1 - 2) && (y2 == y1 - 2) && !(Board[x1-1][y1-1].isempty()))
		{
			if(Board[x1-1][y1-1].get_team() == true)
				return true;
		}
		else if((x2 == x1 - 1) && (y2 == y1 + 1 || y2 == y1 - 1) && force_jump() == true)
			return true;
	}

	return false;
}

bool Checkers::Legal_Player(const int& x1, const int& x2, const int& y1, const int& y2) const
{
	if(Board[x1][y1].isKing())
	{
		if((x2 == x1 - 2) && (y2 == y1 + 2))
		{
			if(Board[x1-1][y1+1].get_team() == false && !(Board[x1-1][y1+1].isempty()))
				return true;
		}
		else if((x2 == x1 - 2) && (y2 == y1 - 2) && !(Board[x1-1][y1-1].isempty()))
		{
			if(Board[x1-1][y1-1].get_team() == false)
				return true;
		}

		else if((x2 == x1 - 1) && (y2 == y1 + 1 || y2 == y1 - 1) && force_jump() == true)
			return true;
	}


	else
	{
		if((x2 == x1 + 2) && (y2 == y1 + 2))
		{
			if(Board[x1+1][y1+1].get_team() == false && !(Board[x1+1][y1+1].isempty()))
				return true;
		}
		else if((x2 == x1 + 2) && (y2 == y1 - 2))
		{
			if(Board[x1+1][y1-1].get_team() == false && !(Board[x1+1][y1-1].isempty()))
				return true;
		}

		else if((x2 == x1 + 1) && (y2 == y1 + 1 || y2 == y1 - 1) && force_jump() == true)
			return true;
	}

	 return false;
}

void Checkers::display_status() const
{
	cout << "    --------------------------------------------------------\n";
	

	for(int x = 7; x > -1; x--)
		for(int z = 0; z < 3; z++)
		{
			if(z == 1)
				cout << " " << (char)(x + (int)'A') << " |";
			else
				cout << "   |";
			for(int y = 0; y < 8; y++)
			{
				Board[x][y].output();
				cout << B_BLACK;
			}
			cout << "|" << endl;
		}


	cout << "    --------------------------------------------------------\n";
	cout << "       1      2      3      4      5      6      7      8   \n";

}

void Checkers::make_move(const string& move)
{
	int x1, x2, y1, y2;
	x1 = (int)move[0] - (int)'A';
	x2 = (int)move[2] - (int)'A';
	y1 = (int)move[1] - (int)'1';
	y2 = (int)move[3] - (int)'1';

	if((x2 == x1 + 2) && (y2 == y1 + 2))
		Board[x1+1][y1+1].reset_empty();
	
	if((x2 == x1 - 2) && (y2 == y1 + 2))
		Board[x1-1][y1+1].reset_empty();

	if((x2 == x1 + 2) && (y2 == y1 - 2))
		Board[x1+1][y1-1].reset_empty();

	if((x2 == x1 - 2) && (y2 == y1 - 2))
		Board[x1-1][y1-1].reset_empty();

	Board[x2][y2] = Board[x1][y1];

	Board[x1][y1].reset_empty();

	
	
	if(x2 == x1 + 2 || x2 == x1 - 2)
	{
		if(check_dbl_jump(x2,y2) == true)
			extra_move(x2,y2);
	}


	if((x2 == 7 && Board[x2][y2].get_team()) || (x2 == 0 && Board[x2][y2].get_team() == false))
		Board[x2][y2].king_me();

	
}

bool Checkers::check_dbl_jump(const int& x, const int& y)
{
	if(moves_completed() % 2 == 0)
	{
		if(!(x + 2 > 7))
		{
			if(!(y + 2 > 7))
			{
				if(Board[x][y].get_team() == true && !(Board[x+1][y+1].isempty()) && (Board[x+1][y+1].get_team() == false) && (Board[x+2][y+2].isempty()))
					return true;
			}
			if (!(y - 2 < 0))
			{
				if(Board[x][y].get_team() == true && !(Board[x+1][y-1].isempty()) && (Board[x+1][y-1].get_team() == false) && (Board[x+2][y-2].isempty()))
					return true;
			}
		}
		if(!(x - 2 < 0) && Board[x][y].isKing())
		{
			if(!(y + 2 > 7))
			{
				if(Board[x][y].get_team() == true && !(Board[x-1][y+1].isempty()) && (Board[x-1][y+1].get_team() == false) && (Board[x-2][y+2].isempty()))
					return true;
			}
			if (!(y - 2 < 0))
			{
				if(Board[x][y].get_team() == true && !(Board[x-1][y-1].isempty()) && (Board[x-1][y-1].get_team() == false) && (Board[x-2][y-2].isempty()))
					return true;
			}
		}

		return false;
	}

	/*else if(moves_completed() % 2 == 1)
	{

		if(!(x + 2 > 7) && Board[x][y].isKing())
		{
			if(!(y + 2 > 7))
			{
				if(Board[x][y].get_team() == false && !(Board[x+1][y+1].isempty()) && (Board[x+1][y+1].get_team() == true) && (Board[x+2][y+2].isempty()))
					return true;
			}
			if (!(y - 2 < 0))
			{
				if(Board[x][y].get_team() == false && !(Board[x+1][y-1].isempty()) && (Board[x+1][y-1].get_team() == true) && (Board[x+2][y-2].isempty()))
					return true;
			}
		}
		if(!(x - 2 < 0))
		{
			if(!(y + 2 > 7))
			{
				if(Board[x][y].get_team() == false && !(Board[x-1][y+1].isempty()) && (Board[x-1][y+1].get_team() == true) && (Board[x-2][y+2].isempty()))
					return true;
			}
			if (!(y - 2 < 0))
			{
				if(Board[x][y].get_team() == false && !(Board[x-1][y-1].isempty()) && (Board[x-1][y-1].get_team() == true) && (Board[x-2][y-2].isempty()))
					return true;
			}
		}

		return false;
	}
	*/ //AI DOES NOT LIKE DOUBLE JUMPING. MANY PROBLEMS.
	return false;
}

bool Checkers::is_game_over() const
{
	bool over1 = true;
	bool over2 = true;

	for(int x = 0; x < 8; x++)
		for(int y = 0; y < 8; y++)
			if(Board[x][y].get_team() == true && Board[x][y].isempty() == false)
				over1 = false;

	for(int x = 0; x < 8; x++)
		for(int y = 0; y < 8; y++)
			if(Board[x][y].get_team() == false && Board[x][y].isempty() == false)
				over2 = false;

	if(over1 == false && over2 == false)
		return false;
	else
		return true;
}


void Checkers::extra_move(int x, int y)
{
	int x2, y2;
	string move;

	x2 = (int)move[2] - (int)'A';
    y2 = (int)move[3] - (int)'1';


	if(moves_completed() % 2 == 0)
	{

		display_status();
		cout << "DOUBLE JUMP!\n";

		move = get_user_move( );
		while (!is_legal(move) && !(x == x2) && !(y == y2))
		{
		    display_message("Illegal move.\n");
		    move = get_user_move( );
	    }
		make_move(move);
	}	    
}

bool Checkers::force_jump() const//returns false if the PLAYER CAN MAKE A JUMP
{
	if(moves_completed() % 2 == 0)
	{
		for(int x = 0; x < 8; x++)
		{
			for(int y = 0; y < 8; y++)
			{
				if(!(x + 2 > 7))
				{
					if(!(y + 2 > 7))
					{
						if(!(Board[x][y].isempty()) && Board[x][y].get_team() == true && !(Board[x+1][y+1].isempty()) && (Board[x+1][y+1].get_team() == false) && (Board[x+2][y+2].isempty()))
							return false;
					}
					if (!(y - 2 < 0))
					{
						if(!(Board[x][y].isempty()) && Board[x][y].get_team() == true && !(Board[x+1][y-1].isempty()) && (Board[x+1][y-1].get_team() == false) && (Board[x+2][y-2].isempty()))
							return false;
					}
				}
				if(!(x - 2 < 0) && Board[x][y].isKing())
				{
					if(!(y + 2 > 7))
					{
						if(!(Board[x][y].isempty()) && Board[x][y].get_team() == true && !(Board[x-1][y+1].isempty()) && (Board[x-1][y+1].get_team() == false) && (Board[x-2][y+2].isempty()))
							return false;
					}
					if (!(y - 2 < 0))
					{
						if(!(Board[x][y].isempty()) && Board[x][y].get_team() == true && !(Board[x-1][y-1].isempty()) && (Board[x-1][y-1].get_team() == false) && (Board[x-2][y-2].isempty()))
							return false;
					}
				}
			}
		}

		return true;
	}


	else if(moves_completed() % 2 == 1)
	{
		for(int x = 0; x < 8; x++)
		{
			for(int y = 0; y < 8; y++)
			{
				if(!(x + 2 > 7) && Board[x][y].isKing())
				{
					if(!(y + 2 > 7))
					{
						if(!(Board[x][y].isempty()) && Board[x][y].get_team() == false && !(Board[x+1][y+1].isempty()) && (Board[x+1][y+1].get_team() == true) && (Board[x+2][y+2].isempty()))
							return false;
					}
					if (!(y - 2 < 0))
					{
						if(!(Board[x][y].isempty()) && Board[x][y].get_team() == false && !(Board[x+1][y-1].isempty()) && (Board[x+1][y-1].get_team() == true) && (Board[x+2][y-2].isempty()))
							return false;
					}
				}
				if(!(x - 2 < 0))
				{
					if(!(y + 2 > 7))
					{
						if(!(Board[x][y].isempty()) && Board[x][y].get_team() == false && !(Board[x-1][y+1].isempty()) && (Board[x-1][y+1].get_team() == true) && (Board[x-2][y+2].isempty()))
							return false;
					}
					if (!(y - 2 < 0))
					{
						if(!(Board[x][y].isempty()) && Board[x][y].get_team() == false && !(Board[x-1][y-1].isempty()) && (Board[x-1][y-1].get_team() == true) && (Board[x-2][y-2].isempty()))
							return false;
					}
				}
			}
		}

		return true;
	}
}

main_savitch_14::game* Checkers::clone() const
{
	return new Checkers(*this);
}

void Checkers::compute_moves(queue<string>& moves) const
{
	char move[4];

	for(int x = 0; x < 8; x++)
	{
		for(int y = 0; y < 8; y++)
		{
			if(((x % 2 == 0 && y % 2 == 1) || (x % 2 == 1 && y % 2 == 0)) && Board[x][y].get_team() == false && Board[x][y].isempty() == false)
			{
				for(int z = 1; z < 3; z++)
				{
					move[0] = (char)x + 'A';
					move[2] = (char)(x + z) + 'A';
					move[1] = (char)y + '1';
					move[3] = (char)(y + z) + '1';

					if(is_legal(move) == true)
						moves.push(move);


					move[0] = (char)x + 'A';
					move[2] = (char)(x + z) + 'A';
					move[1] = (char)y + '1';
					move[3] = (char)(y - z) + '1';

					if(is_legal(move) == true)
						moves.push(move);


					move[0] = (char)x + 'A';
					move[2] = (char)(x - z) + 'A';
					move[1] = (char)y + '1';
					move[3] = (char)(y + z) + '1';

					if(is_legal(move) == true)
						moves.push(move);


					move[0] = (char)x + 'A';
					move[2] = (char)(x - z) + 'A';
					move[1] = (char)y + '1';
					move[3] = (char)(y - z) + '1';


					if(is_legal(move) == true)
						moves.push(move);
				}
			}
		}
	}
}

int Checkers::evaluate() const
{
	int computer_score = 0, human_score = 0;

	for(int x = 0; x < 8; x++)
	{
		for(int y = 0; y < 8; y++)
		{
			if(!(x + 2 > 7))
			{
				if(!(y + 2 > 7))
				{
					if(!(Board[x][y].isempty()) && Board[x][y].get_team() == true && !(Board[x+1][y+1].isempty()) && (Board[x+1][y+1].get_team() == false) && (Board[x+2][y+2].isempty()))
					{
						if(Board[x+1][y+1].isKing())
							human_score += 3;
						else
							human_score += 2;
					}
				}
				if (!(y - 2 < 0))
				{
					if(!(Board[x][y].isempty()) && Board[x][y].get_team() == true && !(Board[x+1][y-1].isempty()) && (Board[x+1][y-1].get_team() == false) && (Board[x+2][y-2].isempty()))
					{
						if(Board[x+1][y-1].isKing())
							human_score += 3;
						else
							human_score += 2;
					}	
				}
			}
			if(!(x - 2 < 0) && Board[x][y].isKing())
			{
				if(!(y + 2 > 7))
				{
					if(!(Board[x][y].isempty()) && Board[x][y].get_team() == true && !(Board[x-1][y+1].isempty()) && (Board[x-1][y+1].get_team() == false) && (Board[x-2][y+2].isempty()))
					{
						if(Board[x-1][y+1].isKing())
							human_score += 3;
						else
							human_score += 2;
					}
				}
				if (!(y - 2 < 0))
				{
					if(!(Board[x][y].isempty()) && Board[x][y].get_team() == true && !(Board[x-1][y-1].isempty()) && (Board[x-1][y-1].get_team() == false) && (Board[x-2][y-2].isempty()))
					{
						if(Board[x+1][y+1].isKing())
							human_score += 3;
						else
							human_score += 2;
					}
				}
			}

			if(!(Board[x][y].isempty()) && Board[x][y].get_team())
			{
				if(Board[x][y].isKing())
					human_score += 5;
				else
					human_score += 3;
			}

			
			if(!(x + 2 > 7) && Board[x][y].isKing())
			{
				if(!(y + 2 > 7))
				{
					if(!(Board[x][y].isempty()) && Board[x][y].get_team() == false && !(Board[x+1][y+1].isempty()) && (Board[x+1][y+1].get_team() == true) && (Board[x+2][y+2].isempty()))
					{
						if(Board[x+1][y+1].isKing())
							computer_score += 3;
						else
							computer_score += 2;
					}
				}
				if (!(y - 2 < 0))
				{
					if(!(Board[x][y].isempty()) && Board[x][y].get_team() == false && !(Board[x+1][y-1].isempty()) && (Board[x+1][y-1].get_team() == true) && (Board[x+2][y-2].isempty()))
					{
						if(Board[x+1][y-1].isKing())
							computer_score += 3;
						else
							computer_score += 2;
					}
				}
			}
			if(!(x - 2 < 0))
			{
				if(!(y + 2 > 7))
				{
					if(!(Board[x][y].isempty()) && Board[x][y].get_team() == false && !(Board[x-1][y+1].isempty()) && (Board[x-1][y+1].get_team() == true) && (Board[x-2][y+2].isempty()))
					{
						if(Board[x-1][y+1].isKing())
							computer_score += 3;
						else
							computer_score += 2;
					}
				}
				if (!(y - 2 < 0))
				{
					if(!(Board[x][y].isempty()) && Board[x][y].get_team() == false && !(Board[x-1][y-1].isempty()) && (Board[x-1][y-1].get_team() == true) && (Board[x-2][y-2].isempty()))
					{
						if(Board[x-1][y-1].isKing())
							computer_score += 3;
						else
							computer_score += 2;
					}
				}
			}

			if(!(Board[x][y].isempty()) && !(Board[x][y].get_team()))
			{
				if(Board[x][y].isKing())
					computer_score += 5;
				else
					computer_score += 3;
			}


		}
	}

	if(moves_completed() % 2 == 0)
		return human_score - computer_score;
	else
		return computer_score - human_score;

}

main_savitch_14::game::who Checkers::winning() const
{
	int x;
	x = evaluate();

	if(moves_completed() % 2 == 0)
	{
		if(x >= 0)
			return HUMAN;
		else
			return COMPUTER;
	}
	else
	{
		if(x <= 0)
			return HUMAN;
		else
			return COMPUTER;
	}
}