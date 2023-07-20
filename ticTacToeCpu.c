#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "games.h"
#include "utils.h"
#include "files.h"

int startTicTacToeCpu(char playerName[]);

int playerPoints = 0;

void ticTacToeCpu(char playerName[]) {
    char choice;

    while(1) {

        gameMenu();

        scanf(" %c", &choice);
        
        if (choice == '1') {
            startTicTacToeCpu(playerName);
            break;
        } else if (choice == '2') {
            setGamePoints(TIC_TAC_TOE);
            break;
        } 
		
        wrongOption();
    } 
};

int generateRandomIntTICTACTOE_PVE(int min, int max) {      //Cria um valor random
    srand((unsigned)time(NULL));
    return min + rand() % (max - min);
}

char tileValues[10] = { 'o', '7', '8', '9', '4', '5', '6', '1', '2', '3' };     //Array para o tabuleiro

int checkwinTICTACTOE_CPU() {                       //Verifica quem ganha   X=PLayer    O=CPU
                                                    //1=>Vitoria do Player   2=>Vitoria do CPU    0=>Empate    -1=>O jogo ainda nao acabou   
    if (tileValues[1] == tileValues[2] && tileValues[2] == tileValues[3]) {
        if (tileValues[1] == 'X') {
            return 1;
        }
        else return 2;
    }
    else if (tileValues[4] == tileValues[5] && tileValues[5] == tileValues[6]) {
        if (tileValues[4] == 'X') {
            return 1;
        }
        else return 2;
    }
    else if (tileValues[7] == tileValues[8] && tileValues[8] == tileValues[9]) {
        if (tileValues[7] == 'X') {
            return 1;
        }
        else return 2;
    }
    else if (tileValues[1] == tileValues[4] && tileValues[4] == tileValues[7]) {
        if (tileValues[1] == 'X') {
            return 1;
        }
        else return 2;
    }
    else if (tileValues[2] == tileValues[5] && tileValues[5] == tileValues[8]) {
        if (tileValues[2] == 'X') {
            return 1;
        }
        else return 2;
    }
    else if (tileValues[3] == tileValues[6] && tileValues[6] == tileValues[9]) {
        if (tileValues[3] == 'X') {
            return 1;
        }
        else return 2;
    }
    else if (tileValues[1] == tileValues[5] && tileValues[5] == tileValues[9]) {
        if (tileValues[1] == 'X') {
            return 1;
        }
        else return 2;
    }
    else if (tileValues[3] == tileValues[5] && tileValues[5] == tileValues[7]) {
        if (tileValues[3] == 'X') {
            return 1;
        }
        else return 2;
    }
    else if (tileValues[1] != '7' && tileValues[2] != '8' && tileValues[3] != '9' &&
        tileValues[4] != '4' && tileValues[5] != '5' && tileValues[6] != '6' && tileValues[7]
        != '1' && tileValues[8] != '2' && tileValues[9] != '3')

        return 0;
    else
        return -1;
}

void boardTICTACTOE_PVE() {                           

    char a = '|', b = '-', c = '|';

    printf("\nJogador (X)  -  Computador (O)\n\n\n");

    printf("     %c     %c     \n", a, a);
    printf("  %c  %c  %c  %c  %c \n", tileValues[1], a, tileValues[2], a, tileValues[3]);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", b, b, b, b, b, c, b, b, b, b, b, c, b, b, b, b, b);
    printf("     %c     %c     \n", a, a);
    printf("  %c  %c  %c  %c  %c \n", tileValues[4], a, tileValues[5], a, tileValues[6]);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", b, b, b, b, b, c, b, b, b, b, b, c, b, b, b, b, b);
    printf("     %c     %c     \n", a, a);
    printf("  %c  %c  %c  %c  %c \n", tileValues[7], a, tileValues[8], a, tileValues[9]);
    printf("     %c     %c     \n\n", a, a);
}

int startTicTacToeCpu(char playerName[]) {

    char a = 196;
    int i, j, choice, cpuchoice;
    printf("\n\n\t\tBem-vindo ao jogo do galo\n\t\tNumPad Number Position\n\n\t\t");
    char mark, cpumark;
    do
    {
        boardTICTACTOE_PVE();
        printf("Inserir numero: ");
        int validnumb = scanf("%d", &choice);

        if (validnumb == 0) {                               //Verifica se o valor é válido                            

            printf("\n\nValor invalido");
        }                   
        else {                                              //Escreve as escolhas do jogador
            mark = 'X';

            if (choice == 7 && tileValues[1] == '7') {
                tileValues[1] = mark;
            }
            else if (choice == 8 && tileValues[2] == '8') {
                tileValues[2] = mark;
            }
            else if (choice == 9 && tileValues[3] == '9') {
                tileValues[3] = mark;
            }
            else if (choice == 4 && tileValues[4] == '4') {
                tileValues[4] = mark;
            }
            else if (choice == 5 && tileValues[5] == '5') {
                tileValues[5] = mark;
            }
            else if (choice == 6 && tileValues[6] == '6') {
                tileValues[6] = mark;
            }
            else if (choice == 1 && tileValues[7] == '1') {
                tileValues[7] = mark;
            }
            else if (choice == 2 && tileValues[8] == '2') {
                tileValues[8] = mark;
            }
            else if (choice == 3 && tileValues[9] == '3') {
                tileValues[9] = mark;
            }
            else {
                wrongOption();
            }

            do
            {                                                             
                cpuchoice = generateRandomIntTICTACTOE_PVE(1, 9);
                cpumark = 'O';
                j = -1;

                if (cpuchoice == 7 && tileValues[1] == '7') {
                    tileValues[1] = cpumark; j++;
                }
                else if (cpuchoice == 8 && tileValues[2] == '8') {
                    tileValues[2] = cpumark; j++;
                }
                else if (cpuchoice == 9 && tileValues[3] == '9') {
                    tileValues[3] = cpumark; j++;
                }
                else if (cpuchoice == 4 && tileValues[4] == '4') {
                    tileValues[4] = cpumark; j++;
                }
                else if (cpuchoice == 5 && tileValues[5] == '5') {
                    tileValues[5] = cpumark; j++;
                }
                else if (cpuchoice == 6 && tileValues[6] == '6') {
                    tileValues[6] = cpumark; j++;
                }
                else if (cpuchoice == 1 && tileValues[7] == '1') {
                    tileValues[7] = cpumark; j++;
                }
                else if (cpuchoice == 2 && tileValues[8] == '2') {
                    tileValues[8] = cpumark; j++;
                }
                else if (cpuchoice == 3 && tileValues[9] == '3') {
                    tileValues[9] = cpumark; j++;
                }
                else {
                    j = -1;
                }

            } while (j == -1);         
         }
        i = checkwinTICTACTOE_CPU();

    } while (i == -1);

    boardTICTACTOE_PVE();
    system("cls");

    if (i == 1){
        printf("==> %s ganha\n", playerName);
        playerPoints++;
    } else if (i == 2) {
        playerPoints-=2;

        if (playerPoints < 0) {
            playerPoints=0;
        }

        printf("==> Computador ganha\n");
    } else {
        printf("==> Empate");
    }    

    char playAgain;

    while (1)
    {
        playAgainScreen();

        scanf(" %c", &playAgain);

        if (playAgain == '1') {

            break;
        } else if(playAgain == '2') {
            saveFile(playerName, TIC_TAC_TOE, playerPoints);
            printf("Obrigado por jogares o jogo do galo :)\n");
            break;
        }

        wrongOption();
    }

    return 0;
}
//Fim do jogo