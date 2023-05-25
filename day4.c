#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int FIRST_LINE_LENGTH = 289;
const int LINE_NUMBER = 500;
const int LINE_LENGTH = 14;
const int BOARD_SIZE = 5;
const int DRAWN_NUMBERS_LENGTH = 100;

enum Direction {
  HORIZONTAL,
  VERTICAL,
};

void getDrawnNumbers(int drawnNumbers[DRAWN_NUMBERS_LENGTH],
                     char firstLine[FIRST_LINE_LENGTH + 1]) {
  drawnNumbers[0] = atoi(strtok(firstLine, ","));
  for (int i = 1; i < DRAWN_NUMBERS_LENGTH; i++) {
    drawnNumbers[i] = atoi(strtok(NULL, ","));
  }
}

void getBoards(
    int boards[LINE_NUMBER / BOARD_SIZE][BOARD_SIZE][BOARD_SIZE],
    int scoreBoardsHorizontal[LINE_NUMBER / BOARD_SIZE][BOARD_SIZE][BOARD_SIZE],
    int scoreBoardsVertical[LINE_NUMBER / BOARD_SIZE][BOARD_SIZE][BOARD_SIZE],
    char content[LINE_NUMBER][LINE_LENGTH + 1]) {
  for (int i = 0; i < LINE_NUMBER / BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      for (int k = 0; k < BOARD_SIZE; k++) {
        int currentNumber;
        if (k == 0) {
          currentNumber = atoi(strtok(content[(i * BOARD_SIZE) + j], " "));
        } else {
          currentNumber = atoi(strtok(NULL, " "));
        }
        boards[i][j][k] = currentNumber;
        scoreBoardsHorizontal[i][j][k] = 0;
        scoreBoardsVertical[i][j][k] = 0;
      }
    }
  }
}

void getScore(int score, int board[BOARD_SIZE][BOARD_SIZE],
              int drawnNumbers[DRAWN_NUMBERS_LENGTH], int drawnNumbersAmount) {
  score = 0;
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      bool isDrawn = false;
      for (int k = 0; k < drawnNumbersAmount; k++) {
        if (drawnNumbers[k] == board[i][j]) {
          isDrawn = true;
          break;
        }
      }
      if (!isDrawn) {
        score += board[i][j];
      }
    }
  }
  score *= drawnNumbers[drawnNumbersAmount - 1];
  printf("The final score is %i\n", score);
}

void firstPart(
    int boards[LINE_NUMBER / BOARD_SIZE][BOARD_SIZE][BOARD_SIZE],
    int scoreBoardsHorizontal[LINE_NUMBER / BOARD_SIZE][BOARD_SIZE][BOARD_SIZE],
    int scoreBoardsVertical[LINE_NUMBER / BOARD_SIZE][BOARD_SIZE][BOARD_SIZE],
    int drawnNumbers[DRAWN_NUMBERS_LENGTH]) {
  int score;
  for (int i = 0; i < DRAWN_NUMBERS_LENGTH; i++) {
    for (int j = 0; j < LINE_NUMBER / BOARD_SIZE; j++) {
      for (int k = 0; k < BOARD_SIZE; k++) {
        for (int l = 0; l < BOARD_SIZE; l++) {
          if (boards[j][k][l] == drawnNumbers[i]) {
            for (int m = 0; m < BOARD_SIZE; m++) {
              scoreBoardsHorizontal[j][m][l]++;
              if (scoreBoardsHorizontal[j][m][l] == BOARD_SIZE) {
                getScore(score, boards[j], drawnNumbers, i + 1);
                return;
              }
              scoreBoardsVertical[j][k][m]++;
              if (scoreBoardsVertical[j][k][m] == BOARD_SIZE) {
                getScore(score, boards[j], drawnNumbers, i + 1);
                return;
              }
            }
          }
        }
      }
    }
  }
}

void secondPart(
    int boards[LINE_NUMBER / BOARD_SIZE][BOARD_SIZE][BOARD_SIZE],
    int scoreBoardsHorizontal[LINE_NUMBER / BOARD_SIZE][BOARD_SIZE][BOARD_SIZE],
    int scoreBoardsVertical[LINE_NUMBER / BOARD_SIZE][BOARD_SIZE][BOARD_SIZE],
    int drawnNumbers[DRAWN_NUMBERS_LENGTH]) {
  int score;
  int undoneBoardsCount = LINE_NUMBER / BOARD_SIZE;
  bool doneBoards[LINE_NUMBER / BOARD_SIZE];
  for (int i = 0; i < LINE_NUMBER / BOARD_SIZE; i++) {
    doneBoards[i] = false;
  }
  for (int i = 0; i < DRAWN_NUMBERS_LENGTH; i++) {
    for (int j = 0; j < LINE_NUMBER / BOARD_SIZE; j++) {
      for (int k = 0; k < BOARD_SIZE; k++) {
        for (int l = 0; l < BOARD_SIZE; l++) {
          if (boards[j][k][l] == drawnNumbers[i]) {
            for (int m = 0; m < BOARD_SIZE; m++) {
              scoreBoardsHorizontal[j][m][l]++;
              scoreBoardsVertical[j][k][m]++;
              if ((scoreBoardsHorizontal[j][m][l] >= BOARD_SIZE ||
                   scoreBoardsVertical[j][k][m] >= BOARD_SIZE) &&
                  doneBoards[j] == false) {
                undoneBoardsCount--;
                doneBoards[j] = true;
                if (undoneBoardsCount == 0) {
                  getScore(score, boards[j], drawnNumbers, i + 1);
                  return;
                }
              }
            }
          }
        }
      }
    }
  }
}

int main() {
  FILE *fp;
  fp = fopen("inputs/day4.txt", "r");
  char firstLine[FIRST_LINE_LENGTH + 1];
  fgets(firstLine, FIRST_LINE_LENGTH + 1, fp);
  char content[LINE_NUMBER][LINE_LENGTH + 1];
  for (int i = 0; i < LINE_NUMBER; i++) {
    fgets(content[i], LINE_LENGTH + 1, fp);
    if (*content[i] == '\n') {
      i--;
    }
  }
  fclose(fp);

  int drawnNumbers[DRAWN_NUMBERS_LENGTH];
  getDrawnNumbers(drawnNumbers, firstLine);
  int boards[LINE_NUMBER / BOARD_SIZE][BOARD_SIZE][BOARD_SIZE];
  int scoreBoardsHorizontal[LINE_NUMBER / BOARD_SIZE][BOARD_SIZE][BOARD_SIZE];
  int scoreBoardsVertical[LINE_NUMBER / BOARD_SIZE][BOARD_SIZE][BOARD_SIZE];

  getBoards(boards, scoreBoardsHorizontal, scoreBoardsVertical, content);
  firstPart(boards, scoreBoardsHorizontal, scoreBoardsVertical, drawnNumbers);

  for (int i = 0; i < LINE_NUMBER / BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      for (int k = 0; k < BOARD_SIZE; k++) {
        scoreBoardsHorizontal[i][j][k] = 0;
        scoreBoardsVertical[i][j][k] = 0;
      }
    }
  }
  secondPart(boards, scoreBoardsHorizontal, scoreBoardsVertical, drawnNumbers);

  return 0;
};
