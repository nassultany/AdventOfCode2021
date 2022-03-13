#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN_BINARY 20
#define MAXLEN_ARRAY 1000
#define PROBLEM 2
// for problem 2
#define OXYGEN 1
#define CO2 2
#define OUT 3
#define UNDEFINED 0

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
	int count = 0;

	if (PROBLEM == 2)
		goto problem2;

// ------------------------ PART 1 -------------------------------

	char report[MAXLEN_ARRAY][MAXLEN_BINARY];

	// read and count lines

	while(fscanf(fp, "%s", report[count]) == 1)
		count++;

	// get number of characters in string
	int numchars = 0;
	while(report[0][numchars] != '\0')
		numchars++;

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
  	    char category;
  	};

 	struct reading report2[MAXLEN_ARRAY];

	// read and count lines
	while(fscanf(fp, "%s", report2[count].value) == 1) {
		report2[count].category = UNDEFINED;
		count++;
	}

	// get number of characters in string
	numchars = 0;
	while(report2[0].value[numchars] != '\0')
		numchars++;


	char ox_result[MAXLEN_BINARY], co2_result[MAXLEN_BINARY]; // store final answer binary strings
	char oxygen_val, co2_val; // used to determine which numbers to keep at each iteration
	int zeros_oxygen, ones_oxygen, zeros_co2, ones_co2; // keep count of digits
	int ox_count, co2_count; // how many matches found for each category at each iteration
	int ox_int=0,co2_int=0;

  	for(int j=0; j<numchars; j++) {
		zeros_oxygen = 0, ones_oxygen = 0, zeros_co2 = 0, ones_co2 = 0; // keep count of digits

  	  	for(int i=0; i<count;i++) {
  	  	  	if (report2[i].category == OXYGEN || report2[i].category == UNDEFINED) {
	  	  		if (report2[i].value[j] == '0')
	  	  			zeros_oxygen++;
  	  	  		else
  	  	  	  		ones_oxygen++;
	  	  	}
			if (report2[i].category == CO2 || report2[i].category == UNDEFINED) {
	  	  		if (report2[i].value[j] == '0')
	  	  			zeros_co2++;
	  	  		else
	  	  			ones_co2++;
	  	  	}
  	  	}

		oxygen_val = zeros_oxygen > ones_oxygen ? '0' : '1';
		co2_val = ones_co2 < zeros_co2 ? '1' : '0';

	  	// now we can go through with this information and filter our list
		ox_count = 0, co2_count = 0;
	  	for (int i=0; i<count; i++) {
			if (report2[i].category == UNDEFINED) {
				report2[i].category = report2[i].value[j] == oxygen_val ? OXYGEN : CO2;
				ox_count = 1, co2_count = 1; // so we don't prematurely exit the search
				continue;
			}

			// now we can perform the filtering, store valid ones, and if the count reaches 0 then we will
			// have our answers (previously) stored in ox_result and co2_result
			if (report2[i].category == OXYGEN) {
				if (report2[i].value[j] == oxygen_val) {
					ox_count++;
					strcpy(ox_result, report2[i].value);
				} else {
					report2[i].category = OUT;
				}
			} else if (report2[i].category == CO2) {
				if (report2[i].value[j] == co2_val) {
					co2_count++;
					strcpy(co2_result, report2[i].value);
				} else {
					report2[i].category = OUT;
				}
			}
	  	}
		// search terminated and result should have been stored previously in [ox,co2]_result
		if (ox_count == 0 && co2_count == 0)
			break;
  	}

	// get the integer values of the result strings
	for( int j=numchars-1; j>=0; j--) {
		ox_int += ((ox_result[j]=='1') << (numchars-(j+1)));
		co2_int += ((co2_result[j]=='1') << (numchars-(j+1)));
	}
	printf("ox_result = %s, co2_result = %s\n", ox_result, co2_result);
	printf("ox_rating*co2_rating = %d\n", ox_int*co2_int);

	return 0;
}
