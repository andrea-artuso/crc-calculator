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
*	Functions that checks the CRC check sequence of a binary string
*
*	@param Binary sequence, Polynomial binary sequence, Binary check sequence
*	@return Returns an integer (0 = valid CRC , 1 = invalid CRC)
*/
int decodeCRC(char* sequence, char* polynomial, char* check_sequence) {
	int i, j, return_code = 0;
	int sequence_length = strlen(sequence), grade = strlen(check_sequence);
	char* seq = (char*)malloc(sequence_length);
	if (seq == NULL)
		exit(-1);

	strcpy(seq, sequence);
	strcat(seq, check_sequence);

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

	for (i = 0; i < grade; i++) {
		return_code += seq[sequence_length - i - 1] - CHAR_TO_INT;
	}

	return return_code;
}