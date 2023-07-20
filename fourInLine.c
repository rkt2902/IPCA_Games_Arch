#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "games.h"
#include "files.h"
#include "utils.h"

#define ROWS 6
#define COLUMS 7
#define FOUR 4

#define HEADER "  1   2   3   4   5   6   7  "
#define SPLITTER "|---|---|---|---|---|---|---|"
#define COMPUTER_NAME "--"

#define DISK1 'X'
#define DISK2 'O'

char scores[ROWS][COLUMS];
int columToWin[COLUMS];
int isComputer;
struct Player
{
    char name[15];
    char disk;
    int score;
};

void boardC4();
void play(struct Player* currentPlayer);
void fillColumn(char currentDisk, int columnNumber);
int check(char currentDisk);
void playComputer(struct Player* currentPlayer);
void saveColumnsToWin(int column);
void setColumsToWin();
void initGame(char *gameMode);
void initScores();
int generateRandomInt(int min, int max);
void createPlayers(char playerName[], struct Player players[], char gameMode);
void startConnected4(char playerName[]);
void endGame(struct Player* winner, struct Player players[], int *playAgain);

void connected4(char playerName[]) {
    char choice = ' ';

    while(1) {

        gameMenu();

        scanf(" %c", &choice);
        
        if (choice == '1') {
            startConnected4(playerName);
            break;
        } else if (choice == '2') {
            setGamePoints(CONNECTED4);
            break;
        }

        wrongOption();
    }  
}

void startConnected4(char playerName[]) {

    char currentDisk;
    char gameMode;
    int playAgain;

    
    struct Player* players = malloc(2 * sizeof(struct Player));
    
    initGame(&gameMode);
    createPlayers(playerName, players, gameMode);

    system("clear || cls");

    struct Player* currentPlayer;

    currentPlayer = &players[0];

    while(1) {

        if (playAgain == 1) {
            initScores();
            setColumsToWin();
        }

        if (strcmp(currentPlayer->name, COMPUTER_NAME) == 0)
        {
            playComputer(currentPlayer);
        } else {
            play(currentPlayer);
        }

        playAgain = 0;

        if (check(currentPlayer->disk)) {
            endGame(currentPlayer, players, &playAgain);
            if (playAgain == 2) {
                break;
            }
        }

        if (playAgain == 1) {
            currentPlayer = &players[0];
        } else {
            if (strcmp(currentPlayer->name, players[0].name) == 0) {
                currentPlayer = &players[1];
            } else {
                currentPlayer = &players[0];
            }
        }        
    }
}

void boardC4() {

    printf("%s\n", HEADER);
    printf("%s\n", SPLITTER);

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMS; j++)
        {   
            int currentScore = scores[i][j];
            if (currentScore == 0)
                printf("|   ");
            else    
                printf("| %c ", scores[i][j]);
        }
        printf("|\n");
        printf("%s\n", SPLITTER);
    }
}

void play(struct Player* currentPlayer) {
    int columnNumber;
    char chosen;
    
    boardC4();
    printf("%s, é tua vez!\n", currentPlayer->name);
    printf("\nEscolher coluna: ");
    

    while(1) {

        scanf(" %c", &chosen);

        switch(chosen)
        {
            case '1':
                columnNumber = 0;
                break;
            case '2':
                columnNumber = 1;
                break;
            case '3':
                columnNumber = 2;
                break;
            case '4':
                columnNumber = 3;
                break;
            case '5':
                columnNumber = 4;
                break;
            case '6':
                columnNumber = 5;
                break;
            case '7':
                columnNumber = 6;
                break;
            default:
                //columnNumber = -1;
                printf("\nColuna errada! Tenta outra vez\n\n");
                boardC4();
        }
        // break out of while loop if the right letter was chosen:
        if ((columnNumber >= 0 && columnNumber <= 6) && (scores[0][columnNumber] == 0))
        {
            fillColumn(currentPlayer->disk, columnNumber);
            break;
        }
    }

    printf("\n\n");
}

