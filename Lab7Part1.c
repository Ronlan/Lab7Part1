#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void initialBoard(char board[][26], int n);
void printBoard(char board[][26], int n);
bool positionInBounds(int n, char row, char col);
bool checkLegalInDirection(char board[][26], int n, char row, char col, char colour, int deltaRow, int deltaCol);
char opponent(char colour);
bool checkAvailableMove(char board[][26], int n, char colour);
void humanMove(char board[][26], int n, char colour );
bool checkValidMove(char board[][26], int n, char row, char col, char colour);
void flip(char board[][26], int n, char colour, char row, char col);
void checkWinner(char board[][26], int n);
void compMove(char board[][26], int n, char comp);
int checkScore(char board[][26], int n, char comp, int row, int col, int deltaRow, int deltaCol);
int main()
{
	int n;
	char board[26][26],comp, human;
	printf("Enter the board dimension: ");
	scanf("%d",&n);
	printf("Computer plays (B/W) : ");
	scanf(" %c", &comp);
	human = opponent(comp);
	initialBoard(board,n);
	if (comp == 'W')
		humanMove(board, n, human);
	do{
		if (!(checkAvailableMove(board, n, comp)))
		{
			printf("%c player has no valid move.\n", comp);
			humanMove(board, n, human);
		}
		else if (!(checkAvailableMove(board, n, human)))
		{
			printf("%c player has no valid move.\n", human);
			compMove(board, n, comp);
		}
		if ((checkAvailableMove(board, n, human)) && (checkAvailableMove(board, n, comp))){
			compMove(board,n,comp);
		}
		if ((checkAvailableMove(board, n, human)) && (checkAvailableMove(board, n, comp))){
			humanMove(board,n,human);
		}
	}while ((checkAvailableMove(board, n, comp)) || (checkAvailableMove(board, n, human)));
	checkWinner(board, n);
	return 0;
}

void initialBoard(char board[][26], int n){
	printf("  ");
	for (int i = 0; i < n; i++)
		printf("%c", 'a'+ i);
	printf("\n");
	for (int j = 0; j<n; j++){
		for (int k = 0; k < n; k++){
			board[j][k] = 'U';
			if (k == 0)
				printf("%c ", 'a'+ j );
			else if ((j == n/2) && (k == n/2))
				board[j][k] = 'W';
			else if ((j == n/2-1) && (k == n/2-1))
				board[j][k] = 'W';
			else if ((j == n/2) && (k == n/2-1))
				board[j][k] = 'B';
			else if((j == n/2-1) && (k == n/2))
				board[j][k] = 'B';
			printf("%c",board[j][k]);
		}
		printf("\n");
	}
}

bool positionInBounds(int n, char row, char col){
	if ((row - 'a'>= 0) &&(row-'a'<n) &&(col-'a'>=0)&&(col-'a'<n))
		return true;
	return false;
}

char opponent( char colour){
	if (colour =='B') return 'W';
	else if (colour =='W') return 'B';
}

void printBoard(char board[][26], int n){
	printf("  ");
	for (int i = 0; i < n; i++)
		printf("%c", 'a'+ i);
	printf("\n");
	for (int i = 0; i<n; i++){
		for (int j = 0; j<n; j++){
			if (j == 0)
				printf("%c ", 'a'+ i);
			printf("%c", board[i][j]);
		}
		printf("\n");
	}
}

bool checkLegalInDirection (char board[][26], int n, char row, char col, char colour, int deltaRow, int deltaCol){
	if (positionInBounds(n, row, col)){
		int r = (row- 'a')+deltaRow;
		int c = (col- 'a')+deltaCol;
		int count = 0;
		if (board[r][c] == colour)
			return false;
		else if ((deltaRow ==0) && (deltaCol == 0 ))
			return false;
		while (positionInBounds (n, r+'a',c+'a') && board [r][c] == opponent(colour)){
			count++;
			r = r+deltaRow;
			c = c+deltaCol;
		}
		if (!(positionInBounds(n,r+'a',c+'a')))
			return false;
		else if (board[r][c] == 'U')//if the one is 'U'
			return false;
		else if ((count > 0) && (board[r][c] == colour))
			return true;
		else if (board[r][c] == opponent(colour))
			return false; 
		else
			return false;
		}
		else 
			return false;
}

