#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <string>
using namespace std;


string defaultBoard = "__";
string defaultPlayer1 = "X";
string defaultPlayer2 = "Y";
// cout<<'dsa'<<endl;
void createBoard(string **board, int size){
	for (int i=0; i < size; i++){
		for (int j=0; j < size; j++){
			board[i][j] = defaultBoard;
		}
	}
}

void displayBoard(string **board, int size){
	for (int i=0; i < size; i++){
		for (int j=0; j<size; j++){
			cout<<board[i][j]<<"  ";
		}
		cout<<endl<<endl;
	}
}

int *playerTurns(int playerTurn, int size, string **board){
	cout<<"PLayer " + to_string(playerTurn) + " turn"<<endl<<endl;
	displayBoard(board, size);
	static int coords[2];
	while(true){
		cout<<"Enter x and y of the turn seperated by space eg. (1 2):";
		int x;
		int y;
		cin>>x>>y;
		if (x >= size  || y >= size){
			cout<<"Invalid credentials"<<endl;
		} else if (board[x][y] != defaultBoard){
			cout<<"Place already filled"<<endl;
		} else{
			if (playerTurn == 1){
				board[x][y] = defaultPlayer1;
			} else{
				board[x][y] = defaultPlayer2;
			}
			coords[0] = x;
			coords[1] = y;
			system("clear");
			break;
		}
		 
	}
	return coords;
}

bool playerWin(string **board, int size, int player_id, int x, int y){
	string defaultPlayers[2] = {defaultPlayer1, defaultPlayer2};
	bool x_row = true;
	bool y_row = true;
	bool diag_row = true;
	for (int i=0; i<size; i++){
		if (board[x][i] != defaultPlayers[player_id-1]){
			x_row = false;
		}
		if (board[i][y] != defaultPlayers[player_id-1]){
			y_row = false;
		}
		if (x == y){
			if (board[i][i] != defaultPlayers[player_id-1]){
				diag_row = false;
			}	
		}
	}
	if (x_row || y_row || (diag_row && x==y)){
		return true;
	} else{
		return false;
	}
}

int main(int argc, char **argv){
	// cout<<'dsa'<<endl;
	int size = 0;
	string sizeGiven = argv[1];

	try{
		size = stoi(sizeGiven);

	} catch(...) {
		cout<<"Invalid size"<<endl;
		exit(1);
	}
	
	if (size <=0){
		cout<<"Invalid board size"<<endl;
		exit(1);
	}

	string **board = new string*[size];
	for (int i = 0; i < size; i++){
		board[i] = new string[size];
	}

	createBoard(board, size);

	int *coords = new int[2];
	while(true){
		coords = playerTurns(1, size, board);
		cin.ignore();
		cin.clear();		
		// displayBoard(board, size);
		if (playerWin(board, size, 1, coords[0], coords[1])){
			cout<<"Player 1 has won"<<endl;
			break;
		}
		coords = playerTurns(2, size, board);
		cin.ignore();
		cin.clear();
		if (playerWin(board, size, 2, coords[0], coords[1])){
			cout<<"Player 2 has won"<<endl;
			break;
		}
		// displayBoard(board, size);
	}


	return 0;
}