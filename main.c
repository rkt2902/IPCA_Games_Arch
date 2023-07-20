#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "files.h"
#include "utils.h"
#include "games.h"

#define TOTAL_OPTIONS 11

void mainMenu();

void main() {
	int ch;
	char user[NAMES_SIZE];
	int records;
	printf("\n \t --- Bem Vindo ao IPCA Games Arch! --- \n Introduza o seu nome de Utilizador: \n");
	scanf("%s", user);

	pressEnter();
	system("cls"); 
	mainMenu();

	int option = 9;

	scanf("%d", &option);

	switch (option)
	{
	case 1:
		setPlayerPoints(user);   
		break;
	case 2:
		setGlobalPoints();
		break;
	case 3:
		guessNumber(user); 
		break;
	case 4:
		guessCard(user);
		break;
	case 5:
		blackjack(user);
		break;
	case 6:
		ticTacToe(user);
		break;
	case 7:
		ticTacToeCpu(user);
		break;
	case 8:
		forca(user);
		break;
	case 9:
		connected4(user);
		break;
	case 0: printf("A Fechar Programa!\n");
		exit(1);
		break;
	default: printf("Escolha invalida\n");
		exit(1);
		break;
	}
}

void mainMenu()
{
	system("cls");
	printf("Menu:\n\n");
	printf("1.    A tua pontuação\n");
	printf("2.    Pontuações globais\n");
	printf("3.    Adivinha o numero.\n");
	printf("4.    Adivinha a carta.\n");
	printf("5.    Vinte e um.\n");
	printf("6.    Jogo do Galo.\n");
	printf("7.    Jogo do Galo vs CPU.\n");
	printf("8.    Jogo da Forca.\n");
	printf("9.    Quatro em Linha.\n");


	printf("0.    Sair\n");
}
