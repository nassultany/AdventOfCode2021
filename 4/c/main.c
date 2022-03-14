#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PROBLEM 2
#define MAX_DRAWNLINE 10000
#define MAX_DRAWN 10000
#define MAX_BOARDS 500

// nothing to see here..
int num_boards_won;
int boards_won[MAX_BOARDS];

int mark_boards(int boards[MAX_BOARDS][5][5], int num_boards, int mark);
int board_wins(int board[5][5], int row, int col, int last);
int calculate_board(int board[5][5], int last);

int main(int argc, char **argv) {
	if (argc < 2) {
		printf("Invalid number of arguments. Pass in input file name.\n");
		return 1;
	}
	FILE* fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("Could not open file %s\n", argv[1]);
		return 1;
	}

	// read drawn numbers
	char drawn_line[MAX_DRAWNLINE];
	int drawn[MAX_DRAWN];
	int count = 0;
	char seps[] = ",";
	char *token;
	if (fscanf(fp,"%s",drawn_line) != 1)
		return -1;
	
	// parse the numbers
	token = strtok(drawn_line, seps);
	while (token) {
		sscanf(token, "%d", &drawn[count++]);
		token = strtok(NULL, seps);
	}
	
	// read the boards now (each one is 5x5)
	int boards[MAX_BOARDS][5][5];
	int num_boards=0;
	while (num_boards < MAX_BOARDS) {
		for (int row=0; row<5; row++) {
			for (int col=0; col<5; col++) {
				if (fscanf(fp, "%d", &boards[num_boards][row][col]) != 1)
					 goto stop_reading;
			}
		}
		num_boards++;
	}
 stop_reading:
	//printf("Read %d boards.\n", num_boards);
	fclose(fp);

	int result=0;

	if (PROBLEM == 2)
		goto problem2;

// ------------------------ PART 1 -------------------------------
	// draw numbers and fill in boards
	for (int i=0; i<count;i++)
		if (result = mark_boards(boards, num_boards, drawn[i]))
			break;
	printf("Answer is: %d\n", result);
	return 0;

// ------------------------ PART 2 -----------------------------
 problem2:;
 	// draw numbers and fill in boards, until last one wins
	int i=0;
	while (num_boards_won < num_boards) {
		result = mark_boards(boards, num_boards, drawn[i++]);
	}
	printf("Answer is: %d\n", result);
	return 0;
}

int mark_boards(int boards[MAX_BOARDS][5][5], int num_boards, int mark) {
	int result = 0;
	for (int i=0; i<num_boards; i++) {
		if (boards_won[i])
			continue;
		for (int row=0; row<5; row++) {
			for (int col=0; col<5; col++) {
				if (boards[i][row][col] == mark) {
					boards[i][row][col] = -1;
					// check row and col to see if it wins
					if (result = board_wins(&boards[i], row, col, mark)) {
						if (PROBLEM == 1)
							return result;
						num_boards_won++;
						boards_won[i] = 1;
					}
				}
			}
		}
	}
	return result;
}

int board_wins(int board[5][5], int row, int col, int last) {
	int win = 1;
	for (int j=0; j<5; j++)
		if (board[row][j] != -1)
			win = 0;
	if (win)
		return calculate_board(board, last);
	win = 1;
	for (int i=0; i<5; i++)
		if (board[i][col] != -1)
			win = 0;
	if (win)
		return calculate_board(board, last);
	
	return 0;
}

int calculate_board(int board[5][5], int last) {
	int result = 0;
	for (int row=0; row<5; row++)
		for (int col=0; col<5; col++)
			if (board[row][col] != -1)
				result += board[row][col];

	return result*last;
}
