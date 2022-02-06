#include <iostream>
#include <windows.h>
using namespace std;
char board_show[3][3] = { '1','2','3','4','5','6','7','8','9' };
char board_calc[3][3] = { 'N','N','N','N','N','N','N','N','N' };
int Turn = 1;
int depth;
int Count_move = 0;
int Min_Max();
int Find_Move;
int Check_Move();
int Show_Move();
string result;
HANDLE console_color;

int Check_Move() {
	for (int i = 0; i < 3; i++) 
		return ((board_calc[i][0] == board_calc[i][1] && board_calc[i][1] == board_calc[i][2] && board_calc[i][0] != 'N') ||
			   ((board_calc[0][0] == board_calc[1][1] && board_calc[1][1] == board_calc[2][2] && board_calc[0][0] != 'N') ||
			    (board_calc[0][i] == board_calc[1][i] && board_calc[1][i] == board_calc[2][i] && board_calc[0][i] != 'N') ||
				(board_calc[0][2] == board_calc[1][1] && board_calc[1][1] == board_calc[2][0] && board_calc[0][2] != 'N'))) ? 1: 0;
}

int Show_Move() {
	console_color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console_color, 10);
	cout << endl;
	for (int i = 0; i < 3; i++) {
		cout << "\t\t\t\t\t | ";
		for (int j = 0; j < 3; j++) {
			if (board_show[i][j] == 'X') {
				SetConsoleTextAttribute(console_color, 12);
				cout << 'X';
			}
			if (board_show[i][j] == 'O') {
				SetConsoleTextAttribute(console_color, 9);
				cout << 'O';
			}
			if (board_show[i][j] != 'X' && board_show[i][j] != 'O') {
				SetConsoleTextAttribute(console_color, 15);
				cout << board_show[i][j];
			}
			SetConsoleTextAttribute(console_color, 10);
			cout << " | ";
		}
		cout << endl;
	}
	SetConsoleTextAttribute(console_color, 11);
	return(0);
}

int Min_Max() {
	int bestScore = 0, score = 0;
	if (Check_Move() == 1) {
		return (Find_Move == 1) ? -1 : 0;
	}
	else {
		if (depth < 9) 
			if (Find_Move == 1) {
				bestScore = -3;
				for (int i = 0; i < 3; i++)
					for (int j = 0; j < 3; j++)
						if (board_calc[i][j] == 'N') {
							board_calc[i][j] = 'O';
							Find_Move = 0;
							depth++;
							score = Min_Max();
							board_calc[i][j] = 'N';
							if (score > bestScore)
								bestScore = score;
						}
				return bestScore;
			}
			else {
				bestScore = 3;
				for (int i = 0; i < 3; i++) 
					for (int j = 0; j < 3; j++)
						if (board_calc[i][j] == 'N') {
							board_calc[i][j] = 'X';
							Find_Move = 1;
							depth++;
							score = Min_Max();
							board_calc[i][j] = 'N';
							if (score < bestScore)
								bestScore = score;
						}
				return bestScore;
			}
		else
			return 0;
	}
}

void AI_VS_Human(){
	int postion;
	while (Check_Move() == 0 && Count_move != 9){
		if (Turn == 2){
			system("CLS");
			Show_Move();
			cout << "enter position : ";
			cin >> postion;
			if (board_calc[(postion-1) / 3][(postion - 1) % 3] == 'N' && postion < 10 && postion >= 1) {
				board_calc[(postion - 1) / 3][(postion - 1) % 3] = 'X';
				board_show[(postion - 1) / 3][(postion - 1) % 3] = 'X';
				Turn = 1;
			}
		}
		else if (Turn == 1){
			int bestScore = -3, score = 0, Row_i = -1, column_i = -1;
			for (int i = 0; i < 3; i++){
				for (int j = 0; j < 3; j++) {
					if (board_calc[i][j] == 'N') {
						board_calc[i][j] = 'O';
						Find_Move = 0;
						depth = Count_move + 1;
						score = Min_Max();
						board_calc[i][j] = 'N';
						if (score > bestScore) {
							bestScore = score;
							Row_i = i;
							column_i = j;
						}
					}
				}
			}
			board_calc[((Row_i * 3 + column_i) / 3)][((Row_i * 3 + column_i) % 3)] = 'O';
			board_show[((Row_i * 3 + column_i) / 3)][((Row_i * 3 + column_i) % 3)] = 'O';
			Turn = 2;
		}
		Count_move++;
	}
}

void Human_VS_Human() {
	int postion, Row = 0, column = 0;
	while (Check_Move() == 0 && Count_move != 9) {
		system("CLS");
		Show_Move();
		cout << "Enter Position : ";
		cin >> postion;
		if (board_calc[(postion - 1) / 3][(postion - 1) % 3] == 'N' && postion < 10 && postion >= 1) {
			if (Turn == 1) {
				board_calc[(postion - 1) / 3][(postion - 1) % 3] = 'O';
				board_show[(postion - 1) / 3][(postion - 1) % 3] = 'O';
				Turn = 2;
			}
			else {
				board_calc[(postion - 1) / 3][(postion - 1) % 3] = 'X';
				board_show[(postion - 1) / 3][(postion - 1) % 3] = 'X';
				Turn = 1;
			}
			Count_move++;
		}
	}
}

void main(){
	int choise;
	system("CLS");
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 10;
	cfi.dwFontSize.X = 10;
	cfi.dwFontSize.Y = 24;
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	console_color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console_color, 10);
	cout << "inter ";
	SetConsoleTextAttribute(console_color, 12);
	cout << 0;
	SetConsoleTextAttribute(console_color, 10);
	cout << " for play with AI\ninter ";
	SetConsoleTextAttribute(console_color, 12);
	cout << 1;
	SetConsoleTextAttribute(console_color, 10);
	cout << " for play with your friend\n";
	SetConsoleTextAttribute(console_color, 9);
	cout << "your choise : ";
	SetConsoleTextAttribute(console_color, 12);
	cin >> choise;
	if (choise == 0)
		AI_VS_Human();
	if (choise == 1)
		Human_VS_Human();
	if(choise != 1 && choise != 0)
		main();
	system("CLS");
	Show_Move();
	cout << "Result: ";
	SetConsoleTextAttribute(console_color, 12);
	result = (Turn == 1) ? "X win :)\n" : "O win :)\n";
	if (Check_Move() == 0 && Count_move == 9)
		cout << "Draw";
	else
		cout << result;
}