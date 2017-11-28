// File: othello.cxx
/**
*@file othello.cc
*@brief This is a file includes check_move check game over and some other functions
*@author Shipeng Yang, Zhaojie Chen, Bohong Li, Xudong Yuan
*@date 2017/11/12
*/
#include "othello.h"
#include <iostream>
#include <stdio.h>
#include <queue>

using namespace std;
namespace main_savitch_14
{
	Othello::Othello(){
		board = new Piece;
	}
	
	Othello::~Othello(){
		Piece *rmptr;
		rmptr = board;
		delete rmptr;
	}
	
	Othello::Othello(const Othello& other){
		board = new Piece(*other.board);
	}

	void Othello::make_move(const string& move){
		int hor;
		int ver;
		if(isupper(move[0])){
			ver = int(move[0] - 'A');
		}
		else if(islower(move[0])){
			ver = int(move[0] - 'a');
		}
		hor = int(move[1] - '1');
		if(next_mover() == HUMAN)
			flip_flip(hor,ver,0,1);
		else
			flip_flip(hor,ver,1,0);
		game::make_move(move);
		pass(move);		
	}

	game* Othello::clone() const
	{
	 return new Othello(*this);
	}

/**
* @brief restart the game
*/
	void Othello::restart(){
		for(int i = 0;i < 8;i++){
			for(int j = 0; j < 8;j++){
				board -> flip(i,j,-1);
			}
		}
		board -> flip(3,3,1);
		board -> flip(4,4,1);
		board -> flip(3,4,0);
		board -> flip(4,3,0);
		game::restart();
	}

/**
* @brief display current status
*
* @see is_black()
* @see is_white()
* @see is_empty()
* @see is_game_over()
*/	
	void Othello::display_status()const{
		cout << endl;
		cout << B_GREEN;
		cout << B_GREEN<< RED << "+---+---+---+---+---+---+---+---+---+---+"<< B_WHITE << endl;
		cout << B_GREEN<< RED << "|   | A | B | C | D | E | F | G | H |   |"<< B_WHITE << endl;
		cout << B_GREEN<< RED << "+---+---+---+---+---+---+---+---+---+---+"<< B_WHITE << endl;
		for(int i = 0; i < 8; i++){
			cout << B_GREEN<< RED <<"| " << RED << i+1 << RED << " |";
			for(int j = 0; j < 8; j++){
				if(board -> is_empty(i,j)){
					cout << RED << "   |";
				}
				else if(board -> is_black(i,j)){
					cout << BLACK << " @ " << RED << "|";
				}
				else if(board -> is_white(i,j)){
					cout << WHITE << " @ " << RED << "|";
				}
			}
			cout << B_GREEN<< " " << RED << i+1 << RED << " |" << B_WHITE << endl;
			cout << B_GREEN<< RED << "+---+---+---+---+---+---+---+---+---+---+"<< B_WHITE << endl;
		}
		cout << B_GREEN<< RED << "|   | A | B | C | D | E | F | G | H |   |"<< B_WHITE << endl;
		cout << B_GREEN<< RED << "+---+---+---+---+---+---+---+---+---+---+"<< B_WHITE << endl << endl;
		cout << BLACK;
		cout << B_WHITE;
		cout << B_WHITE;
		if(is_game_over()){
			if(winning() == HUMAN){
				cout << "Player 1 win !" << endl;
			}
			else if(winning() == COMPUTER){
				cout << "Player 2 win !" << endl;
			}
			else if(winning() == NEUTRAL){
				cout << "DRAW!" << endl;
			}
		}
	}

/**
* @brief check if the location player choose is legal or not
*
* @param move the location which player choose
* @see next_move()
* @see get_piese()
* @see all_legal()
* @return return true if the move is legal otherwise false
*/	
	bool Othello::is_legal(const string& move)const{
		int hor;
		int ver;
		if(isupper(move[0])){
			ver = int(move[0] - 'A');
		}
		else if(islower(move[0])){
			ver = int(move[0] - 'a');
		}
		if(!isdigit(move[1])){
			return false;
		}
		hor = int(move[1] - '1');
		if(next_mover() == HUMAN){
			if((hor>=0&&hor<8)&&(ver>=0&&ver<8))
				if(board -> get_piece(hor,ver) == -1){
					if(all_legal(hor,ver,0,1)){
						return true;
				}
			}
		}
		else{
			if((hor>=0&&hor<8)&&(ver>=0&&ver<8))
				if(board -> get_piece(hor,ver) == -1){
					if(all_legal(hor,ver,1,0)){
						return true;
					}
			}
		}
	}

/**
* @brief display the message for next step
*
* @param message it is used for checking if it is legal move
* @see next_move()
* @see display_message()
*/
	void Othello::display_message(const string& message)const{
		if(message != "Illegal move.\n"){
			if(next_mover() == HUMAN){
				cout << BLACK << "You are Player 1, your piece is: " << BLACK << "@" << endl;
				cout << BLACK <<"Please enter the piece location(such as: A3)" << endl;
				game::display_message(message);
			}
			else{
				cout << BLACK << "You are Player 2, your piece is: " << B_BLACK << WHITE << "@" << B_WHITE << endl;
				cout << BLACK <<"Please enter the piece location(such as: A3)" << endl;
				game::display_message(message);
			}
		}
		else
			game::display_message(message);
	}


/**
* @brief check if game is over
*
* @return return true if game is over
* @see get_piese()
* @see human_legal()
* @see computer_legal()
* @return return true if the game is over
*/	
	bool Othello::is_game_over( ) const{
		int over = 0;
		for(int i = 0; i < 8; i++){
			for(int j = 0; j < 8; j++){
				if(board -> get_piece(i,j) == -1){
					over ++;
				}
			}
		}
		if(over == 0) return true;
		else if(!human_legal()&&!computer_legal()){
			return true;
		}
	}

/**
* @brief for AI the make sure different location has different value
*
* @see is_black()
* @see is_white()
* @return the total evalueta value to know which location the best choice
*/
	int Othello::evaluate(char level) const{
		int eva = 0;
		if(level == 'e'|| level == 'E'){
			return 0;
		}
		else if(level == 'n' || level == 'N'){
			if(board -> is_black(0,0))
				eva -= 100;
			if(board -> is_black(0,7))
				eva -= 100;
			if(board -> is_black(7,0))
				eva -= 100;
			if(board -> is_black(7,7))
				eva -= 100;
			if(board -> is_white(0,0)){
				eva += 100;
			}
			if(board -> is_white(0,7)){
				eva += 100;
			}
			if(board -> is_white(7,0)){
				eva += 100;
			}
			if(board -> is_white(7,7)){
				eva += 100;
			}
			for(int i = 1; i < 7; i++){
				if(board -> is_black(0,i)){
					eva -= 50;
				}
				else if(board -> is_white(0,i)){
					eva += 50;
				}
			}
			for(int i = 1; i < 7; i++){
				if(board -> is_black(7,i)){
					eva -= 50;
				}
				else if(board -> is_white(7,i)){
					eva += 50;
				}
			}
			for(int i = 1; i < 7; i++){
				for(int j = 1; j < 7; j++){
					if(board -> is_black(i,j)){
						eva-=5;
					}
					else if(board -> is_white(i,j)){
						eva+=5;
					}
				}
			}
		return eva;		
		}
		else if(level == 'h' || level == 'H'){
			if(board -> is_black(0,0))
				eva -= 100;
			if(board -> is_black(0,7))
				eva -= 100;
			if(board -> is_black(7,0))
				eva -= 100;
			if(board -> is_black(7,7))
				eva -= 100;
			if(board -> is_white(0,0)){
				eva += 100;
			}
			if(board -> is_white(0,7)){
				eva += 100;
			}
			if(board -> is_white(7,0)){
				eva += 100;
			}
			if(board -> is_white(7,7)){
				eva += 100;
			}
			for(int i = 1; i < 7; i++){
				if(board -> is_black(0,i)){
					if(i == 1 || i == 6)
						eva += 50;
					else
						eva -= 50;
				}
				else if(board -> is_white(0,i)){
					if(i == 1 || i == 6){
						eva -= 50;
					}
					else{
						eva += 50;
					}
				}
			}
			for(int i = 1; i < 7; i++){
				if(board -> is_black(7,i)){
					if(i == 1 || i == 6)
						eva += 50;
					else
						eva -= 50;
				}
				else if(board -> is_white(7,i)){
					if(i == 1 || i == 6){
						eva -= 50;
					}
					else{
						eva += 50;
					}
				}
			}
			for(int i = 1; i < 7; i++){
				if(board -> is_black(i,0)){
					if(i == 1 || i == 6)
						eva += 50;
					else
						eva -= 50;
				}
				else if(board -> is_white(i,0)){
					if(i == 1 || i == 6){
						eva -= 50;
					}
					else{
						eva += 50;
					}
				}
			}
			for(int i = 1; i < 7; i++){
				if(board -> is_black(i,7)){
					if(i == 1 || i == 6)
						eva += 50;
					else
						eva -= 50;
				}
				else if(board -> is_white(i,7)){
					if(i == 1 || i == 6){
						eva -= 50;
					}	
					else{
						eva += 50;
					}
				}
			}
			for(int i = 1; i < 7; i++){
				for(int j = 1; j < 7; j++){
					if(board -> is_black(1,1)||board -> is_black(1,6)||board -> is_black(6,1)||board -> is_black(6,6))
					{
						eva += 80;
					}
					else if(board -> is_white(1,1)||board -> is_white(1,6)||board -> is_white(6,1)||board -> is_white(6,6)){
						eva -= 80;
					}
					else if(board -> is_black(i,j)){
						eva-=5;
					}
					else if(board -> is_white(i,j)){
						eva+=5;
					}
				}
			}
		}
		return eva;
	}

/**
* @brief check if someone can move next step move
*
* @see is_game_over()
* @see make_move()
* @see computer_legal()
* @see human_legal()
*/	
	void Othello::pass(string pass){ 
		if(!is_game_over()){
			if(next_mover() == HUMAN){
				if(!human_legal()){
					cout << "Player 1 should pass" << endl;
					game::make_move(pass);
				}
			}
			else{
				if(!computer_legal()){
					cout << "Player 2 should pass" << endl;
					game::make_move(pass);
				}
			}
		}
	}

/**
* @brief check if up side is legal
*
* @see get_piece()
* @return return true if it is legal
*/
	bool Othello::up_legal(int a, int b, int c, int d)const{
		if(a == 0){
			return false;;
		}
		if(board -> get_piece(a-1,b) != d){
			return false;
		}
		else if(board -> get_piece(a-1,b) == d){
			for(int i = a-1; board -> get_piece(i,b) != -1 && i >= 0; i--){
				if(board -> get_piece(i,b) == c){
					return true;
				}
			}
		return false;
		}
	}
/**
* @brief check if down side is legal
*
* @see get_piece()
* @return return true if it is legal
*/
	bool Othello::down_legal(int a, int b, int c, int d)const{
		if(board -> get_piece(a+1,b) != d){
			return false;
		}
		else if(board -> get_piece(a+1,b) == d){
			for(int i = a+1;board -> get_piece(i,b) != -1 && i < 8; i++){
				if(board -> get_piece(i,b) == c){
					return true;
				}
			}
		}
		return false;
	}

/**
* @brief check if left side is legal
*
* @see get_piece()
* @return return true if it is legal
*/
	bool Othello::left_legal(int a, int b, int c, int d)const{
		if(board -> get_piece(a,b-1) != d){
			return false;
		}
		if(b == 0){
			return false;
		}
		else if(board -> get_piece(a,b-1) == d){
			for(int i = b-1;board -> get_piece(a,i) != -1 && i >= 0; i--){
				if(board -> get_piece(a,i) == c){
					return true;
				}
			}
		}
		return false;
	}

/**
* @brief check if right side is legal
*
* @see get_piece()
* @return return true if it is legal
*/
	bool Othello::right_legal(int a, int b, int c, int d)const{
		if(board -> get_piece(a,b+1) != d){
			return false;
		}
		else if(board -> get_piece(a,b+1) == d){
			for(int i = b+1; board -> get_piece(a,i) != -1 && i < 8; i++){
				if(board -> get_piece(a,i) == c){
					return true;
				}
			}
		}
		return false;
	}

/**
* @brief check if left up side is legal
*
* @see get_piece()
* @return return true if it is legal
*/
	bool Othello::left_up_legal(int a, int b, int c, int d)const{
		if(a == 0){
			return false;
		}
		if(b == 0){
			return false;
		}
		if(board -> get_piece(a-1,b-1) != d){
			return false;
		}
		else if(board -> get_piece(a-1,b-1) == d){
			for(int i = a-1,j = b-1;board -> get_piece(i,j) != -1 && i >= 0 && j >= 0; i--,j--){
				if(board -> get_piece(i,j) == c){
						return true;
				}
			}
		}
		return false;
	}

/**
* @brief check if right up side is legal
*
* @see get_piece()
* @return return true if it is legal
*/
	bool Othello::right_up_legal(int a, int b, int c, int d)const{
		if(a == 0){
			return false;;
		}
		if(board -> get_piece(a-1,b+1) != d){
			return false;
		}
		else if(board -> get_piece(a-1,b+1) == d){
			for(int i = a-1,j = b+1;board -> get_piece(i,j) != -1&& i >= 0 && j < 8; i--,j++){
				if(board -> get_piece(i,j) == c){
						return true;
				}
			}
		}
		return false;
	}

/**
* @brief check if left down side is legal
*
* @see get_piece()
* @return return true if it is legal
*/
	bool Othello::left_down_legal(int a, int b, int c, int d)const{
		if(b == 0){
			return false;
		}
		if(board -> get_piece(a+1,b-1) != d){
			return false;
		}
		else if(board -> get_piece(a+1,b-1) == d){
			for(int i = a+1,j = b-1;board -> get_piece(i,j) != -1&& i < 8 && j >= 0; i++,j--){
				if(board -> get_piece(i,j) == c){
						return true;
				}
			}
		}
		return false;
	}

/**
* @brief check if right down side is legal
*
* @see get_piece()
* @return return true if it is legal
*/
	bool Othello::right_down_legal(int a, int b, int c, int d)const{
		if(board -> get_piece(a+1,b+1) != d){
			return false;
		}
		else if(board -> get_piece(a+1,b+1) == d){
			for(int i = a+1,j = b+1;board -> get_piece(i,j) != -1&& i < 8 && j < 8; i++,j++){
				if(board -> get_piece(i,j) == c){
						return true;
				}
			}
		}
		return false;
	}


/**
* @brief combine all check sides
*
* @see up_legal()
* @see down_legal()
* @see left_legal()
* @see right_legal()
* @see left_up_legal()
* @see right_up_legal()
* @see left_down_legal()
* @see right_down_legal()
* @see human_legal()
* @see get_piece()
* @see all_legal()
* @return return true if it is legal
*/
	bool Othello::all_legal(int a, int b, int c, int d)const{
		if(up_legal(a,b,c,d)||down_legal(a,b,c,d)||left_legal(a,b,c,d)||right_legal(a,b,c,d)||left_up_legal(a,b,c,d)||right_up_legal(a,b,c,d)||left_down_legal(a,b,c,d)||right_down_legal(a,b,c,d)){
			return true;
		}
		else return false;
	}