bool checkAvailableMove(char board[][26], int n, char colour){
	bool mid = false;
	for (int i = 0; i <n; i++){
		for (int j = 0; j<n;j++){
			for (int deltaRow =-1;deltaRow <=1; deltaRow++){
				for (int deltaCol = -1; deltaCol <=1; deltaCol++){
					if (checkLegalInDirection(board, n, 'a'+i, 'a'+j, colour, deltaRow, deltaCol))
						mid = true;
				}
			}
		}
	}
	return mid;
}
void humanMove(char board[][26], int n, char human){
	char row, col;
	printf("Enter move for colour %c (RowCol): ", human);
	scanf(" %c %c", &row, &col);
	if (!(checkValidMove(board, n, row, col, human))){
		printf("Invalid move.\n%c player wins.\n", opponent(human));
		exit(0);
	}else
		flip(board, n, human, row, col);
		printBoard(board, n);
}

bool checkValidMove(char board[][26], int n, char row, char col, char colour){
	bool test = false;
	if (board[row-'a'][col-'a'] != 'U')
		return test; 
	for (int deltaRow =-1;deltaRow <=1; deltaRow++){
		for (int deltaCol = -1; deltaCol <=1; deltaCol++){
			if (checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol)){
				test = true;
			}
		}
	}
	return test;
}

void flip(char board[][26], int n, char colour, char row, char col){
	for (int deltaRow =-1;deltaRow <=1; deltaRow++){
		for (int deltaCol = -1; deltaCol <=1; deltaCol++){
			if (checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol)){
				int r = (row- 'a')+deltaRow;
				int c = (col- 'a')+deltaCol;
				board[row - 'a'][col - 'a'] = colour;
				while (board[r][c] == opponent(colour)){
					board[r][c] = colour;
					r +=deltaRow;
					c +=deltaCol;
				}
			}
		}
	}
}

void checkWinner(char board[][26], int n){
	int cWhite = 0, cBlack = 0 ;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			if (board[i][j] == 'W')
				cWhite++;
			else if (board[i][j] == 'B')
				cBlack++;
		}
	}
	if (cWhite > cBlack)
		printf("W player wins.\n");
	else if (cBlack > cWhite)
		printf("B player wins.\n");
	else 
		printf("Draw!\n");
}

void compMove(char board[][26], int n, char comp){
	printf("Computer places %c at ", comp);
	int bestScore = 0, score1 = 0;
	int hRow, hCol;
	for (int i = 0; i <n; i++){
		for (int j = 0; j<n;j++){
			if (checkValidMove(board, n, 'a'+i, 'a'+j, comp)){
				for (int deltaRow =-1;deltaRow <=1; deltaRow++){
					for (int deltaCol = -1; deltaCol <=1; deltaCol++){
						if (checkLegalInDirection(board, n, 'a'+i, 'a'+j, comp, deltaRow, deltaCol)){
							score1 += checkScore(board, n, comp, i, j, deltaRow, deltaCol);
						}
					}
				}
				
				if (score1 > bestScore){
					bestScore = score1;
					hRow = i;
					hCol = j;
				}
			}
			score1=0;
		}
	}
	printf("%c%c.\n", 'a'+hRow, 'a'+hCol);
	flip(board, n, comp, 'a'+hRow, 'a'+hCol);
	printBoard(board, n);
	
}
int checkScore(char board[][26], int n, char comp, int row, int col, int deltaRow, int deltaCol){
	int count = 0;
	int r = row + deltaRow;
	int c = col+ deltaCol;
	while (board[r][c] == opponent(comp)){
		r +=deltaRow;
		c +=deltaCol;
		count ++;
	}
	return count;
}