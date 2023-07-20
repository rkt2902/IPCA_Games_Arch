#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "games.h"
#include "files.h"

#define _CRT_SECURE_NO_WARNINGS

int randGuess();
void dicas(int number, int password, int attempt, char playerName[]);
void startGuessNumber(char playerName[]);

void guessNumber(char playerName[]) {
    char choice = ' ';

    while(1) {

        gameMenu();

        scanf(" %c", &choice);
        
        if (choice == '1') {
            startGuessNumber(playerName);
            break;
        } else if (choice == '2') {
            setGamePoints(GUESS_NUMBER);
            break;
        }

        wrongOption();
    }  
};

void startGuessNumber(char playerName[])
{
    int continuar = 1,
        password,
        attempt,
        number;

    do
    {
        system("cls || clear");
        printf("Sorteando numero entre 1 e 100...\n");
        password = randGuess();

        printf("Comecou! Tente adivinhar o numero!\n\n");
        attempt = 0;

        do
        {
            attempt++;
            printf("Tentativa %d: ", attempt);
            scanf("%d", &number);
            dicas(number, password, attempt, playerName);
        } while (number != password);

        printf("Digite 0 para sair, ou qualquer outro numero para continuar: ");
        scanf("%d", &continuar);
    } while (continuar);

}

int randGuess()
{
    srand((unsigned)time(NULL));

    return (1 + rand() % 100);
}

void dicas(int number, int password, int attempt, char playerName[])
{
    if (number > password)
        printf("O numero sorteado e menor que %d\n\n", number);
    else
        if (number < password)
            printf("O numero sorteado e maior que %d\n\n", number);
        else
        {
            printf("Parabens! Voce acertou o numero em %d tentativas!\n\n", attempt);
            int points = 10 - attempt;
            saveFile(playerName, GUESS_NUMBER, points);
            printf("voce conseguiu %d pontos!\n\n", points);
        }

}