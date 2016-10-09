/**************************************************************************************
	This is the header file for the space class. It contains all the information for 
	a single checkers space.

	Author: Connot Abla

***************************************************************************************/

class space
{
	public:
		space(){has_piece = false; is_king = false; team1 = false; red = false;}

		void reset_player1()
		{has_piece = true; is_king = false; team1 = true;}
		void reset_player2()
		{has_piece = true; is_king = false; team1 = false;}
		void reset_empty()
		{has_piece = false; is_king = false;}

		void king_me()
		{is_king = true;}

		void captured()
		{has_piece = false; is_king = false;}

		void setRed()
		{red = true;}
		void setBlack()
		{red = false;}

		bool isRed() const
		{return red;}
		
		bool isempty() const;

		bool isKing() const
		{return is_king;}

		bool get_team() const
		{return team1;}



		void output() const;

	private:
		bool has_piece;
		bool is_king;
		bool team1; //if true, piece belongs to player 1. set to NULL when empty
		bool red; //if true space is red. otherwise is black;
};