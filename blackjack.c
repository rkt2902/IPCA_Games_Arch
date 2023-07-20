#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#ifdef _WIN32
	#include<conio.h>
#endif
#include "games.h"
#include "utils.h"
#include "files.h"

void singlePlayerGame(); 
void playerChoice(); 
void defineStrength(); 
void hit(); 
void restartSinglePlayerGame();
void stand(); 
void initialiseDeck(); 
void displayDeck(); 
void dealerTurn(); 
void dealerHit(); 


int menuScreen = 0, cardsDrawn = 0;
int playerOnePoints = 0, dealerPoints = 0, activePlayer = 0;
int dealerCardRevealed = 0;
int pointsToSave = 0;

struct deck { //structure to initilise deck of cards easier
	char* strength;
	char suit[20];
};

typedef struct deck Deck;

char* strength[13] = { "As", "Dois", "Tres", "Quatro", "Cinco", "Seis", "Sete", "Oito", "Nove", "Dez", "Valete", "Dama", "Rei" };
char suit[4][20] = { "Paus", "Ouros", "Copas", "Espadas" };
char playerNameToSave[NAMES_SIZE];

void randomiseDeck(Deck[]);
Deck deck[52] = { "", "" }; 

void startBlackjack();

void blackjack(char playerName[]) {
	char choice = ' ';
	strcpy(playerNameToSave, playerName);

    while(1) {

        gameMenu();

        scanf(" %c", &choice);
        
        if (choice == '1') {
            startBlackjack();
            break;
        } else if (choice == '2') {
            setGamePoints(BLACKJACK);
            break;
        } else {
			wrongOption();
		}
        
    } 
}

void startBlackjack() {
	system("cls"); 
    printf("# # # # # # # # # # # # # # # # # # # #\n");
    printf("#                                     #\n");
	printf("#              VINTE E UM             #\n");
	printf("#                                     #\n");
	printf("# # # # # # # # # # # # # # # # # # # #\n");
	printf("\n         Escolha uma opcao:\n");

	initialiseDeck(); //making deck
	randomiseDeck(deck); //shuffling

	singlePlayerGame(); //from this function everything else is called from

}

void singlePlayerGame() {
	system("clear || cls"); 

	cardsDrawn = 0;
	playerOnePoints = 0;
	dealerPoints = 0;
	dealerCardRevealed = 0;

    printf("# # # # # # # # # # # # # # # # # # # #\n");
    printf("#                                     #\n");
    printf("#             INSTRUCOES              #\n");
	printf("#        1 ---->  PEDIR CARTA         #\n");
	printf("#        2 ---->  FICAR               #\n");
	printf("#                                     #\n");
	printf("# # # # # # # # # # # # # # # # # # # #\n");

	printf("\n      Dealer Distribui as Cartas \n     ............................\n ");
	
	activePlayer = 0;
	
	printf("\n             Dealer tem:  \n\n ");
	displayDeck(); //card 0
	defineStrength();
	cardsDrawn++; //cards drawn = 1
	printf("       Carta Virada para Baixo\n");
	printf("\n     Dealer tem %d pontos visiveis\n     ............................\n", dealerPoints);
	defineStrength();
	cardsDrawn++; //cards drawn = 2
	

	printf("\n            JOGARDOR tem:  \n\n ");  //ERA BOM CONSEGUIR POR AQUI O NOME DO JOGADOR
	activePlayer = 1;
	displayDeck(); // card 2
	defineStrength();
	cardsDrawn++; //cards drawm = 3



	printf("         JOGADOR tem %d pontos \n     ............................\n", playerOnePoints);

	if (dealerPoints == 21 && playerOnePoints == 21) {
		printf("  Dealer Mostra Vinte e Um e o jogo empata!\n");
		restartSinglePlayerGame();
	}
	else if (dealerPoints == 21) {
		pointsToSave--;
		if (pointsToSave < 0) {
			pointsToSave = 0;
		}
		printf("Dealer mostra Vinte e Um, %s perde!\n", playerNameToSave);
		restartSinglePlayerGame();
	}
	else if (playerOnePoints == 21) {
		pointsToSave++;
		printf("%s ganha com Vinte e Um\n", playerNameToSave);
		restartSinglePlayerGame();
	}


	playerChoice();

}

void playerChoice()
{
	int option;
	
		printf("\n        Deseja PEDIR ou FICAR?\n");
		scanf("%d", &option);
		
	switch (option) {
		case 1:
			hit();
			break;
		case 2:
			stand();
			break;
		default:
			hit();
			break;
		}
}


