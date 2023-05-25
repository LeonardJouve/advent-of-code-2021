#include "utils/file.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int LINE_NUMBER = 1000;
const int LINE_LENGTH = 12;

void firstPart(char **content) {
  int gammaRate = 0;
  int epsilonRate = 0;
  for (int i = 0; i < LINE_LENGTH; i++) {
    int columnSum = 0;
    for (int j = 0; j < LINE_NUMBER; j++) {
      char currentNumber[2];
      strncpy(currentNumber, &content[j][i], 1);
      columnSum += atoi(currentNumber);
    }
    int gammaValue = round((double)columnSum / LINE_NUMBER);
    int epsilonValue = !(bool)gammaValue;
    gammaRate += (int)gammaValue * pow(2, LINE_LENGTH - 1 - i);
    epsilonRate += (int)epsilonValue * pow(2, LINE_LENGTH - 1 - i);
  }
  printf("Part 1: the power consumption is %i\n", gammaRate * epsilonRate);
}

void secondPart(char **content) {
  int oxygenCriteria[LINE_LENGTH];
  int carbonCriteria[LINE_LENGTH];
  char positiveOxygen[LINE_LENGTH + 1];
  char positiveCarbon[LINE_LENGTH + 1];
  bool positiveOxygenRows[LINE_NUMBER];
  bool positiveCarbonRows[LINE_NUMBER];
  int positiveOxygenAmount = LINE_NUMBER;
  int positiveCarbonAmount = LINE_NUMBER;
  for (int i = 0; i < LINE_LENGTH; i++) {
    int oxygenColumnSum = 0;
    int carbonColumnSum = 0;
    for (int j = 0; j < LINE_NUMBER; j++) {
      char currentCharacter[2];
      strncpy(currentCharacter, &content[j][i], 1);
      int currentNumber = atoi(currentCharacter);
      if (i == 0 || positiveOxygenRows[j] == true) {
        oxygenColumnSum += currentNumber;
      }
      if (i == 0 || positiveCarbonRows[j] == true) {
        carbonColumnSum += currentNumber;
      }
    }
    oxygenCriteria[i] = round((double)oxygenColumnSum / positiveOxygenAmount);
    carbonCriteria[i] =
        !(bool)round((double)carbonColumnSum / positiveCarbonAmount);
    positiveOxygenAmount = 0;
    positiveCarbonAmount = 0;
    for (int j = 0; j < LINE_NUMBER; j++) {
      char currentCharacter[2];
      strncpy(currentCharacter, &content[j][i], 1);
      int currentNumber = atoi(currentCharacter);
      if (currentNumber == oxygenCriteria[i] &&
          (i == 0 || positiveOxygenRows[j] == true)) {
        positiveOxygenRows[j] = true;
        positiveOxygenAmount++;
        strcpy(positiveOxygen, content[j]);
      } else {
        positiveOxygenRows[j] = false;
      }
      if (currentNumber == carbonCriteria[i] &&
          (i == 0 || positiveCarbonRows[j] == true)) {
        positiveCarbonRows[j] = true;
        positiveCarbonAmount++;
        strcpy(positiveCarbon, content[j]);
      } else {
        positiveCarbonRows[j] = false;
      }
    }
  }
  int oxygenRating = 0;
  int carbonRating = 0;
  for (int i = 0; i < LINE_LENGTH; i++) {
    char currentOxygen[2];
    char currentCarbon[2];
    strncpy(currentOxygen, &positiveOxygen[i], 1);
    strncpy(currentCarbon, &positiveCarbon[i], 1);
    oxygenRating += (int)atoi(currentOxygen) * pow(2, LINE_LENGTH - 1 - i);
    carbonRating += (int)atoi(currentCarbon) * pow(2, LINE_LENGTH - 1 - i);
  }
  printf("Part 2: the life support rating is %i\n",
         oxygenRating * carbonRating);
}

int main() {
  char **content = malloc(LINE_NUMBER * sizeof(char *));
  for (int i = 0; i < LINE_NUMBER; i++) {
    content[i] = malloc((LINE_LENGTH + 1) * sizeof(char));
  }
  getFileContent(content, "inputs/day3.txt", LINE_NUMBER, LINE_LENGTH + 1);
  firstPart(content);
  secondPart(content);
  for (int i = 0; i < LINE_NUMBER; i++) {
    free(content[i]);
  }
  free(content);
  return 0;
}