void playComputer(struct Player* currentPlayer) {

    int columnToPlay;
    int hasColumnsToWin = 0;
    int chances = 0;
    int r;
    int ch;

    for (int i = 0; i < COLUMS; i++) {
        if (columToWin[i] == -1) {
            break;
        }
        chances++;
    }

    boardC4();
    printf("Computador a jogar.\n");

	pressEnter();

    while (1)
    {
        r = generateRandomInt(0, 101);
        if (r > 25 && chances > 0) {

            if (chances == 1) {
                columnToPlay = columToWin[0];
            } else {
                int index = generateRandomInt(0, chances);
                columnToPlay = columToWin[index];
            }
            
        } else {
            columnToPlay = generateRandomInt(0, 6);
        }

        if (scores[0][columnToPlay] == 0)
        {
            fillColumn(currentPlayer->disk, columnToPlay);
            break;
        }
    }

    setColumsToWin();
}

void fillColumn(char currentDisk, int columnNumber) {
    for (int level = ROWS-1; level >= 0; level--)
    {
        if (scores[level][columnNumber] == 0)
        {
            scores[level][columnNumber] = currentDisk;
            break;
        }   
    }    
}

int check(char currentDisk) {

    for (int i = 0; i < ROWS; i++)
    {
        int count = 0;

        for(int j = 0; j < COLUMS; j++)
        {
            if (j == 4 && scores[i][j] != currentDisk) {
                count = 0;
                break;
            } else if (scores[i][j] == currentDisk) {
                count++;
            } else {
                count = 0;
            }

            if (count == 3 && isComputer == 1) {
                if (scores[i][j + 1] == 0) {
                    saveColumnsToWin(j + 1);
                }

                if (scores[i][j - 3] == 0) {
                    saveColumnsToWin(j - 3);
                }
                
            }

            if (count == 4) return 1;
            
        }
    }

    for (int i = 0; i < COLUMS; i++)
    {
        int count = 0;

        for(int j = 0; j < ROWS; j++)
        {
            if (scores[j][i] == currentDisk) {
                count++;
            } else {
                count = 0;
            }

            if (count == 3 && isComputer == 1 && i > 0 && scores[j][i - 1] == 0) {
                saveColumnsToWin(i);
            }

            if (count == 4) return 1;
            
        }
    }
    
    int diagToVerify = 6;

    int diagLeftRows = 2, diagLeftColums = 0, 
        diagRightRows = 3, diagRightColumns = 0;

    for (int i = 0; i < diagToVerify; i++) {
        // Diagonal left

        int leftCount = 0, rightCount = 0;;


        int rowsToCheck = diagLeftRows, columnsToCheck = diagLeftColums;
        while (rowsToCheck < 7 && columnsToCheck < 7) {

            if (scores[rowsToCheck][columnsToCheck] == currentDisk) {
                leftCount++;
            } else {
                leftCount = 0;
            }

            if (leftCount == 3 && isComputer == 1) {

                if (scores[rowsToCheck + 1][columnsToCheck + 1] == 0) {
                    saveColumnsToWin(columnsToCheck + 1);
                }

                if (scores[rowsToCheck - 3][columnsToCheck - 3] == 0) {
                    saveColumnsToWin(columnsToCheck - 3);
                }
            }

            if (leftCount == 4) return 1;

            rowsToCheck++;
            columnsToCheck++;
        }

        int secondRowsToCheck = diagRightRows; 
        int secondColumnsToCheck = diagRightColumns;
        while ( secondRowsToCheck > -1 && secondRowsToCheck < 6 &&  secondColumnsToCheck < 7) {

            if (scores[secondRowsToCheck][secondColumnsToCheck] == currentDisk) {
                rightCount++;
            } else {
                rightCount = 0;
            }

            if (leftCount == 3 && isComputer == 1) {
                if (scores[rowsToCheck - 1][columnsToCheck + 1] == 0) {
                    saveColumnsToWin(columnsToCheck + 1);
                }

                if (scores[rowsToCheck + 3][columnsToCheck - 3] == 0) {
                    saveColumnsToWin(columnsToCheck - 3);
                }
            }

            if (rightCount == 4) return 1;

            secondRowsToCheck--;
            secondColumnsToCheck++;

        }

        if (diagLeftRows == 0 && diagLeftColums == 0) {
            diagLeftColums++;
        }  else if (diagLeftRows > 0) {
            diagLeftRows--;
        }  else if (diagLeftColums > 0) {
            diagLeftColums++;
        } 

        if (diagRightRows == 5 && diagRightColumns == 6) {
            diagRightColumns++;
        } else if (diagRightRows < 5) {
            diagRightRows++;
        } else if (diagRightColumns < 6) {
            diagRightColumns++;
        }
    } 

    
    return 0;
}