void defineStrength()
{
	if (activePlayer == 0) {
		if (strcmp(deck[cardsDrawn].strength, "Dois") == 0) {
			dealerPoints += 2;
		}
		else if (strcmp(deck[cardsDrawn].strength, "Tres") == 0) {
			dealerPoints += 3;
		}
		else if (strcmp(deck[cardsDrawn].strength, "Quatro") == 0) {
			dealerPoints += 4;
		}
		else if (strcmp(deck[cardsDrawn].strength, "Cinco") == 0) {
			dealerPoints += 5;
		}
		else if (strcmp(deck[cardsDrawn].strength, "Seis") == 0) {
			dealerPoints += 6;
		}
		else if (strcmp(deck[cardsDrawn].strength, "Sete") == 0) {
			dealerPoints += 7;
		}
		else if (strcmp(deck[cardsDrawn].strength, "Oito") == 0) {
			dealerPoints += 8;
		}
		else if (strcmp(deck[cardsDrawn].strength, "Nove") == 0) {
			dealerPoints += 9;
		}
		else if (strcmp(deck[cardsDrawn].strength, "Dez") == 0) {
			dealerPoints += 10;
		}
		else if (strcmp(deck[cardsDrawn].strength, "Valete") == 0) {
			dealerPoints += 10;
		}
		else if (strcmp(deck[cardsDrawn].strength, "Dama") == 0) {
			dealerPoints += 10;
		}
		else if (strcmp(deck[cardsDrawn].strength, "Rei") == 0) {
			dealerPoints += 10;
		}
		else if (strcmp(deck[cardsDrawn].strength, "As") == 0) {
			dealerPoints += 1;

		}
	}
	else if (activePlayer == 1) {
		if (strcmp(deck[cardsDrawn].strength, "Dois") == 0) {
			playerOnePoints += 2;
		}
		else if (strcmp(deck[cardsDrawn].strength, "Tres") == 0) {
			playerOnePoints += 3;
		}
		else if (strcmp(deck[cardsDrawn].strength, "Quatro") == 0) {
			playerOnePoints += 4;
		}
		else if (strcmp(deck[cardsDrawn].strength, "Cinco") == 0) {
			playerOnePoints += 5;
		}
		else if (strcmp(deck[cardsDrawn].strength, "Seis") == 0) {
			playerOnePoints += 6;
		}
		else if (strcmp(deck[cardsDrawn].strength, "Sete") == 0) {
			playerOnePoints += 7;
		}
		else if (strcmp(deck[cardsDrawn].strength, "Oito") == 0) {
			playerOnePoints += 8;
		}
		else if (strcmp(deck[cardsDrawn].strength, "Nove") == 0) {
			playerOnePoints += 9;
		}
		else if (strcmp(deck[cardsDrawn].strength, "Dez") == 0) {
			playerOnePoints += 10;
		}
		else if (strcmp(deck[cardsDrawn].strength, "Valete") == 0) {
			playerOnePoints += 10;
		}
		else if (strcmp(deck[cardsDrawn].strength, "Dama") == 0) {
			playerOnePoints += 10;
		}
		else if (strcmp(deck[cardsDrawn].strength, "Rei") == 0) {
			playerOnePoints += 10;
		}
		else if (strcmp(deck[cardsDrawn].strength, "As") == 0) {
			playerOnePoints += 1;
		}
	}
}

void restartSinglePlayerGame()
{
	int option;

	randomiseDeck(deck);



	while(1) {
		playAgainScreen();
		scanf(" %d", &option);

		if (option == 1) {
			singlePlayerGame();
			break;
		}
		else if (option == 2) { 
			saveFile(playerNameToSave, BLACKJACK, playerOnePoints);
			printf("\nObrigado por teres jogado o Vinte e Um :)");
			break;
		}

		wrongOption();
	}
}

void dealerTurn()
{
	activePlayer = 0;

	if (dealerCardRevealed == 0) {
		printf("\n      Dealer mostra a sua carta:\n");
		printf("\n            %s de %s\n\n", deck[1].strength, deck[1].suit);
		dealerCardRevealed = 1;
	}

	if (dealerPoints <= playerOnePoints) {
			dealerHit();
	}
	

	else if (dealerPoints > 21) {
			pointsToSave++;
			printf("Dealer rebentou, %s ganha com : %d pontos!\n     ............................\n", playerNameToSave, playerOnePoints);
			restartSinglePlayerGame();

	}
	else if (dealerPoints > playerOnePoints){
			pointsToSave--;
			if (pointsToSave < 0) {
				pointsToSave = 0;
			}

			printf("     Dealer ganha com: %d pontos!\n     ............................\n", dealerPoints);
			restartSinglePlayerGame();
	}
	
}

void dealerHit()
{
	printf("      Dealer tem : %d pontos!\n\n     ............................\n\n", dealerPoints);
	printf("     Dealer Retira Outra Carta\n\n");
	displayDeck();
	defineStrength();
	cardsDrawn++;

	if (dealerPoints <  playerOnePoints) {
		dealerHit();
	}
	else {
		dealerTurn();
	}
}

void stand()
{
		printf("       JOGADOR escolheu ficar!\n\n    JOGADOR ficou com : %d pontos!\n     ............................\n", playerOnePoints);
		dealerTurn();
}

void hit()
{
		displayDeck();
		defineStrength();
		cardsDrawn++;
		printf("         JOGADOR tem %d pontos \n     ............................\n", playerOnePoints);

		if (playerOnePoints > 21) {
			printf("\n\n   O JOGADOR rebentou, Dealer Ganha!\n\n     ............................\n");
			restartSinglePlayerGame();
		}
		else if (playerOnePoints == 21) {
			stand();
		}
		else if (playerOnePoints < 21) {
			playerChoice();
		}

}

void displayDeck() {
	printf("           %s de %s\n\n", deck[cardsDrawn].strength, deck[cardsDrawn].suit);
}

void randomiseDeck(Deck deck[])
{
	int indexSwap = 0;
	Deck temp = { "", "" };
	srand(time(NULL));
	int i;
	for (i = 0; i < 52; i++) {
		indexSwap = rand() % (52);
		temp = deck[i];
		deck[i] = deck[indexSwap];
		deck[indexSwap] = temp;
	} //creating a temperorary structure deck to store the changed index
}

void initialiseDeck()
{
	int i;
	for ( i = 0; i < 52; i++) {
		deck[i].strength = strength[i % 13];
		strncpy(deck[i].suit, suit[i / 13], 9);
	}
}
