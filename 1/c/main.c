#include <stdio.h>
#include <stdlib.h>
#define MAX_MEASUREMENTS 2000
#define PROBLEM 2

int main(int argc, char **argv) {
	int first, second, result=0;
	if (argc < 2) {
		printf("Invalid number of arguments. Pass in input file name.\n");
		return 1;
	}
	FILE* fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("Could not open file %s\n", argv[1]);
		return 1;
	}

	if (PROBLEM == 2)
		goto problem2;

// -------------------------- PART 1 -------------------------------
	fscanf(fp, "%d", &first);
	result = 0;
	while (fscanf(fp, "%d", &second) == 1) {
		result += second > first;
		first = second;
	}
	printf("The result is: %d\n", result);
	return 0;

// -------------------------- PART 2 (pass file in cmd line arg) --
problem2:;
	int measurements[MAX_MEASUREMENTS];
	int count = 0;
	while(fscanf(fp, "%d", &measurements[count]) == 1)
		count++;	

	// prefix sums
	int *psums = (int *) malloc((count+1)*sizeof(int));
	psums[0] = 0;
	for(int i = 1; i<=count;i++)
		psums[i] = psums[i-1] + measurements[i-1];
	
	int end = 3;
	int begin = 0;
	first = psums[end] - psums[begin];
	result = 0;
	while (end < count) {
		second = psums[++end] - psums[++begin];
		result += second > first;
		first = second;
	}
	printf("The result is: %d\n", result);
	return 0;	
}
