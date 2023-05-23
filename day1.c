#include <stdio.h>
#include <stdlib.h>
#include "utils/file.h"

const int LINE_NUMBER = 2000;
const int LINE_LENGTH = 4;

void firstPart(char **content) {
    int increaseNumber = 0;
    int previousNumber = -1;
    for (int i = 0; i < LINE_NUMBER; i++) {
        const int currentNumber = atoi(content[i]);
        if (previousNumber != -1 && currentNumber > previousNumber) {
            increaseNumber++;
        }
        previousNumber = currentNumber;
    }
    printf("Part 1: value increased %i times\n", increaseNumber);
}

void secondPart(char **content) {
    int increaseNumber = 0;
    int previousNumber = -1;
    for (int i = 0; i + 2 < LINE_NUMBER; i++) {
        const int currentNumber = atoi(content[i]) + atoi(content[i + 1]) + atoi(content[i + 2]);
        if (previousNumber != -1 && currentNumber > previousNumber) {
            increaseNumber++;
        }
        previousNumber = currentNumber;
    }
    printf("Part 2: value increased %i times\n", increaseNumber);
}

int main() {
    char **content = malloc(LINE_NUMBER * sizeof(char *));
    for (int i = 0; i < LINE_NUMBER; i++) {
        content[i] = malloc((LINE_LENGTH + 1) * sizeof(char));
    }
    getFileContent(content, "inputs/day1.txt", LINE_NUMBER, LINE_LENGTH + 1);
    firstPart(content);
    secondPart(content);
    for (int i = 0; i < LINE_NUMBER; i++) {
        free(content[i]);
    }
    free(content);
    return 0;
}