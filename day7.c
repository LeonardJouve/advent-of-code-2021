#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int LINE_LENGTH = 3873;

int *getCrabList(char crabInput[LINE_LENGTH + 1], int *crabLength,
                 int *crabMax) {
  *crabLength = *crabLength + 1;
  int *crabList = malloc(sizeof(int));
  char *currentCrabString = strtok(crabInput, ",");
  int currentCrab = atoi(currentCrabString);
  *crabMax = currentCrab;
  crabList[0] = currentCrab;
  while ((currentCrabString = strtok(NULL, ","))) {
    *crabLength = *crabLength + 1;
    crabList = realloc(crabList, *crabLength * sizeof(int));
    currentCrab = atoi(currentCrabString);
    if (currentCrab > *crabMax) {
      *crabMax = currentCrab;
    }
    crabList[*crabLength - 1] = currentCrab;
  }
  return crabList;
}

void firstPart(int *crabList, int crabLength, int crabMax) {
  uint64_t smallestFuelCost = 0;
  for (int i = 0; i < crabMax; i++) {
    uint64_t currentFuelCost = 0;
    for (int j = 0; j < crabLength; j++) {
      currentFuelCost += abs(crabList[j] - i);
    }
    if (currentFuelCost < smallestFuelCost || smallestFuelCost == 0) {
      smallestFuelCost = currentFuelCost;
    }
  }
  printf("Part 1: the smallest fuel cost is %lli\n", smallestFuelCost);
}

void secondPart(int *crabList, int crabLength, int crabMax) {
  uint64_t smallestFuelCost = 0;
  for (int i = 0; i < crabMax; i++) {
    uint64_t currentFuelCost = 0;
    for (int j = 0; j < crabLength; j++) {
      int currentCrabFuelCost = 0;
      for (int k = 1; k < abs(crabList[j] - i) + 1; k++) {
        currentCrabFuelCost += k;
      }
      currentFuelCost += currentCrabFuelCost;
    }
    if (currentFuelCost < smallestFuelCost || smallestFuelCost == 0) {
      smallestFuelCost = currentFuelCost;
    }
  }
  printf("Part 2: the smallest fuel cost is %lli\n", smallestFuelCost);
}

int main() {
  FILE *fp = fopen("inputs/day7.txt", "r");
  char input[LINE_LENGTH + 1];
  fgets(input, LINE_LENGTH + 1, fp);
  int crabLength = 0;
  int crabMax;
  char crabInput[LINE_LENGTH + 1];
  strcpy(crabInput, input);
  int *crabList = getCrabList(crabInput, &crabLength, &crabMax);
  firstPart(crabList, crabLength, crabMax);
  secondPart(crabList, crabLength, crabMax);
  free(crabList);
  return 0;
}