void saveColumnsToWin(int column) {
    for (int i = 0; i < 8; i++) {
        int col = columToWin[i];

        if (col == -1 && col != column) {
            columToWin[i] = column;
            break;
        };
    }
};

void setColumsToWin() {
    for (int i = 0; i < COLUMS; i++) {
        columToWin[i] = -1;
    }
}

int generateRandomInt(int min, int max) {
    srand((unsigned)time(NULL));
    return min + rand() % (max - min);
}

void initGame(char *gameMode) {
    initScores(); 
    setColumsToWin();
    

    printf("1. vs jogador\n");
    printf("2. vs cpu\n");

    while(1) {
        scanf(" %c", gameMode);

        if (*gameMode == '2') {
            isComputer = 1;
            break;
        } else if (*gameMode == '1') {
            break;
        }
    }
}

void initScores() {
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMS; j++)
        {
            scores[i][j] = 0;
        }
    }
}

void createPlayers(char playerName[], struct Player* players, char gameMode) {
    char player2Name[15];

    if (gameMode == '2') {
        strcpy(player2Name, COMPUTER_NAME);
    } else {
        printf("Nome do jogador 2: \n");
        scanf("%s", player2Name);
    }

    players[0].disk = malloc(sizeof(char));
    players[0].score = malloc(sizeof(int));

    players[1].disk = malloc(sizeof(char));
    players[1].score = malloc(sizeof(int));

    strcpy(players[0].name, playerName);
    players[0].disk = DISK1;
    players[0].score = 0;

    strcpy(players[1].name, player2Name);
    players[1].disk = DISK2;
    players[1].score = 0;
}

void endGame(struct Player* winner, struct Player players[], int *playAgain) {
    struct Player* looser = malloc(sizeof(struct Player));


    if (strcmp(winner->name, players[0].name) == 0) {
        looser = &players[1];
    } else {
        looser = &players[0];
    }

    winner->score += 4;
    looser->score -= 4;

    if (looser->score < 0) {
        looser->score = 0;
    }

    char* nameToDisplay = strcmp(winner->name, COMPUTER_NAME) == 0 ? "Computador" : winner->name;

    printf("%s ganhou! Parabéns!\n", nameToDisplay);
    pressEnter();

    while(1) {
        playAgainScreen();
        scanf(" %d", playAgain);

        if (*playAgain == 1 || *playAgain == 2) {
            break;
        }
    }

    if (*playAgain == 2) {

        char* winnerName = winner->name;

        if(strcmp(winnerName, COMPUTER_NAME) != 0) {
            saveFile(winnerName, CONNECTED4, winner->score);
        }

        char* looserName = looser->name;

        if(strcmp(looserName, COMPUTER_NAME) != 0) {
            saveFile(looserName, CONNECTED4, looser->score);
        }

        printf("\n\nObrigado por jogares o quatro em linha :)\n");
    }
}