	bool Othello::human_legal()const{
		for(int i = 0;i < 8;i++){
			for(int j = 0;j < 8;j++){
				if(board -> get_piece(i,j) == -1){
					if(all_legal(i,j,0,1)){
						return true;
					}
				}
			}
		}
		return false;
	}

/**
* @brief check computer step is legal
*
* @see get_piece()
* @see all_legal()
* @return return true if it is legal
*/
	bool Othello::computer_legal()const{ 
		for(int i = 0;i < 8;i++){
			for(int j = 0;j < 8;j++){
				if(board -> get_piece(i,j) == -1){
					if(all_legal(i,j,1,0)){
						return true;
					}
				}
			}
		}
		return false;
	}

/**
* @brief check who is the winnner
*
* @see get_piece()
* @return return who wins this game otherwise return neutral
*/	
	game::who Othello::winning() const{
		int black = 0;
		for(int i = 0;i < 8;i++){
			for(int j = 0;j < 8;j++){
				if(board -> get_piece(i,j) == 0){
					black ++;
				}
				else if(board -> get_piece(i,j) == 1){
					black --;
				}
			}
		}
		if(black > 0){
			return HUMAN;
		}
		else if(black < 0){
			return COMPUTER;
		}
		else if(black == 0){
			return NEUTRAL;
		}
	}

/**
* @brief flip_flip after someone make moves
*
* @see get_piece()
* @see up_legal()
* @see down_legal()
* @see left_legal()
* @see right_legal()
* @see left_up_legal()
* @see right_up_legal()
* @see left_down_legal()
* @see right_down_legal()
*/		
	void Othello::flip_flip(int a,int b,int c,int d){
		board -> flip(a,b,c);
		if(up_legal(a,b,c,d)){
			for(int i = a-1; board -> get_piece(i,b) != c;i--){
				board -> flip(i,b,c);
			}
		}
		if(down_legal(a,b,c,d)){
			for(int i = a+1; board -> get_piece(i,b) != c;i++){
				board -> flip(i,b,c);
			}
		}
		if(left_legal(a,b,c,d)){
			for(int i = b-1; board -> get_piece(a,i) != c;i--){
				board -> flip(a,i,c);
			}
		}
		if(right_legal(a,b,c,d)){
			for(int i = b+1; board -> get_piece(a,i) != c;i++){
				board -> flip(a,i,c);
			}
		}
		if(left_up_legal(a,b,c,d)){
			for(int i = a-1,j = b-1; board -> get_piece(i,j) != c;i--,j--){
				board -> flip(i,j,c);
			}
		}
		if(right_up_legal(a,b,c,d)){
			for(int i = a-1,j = b+1; board -> get_piece(i,j) != c;i--,j++){
				board -> flip(i,j,c);
			}
		}
		if(left_down_legal(a,b,c,d)){
			for(int i = a+1, j = b-1; board -> get_piece(i,j) != c;i++,j--){
				board -> flip(i,j,c);
			}
		}
		if(right_down_legal(a,b,c,d)){
			for(int i = a+1,j = b+1; board -> get_piece(i,j) != c;i++,j++){
				board -> flip(i,j,c);
			}
		}
	}

/**
* @brief make computer move
*
* @see is_legal()
*/	

	void Othello::compute_moves(std::queue<std::string>& moves) const{
		string str;
		char ver = 'A';
		char hor = '1';
		for(ver = 'A';ver <= 'H'; ver++){
			for(hor = '1';hor <= '8'; hor++){
				str = "";
				str += ver;
				str += hor;
				if(is_legal(str))
					moves.push(str);
			}
		}
	}

}




	
	
		

					
			
					
