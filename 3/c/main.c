#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN_BINARY 20
#define MAXLEN_ARRAY 1000
#define PROBLEM 2

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
 problem2:;
	// we can define a struct to help us out
  	struct reading {
  	    char value[MAXLEN_BINARY];
  	    int next;
  	};

 	struct reading report[MAXLEN_ARRAY];
	int count = 0;

	// read and count lines
	while(fscanf(fp, "%s", report[count].value) == 1)
		count++;
	 
	// get number of characters in string
	int numchars = 0;
	while(report[0].value[numchars] != '\0')
		numchars++;

 	printf("numchars = %d\n", numchars);
	return 0;
  	char gamstr[MAXLEN_BINARY];
  	for(int j=numchars-1; j>=0; j--) {
  	  int zeros = 0, ones = 0;
  	  for(int i=0; i<count;i++) {
  	    if (report[i][j] == '0')
  	      zeros++;
  	    else
  	      ones++;
  	  }
  	  printf("ones and zeros for [%d] = %d,%d\n", j, ones, zeros);
  	  if (ones == zeros)
  	    gamstr[j] = 'x';
  	  else
  	    gamstr[j] = ones > zeros ? '1' : '0';
  	}
  	printf("gamstr: %s\n", gamstr);
  	int longest_match = 0;
  	char *matchstr = NULL;
  	for(int i = 0; i<count; i++) {
  	  int j;
  	  //for(j=numchars-1;j>=0;j--) {
  	  for(j=0;j<numchars;j++) {
  	    if (gamstr[j] == 'x')
  	      if (report[i][j] != '1')
  	        break;
  	      else
  	        continue;
  	    if (report[i][j] != gamstr[j])
  	      break;
  	  }
  	  printf("Current candidate: %s, match length: %d\n", report[i], j);
  	  matchstr = j > longest_match ? report[i] : matchstr;
  	  longest_match = j > longest_match ? j : longest_match;
  	  printf("matchstr: %s\n", matchstr);
  	}

  	printf("Longest match: %d, str: %s\n", longest_match, matchstr);
	return 0;

}
