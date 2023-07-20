#include "utils.h"

#define MAX_SCORES 100
#define RECORDS_TO_SHOW 10

struct Record
{
    char player[NAMES_SIZE];
    char game[NAMES_SIZE];
    char score[NAMES_SIZE];
};


int readFile(int *totalRecords, struct Record* records);

void saveFile(char playerName[], char gameName[], int score);

void setPlayerPoints(char gameName[]);

void setGamePoints(char playerName[]);

void setGlobalPoints();