#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

int main() {
	size_t bufsize = 0;
	while (1) {
		printf("Input: ");
		char* input = NULL;
		getline(&input, &bufsize, stdin);
		
		size_t input_len = strlen(input);
		if (input_len <= 0 || input[0] == '\n') break;
		if (input[input_len - 1] == '\n') input[input_len - 1] = '\0';
		
		long long num1, num2;
		char operator;
		char* output = input;

		if (sscanf(input, "%lld%c%lld", &num1, &operator, &num2) == 3) {
                        if (num1 <= 0 || num2 <= 0) {
                                printf("Wrong Input!\n");
                                continue;
                        }
                        if (operator == '+') {
                                long long return_value = syscall(452, num1, num2);
                                printf("Output: %lld\n", return_value);
                        } else if (operator == '-') {
                                long long return_value = syscall(451, num1, num2);
                                printf("Output: %lld\n", return_value);
                        } else {
				printf("Wrong Input!\n");
			}

                } else if (sscanf(input, "%lld", &num1) == 1) {
			if (num1 <= 0) {
				printf("Wrong Input!\n");
				continue;
			}
			int flag = 0;
			char *tmp = input;
			while(*tmp) {
				if (!isdigit(*tmp)) {
					flag = 1;
					printf("Wrong Input!\n");
					break;
				}
				tmp++;
			}
			if (flag) continue;
			long long reverse_value = syscall(450, input, output, input_len);
			if (reverse_value == -1) {
				perror("Error in syscall 450");
			}
			printf("Output: %s\n", output + 1);
		} else {
			printf("Wrong Input!\n");
		}

		free(input);
	}

	return 0;
}
