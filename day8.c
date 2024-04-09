#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// const int LINE_NUMBER = 200;
const int LINE_LENGTH = 89;
const int DIGIT_SEGMENTS[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
const int DISPLAY_SEGMENT_AMOUNT = 4;

int **getDisplaySegmentLength(char **lines, int lineNumber) {
  int **displaySegmentsLength = malloc(lineNumber * sizeof(int *));
  for (int i = 0; i < lineNumber; i++) {
    displaySegmentsLength[i] = malloc(4 * sizeof(int));
    for (int j = 0; j < 4; j++) {
      displaySegmentsLength[i][j] = strlen();
      printf("\n");
    }
    return displaySegmentsLength;
  }

  int main() {
    FILE *fp = fopen("inputs/day8.txt", "r");
    int lineNumber = 0;
    char **lines = NULL;
    char currentLine[LINE_LENGTH + 1];
    while (fgets(currentLine, LINE_LENGTH + 1, fp)) {
      lineNumber++;
      lines = realloc(lines, lineNumber * sizeof(char *));
      lines[lineNumber - 1] = malloc((strlen(currentLine) + 1) * sizeof(char));
      strcpy(lines[lineNumber - 1], currentLine);
      // printf("%s\n", lines[lineNumber - 1]);
    }
    fclose(fp);

    int **displaySegementLength = getDisplaySegmentLength(lines, lineNumber);

    for (int i = 0; i < lineNumber; i++) {
      printf("%i %i %i %i\n", displaySegementLength[i][0],
             displaySegementLength[i][1], displaySegementLength[i][2],
             displaySegementLength[i][3]);
      free(lines[i]);
      free(displaySegementLength[i]);
    }
    free(lines);
    free(displaySegementLength);
    return 0;
  }
