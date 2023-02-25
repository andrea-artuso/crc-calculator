/*
	Author:			Andrea Artuso
	Website:		https://www.andrea-artuso.dev/
	Github:			https://www.github.com/andrea-artuso

	Last update:	26/02/2023
*/

#include <stdlib.h>
#include <string.h>

#define CHAR_TO_INT 48

/*
*	Functions that calculates the CRC check sequence of a binary string
*
*	@param Binary sequence, Polynomial binary sequence
*	@return Returns a pointer to the first char of the calculated CRC sequence
*/
char* encodeCRC(char* sequence, char* polynomial) {
	int i, j;
	int grade = strlen(polynomial) - 1, sequence_length = strlen(sequence);
	char* seq = (char*)malloc(sequence_length);
	char* check_sequence = (char*)malloc(grade + 1);

	strcpy(seq, sequence);
	seq = (char*)realloc(seq, sizeof(seq) + grade + 1);
	if (seq == NULL)
		exit(-1);

	for (i = sequence_length; i < sequence_length + grade; i++) {
		seq[i] = '0';
	}
	seq[i] = '\0';
	sequence_length = strlen(seq);

	i = 0;
	while (sequence_length - i >= grade) {
		for (j = 0; j < (grade + 1) && (j + i) < sequence_length; j++) {
			int xor_res = (seq[j + i] - CHAR_TO_INT) ^ (polynomial[j] - CHAR_TO_INT);
			seq[j + i] = xor_res + CHAR_TO_INT;
		}
		if ((j + i) >= sequence_length)
			break;

		for (j = 0; j <= grade; j++) {
			if (seq[i] == '0')
				i++;
		}
	}

	check_sequence[grade] = '\0';
	for (i = 0; i < grade; i++) {
		check_sequence[grade - i - 1] = seq[sequence_length - i - 1];
	}

	return check_sequence;
}
