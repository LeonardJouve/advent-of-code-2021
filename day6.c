#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int LINE_NUMBER = 1;
const int LINE_LENGTH = 599;
// const int LINE_LENGTH = 9;
const int DAY_NUMBER_FIRST_PART = 80;
const int DAY_NUMBER_SECOND_PART = 256;

int *getLanterFishs(int *lanternFishsSize, char initialState[LINE_LENGTH + 1]) {
  *lanternFishsSize = *lanternFishsSize + 1;
  int *lanterFishs = malloc(sizeof(int));
  lanterFishs[0] = atoi(strtok(initialState, ","));
  int currentFish;
  while ((currentFish = atoi(strtok(NULL, ",")))) {
    *lanternFishsSize = *lanternFishsSize + 1;
    lanterFishs = realloc(lanterFishs, *lanternFishsSize * sizeof(int));
    lanterFishs[*lanternFishsSize - 1] = currentFish;
  }
  return lanterFishs;
}

struct LanterFishsTableEntry {
  int timer;
  uint64_t amount;
};

struct LanterFishsTableEntry *
getLanterFishsTable(int *lanternFishsTableSize, char initialState[LINE_LENGTH],
                    uint64_t *lanternFishsTableAmount) {
  *lanternFishsTableSize = *lanternFishsTableSize + 1;
  struct LanterFishsTableEntry *lanternFishsTable =
      malloc(sizeof(struct LanterFishsTableEntry));
  int currentTimer = atoi(strtok(initialState, ","));
  struct LanterFishsTableEntry lanternFishsEntry = {
      currentTimer,
      1,
  };
  *lanternFishsTableAmount = *lanternFishsTableAmount + 1;
  lanternFishsTable[0] = lanternFishsEntry;
  while ((currentTimer = atoi(strtok(NULL, ",")))) {
    bool tableEntryExists = false;
    int tableEntryIndex;
    for (int i = 0; i < *lanternFishsTableSize; i++) {
      if (lanternFishsTable[i].timer == currentTimer) {
        tableEntryExists = true;
        tableEntryIndex = i;
        break;
      }
    }
    if (tableEntryExists == false) {
      *lanternFishsTableSize = *lanternFishsTableSize + 1;
      lanternFishsTable =
          realloc(lanternFishsTable, *lanternFishsTableSize *
                                         sizeof(struct LanterFishsTableEntry));
      lanternFishsEntry.amount = 0;
      lanternFishsEntry.timer = currentTimer;
      tableEntryIndex = *lanternFishsTableSize - 1;
      lanternFishsTable[tableEntryIndex] = lanternFishsEntry;
    }
    *lanternFishsTableAmount = *lanternFishsTableAmount + 1;
    lanternFishsTable[tableEntryIndex].amount++;
  }
  return lanternFishsTable;
}

void firstPart(int *lanterFishs, int *lanternFishsSize) {
  for (int i = 0; i < DAY_NUMBER_FIRST_PART; i++) {
    int currentLanterFishsSize = *lanternFishsSize;
    for (int j = 0; j < currentLanterFishsSize; j++) {
      if (lanterFishs[j] == 0) {
        lanterFishs[j] = 6;
        *lanternFishsSize = *lanternFishsSize + 1;
        lanterFishs = realloc(lanterFishs, *lanternFishsSize * sizeof(int));
        lanterFishs[*lanternFishsSize - 1] = 8;
        continue;
      }
      lanterFishs[j]--;
    }
  }
  printf("Part 1: there are %i lantern fishs\n", *lanternFishsSize);
}

void secondPart(struct LanterFishsTableEntry *lanternFishsTable,
                int lanternFishsTableSize, uint64_t lanternFishsTableAmount) {
  for (int i = 0; i < DAY_NUMBER_SECOND_PART; i++) {
    int currentLanterFishsTableSize = lanternFishsTableSize;
    int sixDayTimerEntryAmount = 0;
    int sixDayTimerEntryToDeleteIndex[2];
    for (int j = 0; j < currentLanterFishsTableSize; j++) {
      if (lanternFishsTable[j].timer == 0) {
        sixDayTimerEntryAmount++;
        sixDayTimerEntryToDeleteIndex[0] = j;
        lanternFishsTable[j].timer = 6;
        lanternFishsTableSize++;
        lanternFishsTable = realloc(lanternFishsTable,
                                    lanternFishsTableSize *
                                        sizeof(struct LanterFishsTableEntry));
        struct LanterFishsTableEntry lanternFishsEntry = {
            8,
            lanternFishsTable[j].amount,
        };
        lanternFishsTable[lanternFishsTableSize - 1] = lanternFishsEntry;
        lanternFishsTableAmount += lanternFishsTable[j].amount;
        printf("increase %lli | %lli\n", lanternFishsTableAmount,
               lanternFishsTable[j].amount);
        continue;
      }
      lanternFishsTable[j].timer--;
      if (lanternFishsTable[j].timer == 6) {
        sixDayTimerEntryAmount++;
        sixDayTimerEntryToDeleteIndex[1] = j;
      }
    }
    if (sixDayTimerEntryAmount == 2) {
      uint64_t sixDayTimerEntryToDeleteAmount =
          lanternFishsTable[sixDayTimerEntryToDeleteIndex[0]].amount;
      lanternFishsTable[sixDayTimerEntryToDeleteIndex[0]] =
          lanternFishsTable[lanternFishsTableSize - 1];
      lanternFishsTableSize--;
      lanternFishsTable =
          realloc(lanternFishsTable,
                  lanternFishsTableSize * sizeof(struct LanterFishsTableEntry));
      lanternFishsTable[sixDayTimerEntryToDeleteIndex[1]].amount +=
          sixDayTimerEntryToDeleteAmount;
    }
  }
  printf("Part 2: there are %lli lantern fishs\n", lanternFishsTableAmount);
}

int main() {
  FILE *fp = fopen("inputs/day6.txt", "r");
  char initialState[LINE_LENGTH + 1];
  fgets(initialState, LINE_LENGTH + 1, fp);
  fclose(fp);

  int lanternFishsSize = 0;
  char lanternFishsList[LINE_LENGTH];
  strcpy(lanternFishsList, initialState);
  int *lanternFishs = getLanterFishs(&lanternFishsSize, lanternFishsList);
  firstPart(lanternFishs, &lanternFishsSize);

  int lanternFishsTableSize = 0;
  uint64_t lanternFishsTableAmount = 0;
  strcpy(lanternFishsList, initialState);
  struct LanterFishsTableEntry *lanterFishsTable = getLanterFishsTable(
      &lanternFishsTableSize, initialState, &lanternFishsTableAmount);
  secondPart(lanterFishsTable, lanternFishsTableSize, lanternFishsTableAmount);

  free(lanternFishs);
  free(lanterFishsTable);
  return 0;
}
