#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	int x = 0, y=0, amt, aim=0;
	char dir[8];
	if (PROBLEM == 2)	
		goto problem2;

// -------------------------- PART 1 -------------------------------
	while (fscanf(fp, "%s %d", &dir, &amt) == 2) {
		if (!strcmp(dir, "forward"))
			x += amt;
		else if (!strcmp(dir, "down"))
			y += amt;
		else if (!strcmp(dir, "up"))
			y -= amt;
		else
			printf("error\n");
	}
	printf("The result is x: %d, y: %d, x*y = %d\n", x, y, x*y);
	return 0;

// -------------------------- PART 2 -------------------------------
problem2:
	while (fscanf(fp, "%s %d", &dir, &amt) == 2) {
		if (!strcmp(dir, "forward")) {
			y += amt*aim;
			x += amt;
		}
		else if (!strcmp(dir, "down"))
			aim += amt;
		else if (!strcmp(dir, "up"))
			aim -= amt;
		else
			printf("error\n");
	}
	printf("The result is x: %d, y: %d, x*y = %d\n", x, y, x*y);
	return 0;

}
