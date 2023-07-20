#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "files.h"
#include "utils.h"
#include "games.h"

void startGuessCard(char playerName[]);

void guessCard(char playerName[]) {
    char choice = ' ';

    while(1) {

        gameMenu();

        scanf(" %c", &choice);
        
        if (choice == '1') {
            startGuessCard(playerName);
            break;
        } else if (choice == '2') {
            setGamePoints(GUESS_CARD);
            break;
        }

        wrongOption();
    }  
}



int generateRanInt(int min, int max) {
    srand((unsigned)time(NULL));
    return min + rand() % (max - min);
}


void startGuessCard(char playerName[]) {


    printf("Foi escolhida uma carta random, cabe te a ti descubrir.\n");
    printf("O 1 equivale ao As e outros numeros equivalem aos respetivos numeros sendo que o valete 11, a dama 12, e o rei 13.\n");
    printf("Nao existe joker.\n\n");
    printf("espadas 1| ouros 2 | paus 3 | copas 4\n\n");

    
    int numcarta = generateRanInt(1, 13);
    int naipecarta = generateRanInt(1, 4);

    int numguess, naipeguess, numpontos, result = 0, numtent = 0;

    
    while (result == 0) {

        printf("Numero da carta oculta: ");
        scanf("%d", &numguess);
        printf("\n");
        printf("Naipe da carta oculta: ");
        scanf("%d", &naipeguess);
        printf("\n");

        if ((numguess < 1 || numguess > 13) || (naipeguess < 1 || naipeguess > 4)) {

            printf("RESPOSTA INVALIDA.\n\n");

        }
        else {

            if (numguess != numcarta || naipeguess != naipecarta) {

                
                printf("-Resposta errada-\n\n");

                if (numguess > numcarta) {
                    printf("O numero da carta e menor.\n\n");
                }
                else {
                    if (numguess < numcarta) {
                        printf("O numero da carta e maior.\n\n");
                    }
                    else {
                        printf("O numero escolhido esta correto!\n\n");
                    }
                }

                if (naipeguess != naipecarta) {
                    printf("O naipe escolhido esta errado.\n\n");
                }
                else {
                    printf("O naipe escolhido esta certo!\n\n");
                }

                numtent++;
            }
        }

        if (numguess == numcarta && naipeguess == naipecarta) {


            printf("-RESPOSTA CORRETA-\n\n");

            numtent++;
            numpontos = (7 - numtent);

            saveFile(playerName, GUESS_CARD, numpontos);

            printf("TENTATIVAS: %d\n\n", numtent);

            printf("PONTUACAO: %d\n\n", numpontos);

            result++;

        }
    }
}