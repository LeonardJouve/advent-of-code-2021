#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils/file.h"

const int LINE_NUMBER = 1000;
const int LINE_LENGTH = 9;

struct Location {
    int x;
    int z;
    int aim;
};

enum InstructionNames {
    FORWARD,
    DOWN,
    UP,
};

const char INSTRUCTION_NAMES[3][8] = {"forward", "down", "up"};

typedef struct {
    char * instructionName;
    int value;
} Instruction;

void parseInstructions(char **content, Instruction instructions[]) {
    const char delimiter[] = " ";
    for (int i = 0; i < LINE_NUMBER; i++) {
        Instruction instruction = {
            strtok(content[i], delimiter),
            atoi(strtok(NULL, delimiter)),
        };
        instructions[i] = instruction;
    }
}

void firstPart(Instruction instructions[LINE_NUMBER]) {
    struct Location location = {0, 0, 0};
    for (int i = 0; i < LINE_NUMBER; i++) {
        Instruction instruction = instructions[i];
        if (strcmp(instruction.instructionName, INSTRUCTION_NAMES[FORWARD]) == 0) {
            location.x += instruction.value;
            continue;
        }
        if (strcmp(instruction.instructionName, INSTRUCTION_NAMES[DOWN]) == 0) {
            location.z += instruction.value;
            continue;
        }
        if (strcmp(instruction.instructionName, INSTRUCTION_NAMES[UP]) == 0) {
            location.z -= instruction.value;
            continue;
        }
    }
    printf("Part 1: the multiplication result is %i\n", location.x * location.z);
}

void secondPart(Instruction instructions[LINE_NUMBER]) {
    struct Location location = {0, 0, 0};
    for (int i = 0; i < LINE_NUMBER; i++) {
        Instruction instruction = instructions[i];
        if (strcmp(instruction.instructionName, INSTRUCTION_NAMES[FORWARD]) == 0) {
            location.x += instruction.value;
            location.z += location.aim * instruction.value;
            continue;
        }
        if (strcmp(instruction.instructionName, INSTRUCTION_NAMES[DOWN]) == 0) {
            location.aim += instruction.value;
            continue;
        }
        if (strcmp(instruction.instructionName, INSTRUCTION_NAMES[UP]) == 0) {
            location.aim -= instruction.value;
            continue;
        }
    }
    printf("Part 2: the multiplication result is %i\n", location.x * location.z);
}

int main() {
    char **content = malloc(LINE_NUMBER * sizeof(char *));
    for (int i = 0; i < LINE_NUMBER; i++) {
        content[i] = malloc((LINE_LENGTH + 1) * sizeof(char));
    }
    getFileContent(content, "inputs/day2.txt", LINE_NUMBER, LINE_LENGTH + 1);
    Instruction parsedInstructions[LINE_NUMBER];
    parseInstructions(content, parsedInstructions);
    firstPart(parsedInstructions);
    secondPart(parsedInstructions);
    for(int i = 0; i < LINE_NUMBER; i++) {
        free(content[i]);
    }
    free(content);
    return 0;
}