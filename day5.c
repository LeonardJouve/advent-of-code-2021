#include "utils/file.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int LINE_NUMBER = 500;
const int LINE_LENGTH = 18;
const int GRID_SIZE = 1000;

struct Position {
  int x;
  int y;
};

enum Direction {
  UNKNOWN,
  HORIZONTAL,
  VERTICAL,
  DIAGONAL,
};

struct Instruction {
  struct Position start;
  struct Position end;
  enum Direction direction;
};

void getInstructions(struct Instruction instructions[LINE_NUMBER],
                     char **content) {
  for (int i = 0; i < LINE_NUMBER; i++) {
    int startX, startY, endX, endY;
    sscanf(content[i], "%i,%i -> %i,%i", &startX, &startY, &endX, &endY);
    struct Position start = {
        startX,
        startY,
    };
    struct Position end = {
        endX,
        endY,
    };
    enum Direction direction = UNKNOWN;
    if (start.x == end.x) {
      direction = VERTICAL;
    } else if (start.y == end.y) {
      direction = HORIZONTAL;
    } else if (abs(start.x - end.x) == abs(start.y - end.y)) {
      direction = DIAGONAL;
    }
    struct Instruction instruction = {
        start,
        end,
        direction,
    };
    instructions[i] = instruction;
  }
}

int min(int a, int b) { return a - b > 0 ? b : a; }

int max(int a, int b) { return a - b > 0 ? a : b; }

void firstPart(struct Instruction instructions[LINE_NUMBER], int **grid) {
  int overlap = 0;
  for (int i = 0; i < LINE_NUMBER; i++) {
    struct Instruction instruction = instructions[i];
    if (instruction.direction == HORIZONTAL) {
      int minX = min(instruction.start.x, instruction.end.x);
      int maxX = max(instruction.start.x, instruction.end.x);
      for (int j = 0; j < maxX - minX + 1; j++) {
        grid[minX + j][instruction.start.y]++;
        if (grid[minX + j][instruction.start.y] == 2) {
          overlap++;
        }
      }
    }
    if (instruction.direction == VERTICAL) {
      int minY = min(instruction.start.y, instruction.end.y);
      int maxY = max(instruction.start.y, instruction.end.y);
      for (int j = 0; j < maxY - minY + 1; j++) {
        grid[instruction.start.x][minY + j]++;
        if (grid[instruction.start.x][minY + j] == 2) {
          overlap++;
        }
      }
    }
  }
  printf("Part 1: the number of overlap is %i\n", overlap);
}

void secondPart(struct Instruction instructions[LINE_NUMBER], int **grid) {
  int overlap = 0;
  for (int i = 0; i < LINE_NUMBER; i++) {
    struct Instruction instruction = instructions[i];
    if (instruction.direction == HORIZONTAL) {
      int minX = min(instruction.start.x, instruction.end.x);
      int maxX = max(instruction.start.x, instruction.end.x);
      for (int j = 0; j < maxX - minX + 1; j++) {
        grid[minX + j][instruction.start.y]++;
        if (grid[minX + j][instruction.start.y] == 2) {
          overlap++;
        }
      }
    } else if (instruction.direction == VERTICAL) {
      int minY = min(instruction.start.y, instruction.end.y);
      int maxY = max(instruction.start.y, instruction.end.y);
      for (int j = 0; j < maxY - minY + 1; j++) {
        grid[instruction.start.x][minY + j]++;
        if (grid[instruction.start.x][minY + j] == 2) {
          overlap++;
        }
      }
    } else if (instruction.direction == DIAGONAL) {
      struct Position startPosition = instruction.start;
      struct Position endPosition = instruction.end;
      int incrementerX;
      if (startPosition.x < endPosition.x) {
        // vector goes left to right
        incrementerX = 1;
      } else {
        // vector goes right to left
        incrementerX = -1;
      }
      int incrementerY;
      if (startPosition.y < endPosition.y) {
        // vector goes top to bottom
        incrementerY = 1;
      } else {
        // vector goes bottom to top
        incrementerY = -1;
      }
      for (int j = 0; j < abs(endPosition.x - startPosition.x) + 1; j++) {
        grid[startPosition.x + (incrementerX * j)]
            [startPosition.y + (incrementerY * j)]++;
        if (grid[startPosition.x + (incrementerX * j)]
                [startPosition.y + (incrementerY * j)] == 2) {
          overlap++;
        }
      }
    }
  }
  printf("Part 2: the number of overlap is %i", overlap);
}

int main() {
  char **content = malloc(LINE_NUMBER * sizeof(char *));
  for (int i = 0; i < LINE_NUMBER; i++) {
    content[i] = malloc((LINE_LENGTH + 1) * sizeof(char));
  }
  getFileContent(content, "inputs/day5.txt", LINE_NUMBER, LINE_LENGTH + 1);

  int **grid = malloc(GRID_SIZE * sizeof(int *));
  for (int i = 0; i < GRID_SIZE; i++) {
    grid[i] = malloc(GRID_SIZE * sizeof(int));
  }
  for (int i = 0; i < GRID_SIZE; i++) {
    for (int j = 0; j < GRID_SIZE; j++) {
      grid[i][j] = 0;
    }
  }

  struct Instruction instructions[LINE_NUMBER];
  getInstructions(instructions, content);

  firstPart(instructions, grid);

  for (int i = 0; i < GRID_SIZE; i++) {
    for (int j = 0; j < GRID_SIZE; j++) {
      grid[i][j] = 0;
    }
  }
  secondPart(instructions, grid);

  for (int i = 0; i < LINE_NUMBER; i++) {
    free(content[i]);
  }
  for (int i = 0; i < GRID_SIZE; i++) {
    free(grid[i]);
  }
  free(content);
  free(grid);
  return 0;
}
