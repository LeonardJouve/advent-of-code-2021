#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getFileContent(char **content, char path[], int lineNumber,
                    int lineLength) {
  FILE *fp;
  fp = fopen(path, "r");
  if (fp == NULL) {
    fprintf(stderr, "Failed to open file: %s\n", path);
    return;
  }
  for (int i = 0; i < lineNumber; i++) {
    char line[lineLength];
    fgets(line, lineLength, fp);
    if (*line == '\n') {
      i--;
      continue;
    }
    strcpy(content[i], line);
  }
  fclose(fp);
}
