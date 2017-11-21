/**
*@file main.cc
*@brief This is the main function
*@author Shipeng Yang, Zhaojie Chen, Bohong Li, Xudong Yuan
*@date 2017/11/12
*/
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



