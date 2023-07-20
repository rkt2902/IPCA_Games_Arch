#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "games.h"
#include "files.h"
#include "utils.h"

char square[10];

int startTicTacToe(char playerName[], char player2Name[]);
int checkwin();
void boardTtt();
void initSquares();

int player1Points = 0, player2Points = 0;

void ticTacToe(char playerName[]) {
    char choice = ' ';

    while(1) {

        gameMenu();

        scanf(" %c", &choice);
        
        if (choice == '1') {
            char player2Name[NAMES_SIZE];            
            printf("Nome do jogador 2: \n");
            scanf("%s", player2Name);
            startTicTacToe(playerName, player2Name);
            break;
        } else if (choice == '2') {
            setGamePoints(TIC_TAC_TOE);
            break;
        } else {
			wrongOption();
		}
    }  
};

int startTicTacToe(char playerName[], char player2Name[]) {
    int player = 1, i, choice;

    char mark;
    char nameToDisplay[NAMES_SIZE];

    initSquares();

    do
    {
        boardTtt();
        player = (player % 2) ? 1 : 2;

        if (player == 1) {
            strcpy(nameToDisplay, playerName);
        } else {
            strcpy(nameToDisplay, player2Name);
        }

        printf("%s, insere um número:  ", nameToDisplay);
        scanf(" %d", &choice);

        mark = (player == 1) ? 'X' : 'O';

        if (choice == 1 && square[1] == '1')
            square[1] = mark;

        else if (choice == 2 && square[2] == '2')
            square[2] = mark;

        else if (choice == 3 && square[3] == '3')
            square[3] = mark;

        else if (choice == 4 && square[4] == '4')
            square[4] = mark;

        else if (choice == 5 && square[5] == '5')
            square[5] = mark;

        else if (choice == 6 && square[6] == '6')
            square[6] = mark;

        else if (choice == 7 && square[7] == '7')
            square[7] = mark;

        else if (choice == 8 && square[8] == '8')
            square[8] = mark;

        else if (choice == 9 && square[9] == '9')
            square[9] = mark;

        else
        {
            printf("Invalid move ");

            player--;
           
        }
        i = checkwin();

        player++;

    if (i == 1){
        printf("==>\aPlayer %d win ", --player);        
    } else
        printf("==>\aGame draw");
    } while (i == -1);

    boardTtt();

    if (player == 1) {
        player1Points++;
        player2Points-=2;

        if (player2Points < 0) {
            player2Points = 0;
        }
    } else {
        player1Points-=2;
        player2Points++;

        if (player1Points < 0) {
            player1Points = 0;
        }
    }

    char playAgain;

    while (1)
    {
        playAgainScreen();

        scanf(" %c", &playAgain);

        if (playAgain == '1') {
            startTicTacToe(playerName, player2Name);
            break;
        } else if(playAgain == '2') {
            saveFile(playerName, TIC_TAC_TOE, player1Points);
            saveFile(player2Name, TIC_TAC_TOE, player2Points);
            printf("Obrigado por jogares o jogo do galo :)\n");
            break;
        }

        wrongOption();
    }

    return 0;
}

int checkwin()
{
    if (square[1] == square[2] && square[2] == square[3])
        return 1;

    else if (square[4] == square[5] && square[5] == square[6])
        return 1;

    else if (square[7] == square[8] && square[8] == square[9])
        return 1;

    else if (square[1] == square[4] && square[4] == square[7])
        return 1;

    else if (square[2] == square[5] && square[5] == square[8])
        return 1;

    else if (square[3] == square[6] && square[6] == square[9])
        return 1;

    else if (square[1] == square[5] && square[5] == square[9])
        return 1;

    else if (square[3] == square[5] && square[5] == square[7])
        return 1;

    else if (square[1] != '1' && square[2] != '2' && square[3] != '3' &&
        square[4] != '4' && square[5] != '5' && square[6] != '6' && square[7]
        != '7' && square[8] != '8' && square[9] != '9')

        return 0;
    else
        return  -1;
}

void boardTtt()
{
    system("cls");
    printf("\n\n\tTic Tac Toe\n\n");

    printf("Player 1 (X)  -  Player 2 (O)\n\n\n");


    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c \n", square[1], square[2], square[3]);

    printf("_____|_____|_____\n");
    printf("     |     |     \n");

    printf("  %c  |  %c  |  %c \n", square[4], square[5], square[6]);

    printf("_____|_____|_____\n");
    printf("     |     |     \n");

    printf("  %c  |  %c  |  %c \n", square[7], square[8], square[9]);

    printf("     |     |     \n\n");
}

void initSquares() {
    square[0] = '0';
    square[1] = '1';
    square[2] = '2';
    square[3] = '3';
    square[4] = '4';
    square[5] = '5';
    square[6] = '6';
    square[7] = '7';
    square[8] = '8';
    square[9] = '9';
}