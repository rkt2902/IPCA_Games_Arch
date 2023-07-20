#include <stdio.h>
#include "utils.h"

void pressEnter() {
    int ch;
	while ((ch = getchar()) != '\n' && ch != EOF); 
	printf("\n\nPressione Enter para continuar.");
	while ((ch = getchar()) != '\n' && ch != EOF);
};

void gameMenu() {
    printf("1. Jogar\n");
    printf("2. Ver pontuações\n");
};

void playAgainScreen() {
	printf("Jogar outra vez?\n");
	printf("1. Sim\n");
	printf("2. Não\n");
};

void wrongOption() {
	printf("Opção errada! Volta a tentar!\n");
}