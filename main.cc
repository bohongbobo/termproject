//**************************
//
// program: prog8-main.cc(stage 3)
//
// Name :Zhaojie Chen
//
// Introduce :Main program start playing.
//            
//
// Email :zc700015@ohio.edu
//
//
// Date : 12/01/2016
//
/**********************************************************/
#include "game.h"
#include "othello.h"
#include <iostream>

using namespace std;

int main(){
	using namespace main_savitch_14;{
		char level;
		cout << "*************************************************************" << endl;
		cout << "*          ***  ***** *   * ***** *     *      ***          *" << endl;
		cout << "*         *   *   *   *   * *     *     *     *   *         *" << endl;
		cout << "*         *   *   *   ***** ***** *     *     *   *         *" << endl;
		cout << "*         *   *   *   *   * *     *     *     *   *         *" << endl;
		cout << "*          ***    *   *   * ***** ***** *****  ***          *" << endl;
		cout << "*************************************************************" << endl;
		cout << "Choose the level (H - hard, N - normal, E - easy) : ";
		cin >> level;
		cout << endl;
		Othello othe;
		othe.play(level);
	}
	return 0;
}



