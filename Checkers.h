/*********************************************************************************************
    This is the header file for the checkers class. It is a child class of the game class,
    and a game of checkers may be started using the play() function.

    Author: Connor Abla
*********************************************************************************************/


#include "game.h"
#include "Space.h"

class Checkers : public main_savitch_14::game
{
	public:
    
	   Checkers( ) {restart();}

    	void make_move(const std::string& move);
    	void restart( );

    	void display_status( ) const;

    	bool is_legal(const std::string& move) const;

    private:
        space Board[8][8];

        bool Legal_Opponent(const int& x1, const int& x2, const int& y1, const int& y2) const;
        bool Legal_Player(const int& x1, const int& x2, const int& y1, const int& y2) const;

        bool check_dbl_jump(const int& x, const int& y);
        bool force_jump() const;

        bool is_game_over() const;

        void extra_move(int x, int y);

        game* clone() const;
        void compute_moves(std::queue<std::string>& moves) const;
        int evaluate() const;


        who winning() const;
    	
};