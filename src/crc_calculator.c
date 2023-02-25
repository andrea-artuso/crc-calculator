/*
	Author:		Andrea Artuso
	Website:	https://www.andrea-artuso.dev/
	Github:		https://www.github.com/andrea-artuso

	Last update:	26/02/2023
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "./header/decode_crc.h"
#include "./header/encode_crc.h"

int verify_binary_string(char* str);

int main(void) {
	char tmp[BUFSIZ];
	char* bin_sequence, * polynomial, * check_sequence;
	int bin_sequence_length, polynomial_length, check_sequence_length;
	int action, is_sequence_valid;

	do
	{
		printf("\n-- CRC Calculator/Checker --\nOptions:\n");
		printf("\t [0] - Calculate the CRC of a binary sequence\n\t [1] - Verify a CRC with a binary sequence\n\n");
		printf("Enter choice (-1 to quit): ");
		assert(scanf("%d", &action) == 1);

		switch (action)
		{
			case -1:
				printf("Closing...\n");
				break;
			case 0:
				printf(" -- Calculate CRC --\n");

				// Get the binary sequence
				printf("Enter the binary sequence: ");
				assert(scanf("%s", tmp) == 1);

				if (!verify_binary_string(tmp)) {
					printf("Invalid binary sequence.");
					continue;
				}
				bin_sequence_length = strlen(tmp);
				bin_sequence = (char*)malloc(bin_sequence_length);
				if (bin_sequence == NULL) {
					printf("[FATAL] - Error during memory allocation. Terminating...");
					exit(-1);
				}
				strcpy(bin_sequence, tmp);

				// Get the polynomial
				printf("Enter the polynomial: ");
				assert(scanf("%s", tmp) == 1);

				if (!verify_binary_string(tmp)) {
					printf("Invalid binary sequence.");
					continue;
				}
				polynomial_length = strlen(tmp);
				polynomial = (char*)malloc(polynomial_length);
				if (polynomial == NULL) {
					printf("[FATAL] - Error during memory allocation. Terminating...");
					exit(-1);
				}
				strcpy(polynomial, tmp);

				// Calculate crc
				check_sequence = encodeCRC(bin_sequence, polynomial);

				// Print output
				check_sequence_length = strlen(check_sequence);
				printf("\n\nCheck sequence: \t%s\t\t[%d bit(s)]\n", check_sequence, check_sequence_length);
				printf("Complete codeword: \t%s%s\t[%d bits]\n\n", bin_sequence, check_sequence, bin_sequence_length + check_sequence_length);

				break;

			case 1:
				printf(" -- Check CRC --\n");

				// Get the binary sequence
				printf("Enter the binary sequence: ");
				assert(scanf("%s", tmp) == 1);

				if (!verify_binary_string(tmp)) {
					printf("Invalid binary sequence.");
					continue;
				}
				bin_sequence_length = strlen(tmp);
				bin_sequence = (char*)malloc(bin_sequence_length);
				if (bin_sequence == NULL) {
					printf("[FATAL] - Error during memory allocation. Terminating...");
					exit(-1);
				}
				strcpy(bin_sequence, tmp);

				// Get the polynomial
				printf("Enter the polynomial: ");
				assert(scanf("%s", tmp) == 1);

				if (!verify_binary_string(tmp)) {
					printf("Invalid binary sequence.");
					continue;
				}
				polynomial_length = strlen(tmp);
				polynomial = (char*)malloc(polynomial_length);
				if (polynomial == NULL) {
					printf("[FATAL] - Error during memory allocation. Terminating...");
					exit(-1);
				}
				strcpy(polynomial, tmp);

				// Get the CRC sequence
				printf("Enter the CRC sequence: ");
				assert(scanf("%s", tmp) == 1);

				if (!verify_binary_string(tmp)) {
					printf("Invalid binary sequence.");
					continue;
				}
				check_sequence_length = strlen(tmp);
				check_sequence = (char*)malloc(check_sequence_length);
				if (check_sequence == NULL) {
					printf("[FATAL] - Error during memory allocation. Terminating...");
					exit(-1);
				}
				strcpy(check_sequence, tmp);

				// Evaluate input data
				if (check_sequence_length >= polynomial_length) {
					printf("\n[ERROR] - CRC grade is higher than the polynomial grade.\n");
					continue;
				}

				// Check CRC sequence and print output
				if (decodeCRC(bin_sequence, polynomial, check_sequence) == 0) {
					printf("\n[VALID] - The CRC sequence '%s' is valid.\n", check_sequence);
				}
				else {
					printf("\n[INVALID] - The CRC sequence '%s' is not valid.\n", check_sequence);
				}

				break;

			default:
				printf(" -- Undefined choice. Please retry.\n");
				break;
		}
	} while (action != -1);

	return 0;
}


int verify_binary_string(char* str) {
	int i = 0;

	while (str[i] != '\0') {
		if (str[i] != '1' && str[i] != '0')
			return 0;
		i++;
	}

	return 1;
}
