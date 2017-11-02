//**************************
//
// program: prog8-othello.h(stage 3)
//
// Name :Zhaojie Chen
//
// Introduce :The othello class, child of game class.
//            
//
// Email :zc700015@ohio.edu
//
//
// Date : 12/01/2016
//
/**********************************************************/
#ifndef OTHELLO_H
#define OTHELLO_H
#include "game.h"
#include "piece.h"
#include "colors.h"

using namespace std;
namespace main_savitch_14
{
	class Othello:public game{
		public:
			Othello();
			~Othello();
			Othello(const Othello& other);
			game* clone( ) const;
			void make_move(const std::string& move);
			void restart( );
			void display_status( )const;
			bool is_legal(const std::string& move)const;
			void display_message(const std::string& message) const;
			bool is_game_over( ) const;
			void compute_moves(std::queue<std::string>& moves) const;
			int evaluate( ) const;
			void flip_flip(int a,int b,int c,int d);
			void pass(std::string move);
			bool up_legal(int a, int b, int c, int d)const;
			bool down_legal(int a, int b, int c, int d)const;
			bool left_legal(int a, int b, int c, int d)const;
			bool right_legal(int a, int b, int c, int d)const;
			bool left_up_legal(int a, int b, int c, int d)const;
			bool right_up_legal(int a, int b, int c, int d)const;
			bool left_down_legal(int a, int b, int c, int d)const;
			bool right_down_legal(int a, int b, int c, int d)const;
			bool all_legal(int a, int b, int c, int d)const;
			bool human_legal()const;
			bool computer_legal()const;
			who winning( ) const;
		private:
			Piece *board;
	};
}

#endif
