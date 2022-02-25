#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN_BINARY 20
#define MAXLEN_ARRAY 1000
#define PROBLEM 1

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
	char report[MAXLEN_ARRAY][MAXLEN_BINARY];
	int count = 0;

	// read and count lines
	while(fscanf(fp, "%s", report[count]) == 1)
		count++;
	 
	// get number of characters in string
	int numchars = 0;
	while(report[0][numchars] != '\0')
		numchars++;

	if (PROBLEM == 2)	
		goto problem2;

// ------------------------ PART 1 -------------------------------
	
	int gamma = 0, epsilon = 0;
	for( int j=numchars-1; j>=0; j--) {
		int zeros = 0,ones = 0;
		for (int i = 0; i < count; i++) {
			if (report[i][j] == '0')
				zeros++;
			else
				ones++;
		}
		if (ones > zeros)
			gamma += (1 << (numchars-(j+1)));
		else
			epsilon += (1 << (numchars-(j+1)));
	}
	printf("Gamma = %d, Epsilon = %d\n", gamma, epsilon);
	printf("Result = %d\n", gamma*epsilon);
	return 0;

// ------------------------ PART 2 -----------------------------
problem2:
	return 0;

}
