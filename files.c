#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include "files.h"
#include "utils.h"

#define FOLDER "leaderboard"

void sortRecords(int totalRecords, struct Record records[]);
void setGameNameToDisplay(char* nameToDisplay, char* gameName);
void noResults();

int readFile(int *totalRecords, struct Record* records) {
    int size = 0;
    FILE* myFile;
    char path[100] = FOLDER;

    strcat(path, "/records.txt");

    myFile = fopen(path, "r");

    if (myFile == NULL)
    {
        printf("Error : Failed to open file - \n");
        exit(1);
    }

    while(fscanf(myFile, "%s %s %s", records[size].player, records[size].game, records[size].score) != EOF) {
        size++;
    };

    fclose(myFile);
    
    *totalRecords = size;
    
    return 0;
}

void saveFile(char playerName[], char gameName[], int score) {
    FILE *myFile;
    char path[100] = FOLDER;

    strcat(path, "/records.txt");

    mkdir(FOLDER, 0777);

    myFile = fopen(path, "a");

    if(myFile == NULL) {
        perror("Not possible to open file");
        exit(1);
    }

    char* lineToWrite;

    if (ftell(myFile) == 0) {
        lineToWrite = "%s %s %d";
    } else {
        lineToWrite = "\n%s %s %d";
    }

    fprintf(myFile, lineToWrite, playerName, gameName, score);

    fclose(myFile);
}

void setPlayerPoints(char playerName[]) {
    struct Record* recordsToSet = malloc(100 * sizeof(struct Record));
    struct Record* recordsToSend = malloc(100 * sizeof(struct Record));;

    int totalRecords;

    readFile(&totalRecords, recordsToSet);

    int recordsIndex = 0;

    for(int i = 0; i < totalRecords; i++) {
        if (strcmp(recordsToSet[i].player, playerName) == 0) {
            recordsToSend[recordsIndex] = recordsToSet[i];
            recordsIndex++;
        }
    }

    sortRecords(totalRecords, recordsToSend);

    for(int i = 0; i < RECORDS_TO_SHOW; i++) {
        if (recordsToSend[i].game[0] == '\0') {
            if (i == 0) {
                noResults();
            }
            break;
        }

        char nameToDisplay[30];

        setGameNameToDisplay(nameToDisplay, recordsToSend[i].game);

        printf("%s  ->  %s\n", nameToDisplay, recordsToSend[i].score);
    }

    free(recordsToSet);
    free(recordsToSend);
}

void setGamePoints(char gameName[]) {
    struct Record* recordsToSet = malloc(100 * sizeof(struct Record));
    struct Record* recordsToSend = malloc(100 * sizeof(struct Record));

    int totalRecords;

    readFile(&totalRecords, recordsToSet);

    int recordsIndex = 0;

    for(int i = 0; i < totalRecords; i++) {
        if (strcmp(recordsToSet[i].game, gameName) == 0) {
            recordsToSend[recordsIndex] = recordsToSet[i];
            recordsIndex++;
        }
    }

    sortRecords(totalRecords, recordsToSend);

    for(int i = 0; i < RECORDS_TO_SHOW; i++) {
        if (recordsToSend[i].player[0] == '\0') {
            if (i == 0) {
                noResults();
            }
            break;
        }

        printf("%s  ->  %s\n", recordsToSend[i].player, recordsToSend[i].score);
    }

    free(recordsToSet);
    free(recordsToSend);
}

void setGlobalPoints() {
    struct Record* records = malloc(100 * sizeof(struct Record));

    int totalRecords;

    readFile(&totalRecords, records);

    sortRecords(totalRecords, records);

    for(int i = 0; i < RECORDS_TO_SHOW; i++) {
        if (records[i].player[0] == '\0') {
            if (i == 0) {
                noResults();
            }
            break;
        }

        char nameToDisplay[30];

        setGameNameToDisplay(nameToDisplay, records[i].game);
        printf("%s  ->  %s  ->  %s\n", records[i].player, nameToDisplay, records[i].score);
    }
}

void sortRecords(int totalRecords, struct Record* records) {
    for (int i = 0; i < totalRecords; i++) {
        int prevScore = atoi(records[i].score);
        for (int j = i + 1; j < totalRecords; j++) {
            
            int nextScore = atoi(records[j].score);

            if (nextScore > prevScore) {
                struct Record tmp = records[i];
                records[i] = records[j];
                records[j] = tmp;
            }
        }
    }
}

void setGameNameToDisplay(char* nameToDisplay, char* gameName) {
    if (strcmp(gameName, BLACKJACK) == 0) {
        strcpy(nameToDisplay, "Vinte e um");
    } else if (strcmp(gameName, TIC_TAC_TOE) == 0) {
        strcpy(nameToDisplay, "Jogo do galo");
    } else if (strcmp(gameName, GUESS_NUMBER) == 0) {
        strcpy(nameToDisplay, "Adivinha o numero");
    } else if (strcmp(gameName, GUESS_CARD) == 0) {
        strcpy(nameToDisplay, "Adivinha a carta");
    }else if (strcmp(gameName, CONNECTED4) == 0) {
        strcpy(nameToDisplay, "Quatro em linha");
    } else {
        strcpy(nameToDisplay, gameName);
    }
}

void noResults() {
    printf("Sem resultados para mostrar");
}