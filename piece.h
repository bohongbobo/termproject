//**************************
//
// program: prog8-piece.h(stage 3)
//
// Name :Zhaojie Chen
//
// Introduce :Design how the piece work.
//            
//
// Email :zc700015@ohio.edu
//
//
// Date : 12/01/2016
//
/**********************************************************/
#ifndef PIECE_H
#define PIECE_H
#include <iostream>
namespace main_savitch_14
{
	class Piece{
		public:
			Piece(){
				for(int i = 0;i < h; i++){
					for(int j = 0;j < v;j++){
						piece[i][j] = -1;
					}
				}
				piece[3][3] = 1;
				piece[4][4] = 1;
				piece[3][4] = 0;
				piece[4][3] = 0;
			}
			int get_horizontal(){
				return h;
			}
			int get_vertical(){
				return v;
			}
			int get_piece(int i,int j){
				return piece[i][j];
			}
			void flip(int i,int j,int p){
				piece[i][j] = p;
			}
			bool is_empty(int i, int j){
				return (piece[i][j] == -1);
			}
			bool is_black(int i, int j){
				return (piece[i][j] == 0);
			}
			bool is_white(int i, int j){
				return (piece[i][j] == 1);
			}
		private:
			static const int h = 10;
			static const int v = 10;
			int piece[h][v];
	};
}

#endif
