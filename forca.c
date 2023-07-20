#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include "games.h"
#include "utils.h"
#include "files.h"

void startForca(char playerName[]);

void forca(char playerName[]) {
    char choice = ' ';

    while(1) {

        gameMenu();

        scanf(" %c", &choice);
        
        if (choice == '1') {
            startForca(playerName);
            break;
        } else if (choice == '2') {
            setGamePoints(FORCA);
            break;
        }

        wrongOption();
    }  
}

void startForca(char playerName[]) {

	srand(time(NULL));
	char playerNameToSave[NAMES_SIZE];
	int pointsToSave = 0;
	
	char guessWords[][16] = {
		"azul", "chavena"
		"roda", "amarelo","pincel", "rolha", "anel", "pai", "computador", "comando", "cama", "barriga", "padre", "professor", "maquina", "amor", "amigo", "loja", "pastel", "castelo", "telemovel","prato", "bolachas","transito","fila","nike","adidas", "feira", "rosca", "feriado"
	};
	
	// index for random word
	int randomIndex = rand() % 30;
	
	int numLives = 6;
	int numCorrect = 0;
	int oldCorrect = 0;
	
	int lengthOfWord = strlen(guessWords[randomIndex]);
	
	//					     0 1 2 3 4 5
	//				         p u r p l e
	//  letterGuessed[8] = { 0,0,0,0,0,0,0,0 };
	int letterGuessed[8] = { 0,0,0,0,0,0,0,0 };
	
	int quit = 0;	
	
	int loopIndex = 0;
	int reguessed = 0; // EDIT
	
	char guess[16];
	char letterEntered;	
	
	printf("Jogo da Forca");
    // game loop	
	while ( numCorrect < lengthOfWord ) {
	
		printf("\n\n\nPALAVRA : ");
	
		for( loopIndex = 0; loopIndex < lengthOfWord; loopIndex++) {
		
			if(letterGuessed[loopIndex] == 1) {
				printf("%c ",guessWords[randomIndex][loopIndex]);			
			} else {
				printf("- ");
			}
		
		}	
		
		printf("\n");
	
		printf("Numero de acertos :%d\n",numCorrect);
		printf("Introduza um letra ou a Palavra:");
		fgets(guess, 16, stdin);
		
		if( strncmp(guess, "quit", 4) == 0) {
			quit = 1;
			break;
		}
			else if (strncmp(guess, guessWords[randomIndex], lengthOfWord) == 0){
			printf("Acertou a palavra!");
			pointsToSave = pointsToSave + (lengthOfWord-((6+pointsToSave)-numLives));
			
			break;
		}
			else{
			
		
		letterEntered = guess[0];
		reguessed = 0; 
		
		
		oldCorrect = numCorrect;
		
		for( loopIndex = 0; loopIndex < lengthOfWord; loopIndex++) {
		
			if(letterGuessed[loopIndex] == 1) {
				if(guessWords[randomIndex][loopIndex] == letterEntered) {
					reguessed = 1; 
					break;
				} 
				continue;
			}
		
			if( letterEntered == guessWords[randomIndex][loopIndex] ) {
				letterGuessed[loopIndex] = 1;
				numCorrect++;
						
			}		
		
		}	
		
		if( oldCorrect == numCorrect && reguessed == 0) {
			numLives--;
			pointsToSave--;	
			if (pointsToSave < 0) {
			pointsToSave = 0;
		}
			//PERDER 1 PONTUACAO
			printf("Errado!\n");
			if (numLives == 0) {
				break;
			}
		} else if( reguessed == 1) {
			printf("Ja tentou adivinhar!\n");
		} else {
			printf("Acertou!\n");
			pointsToSave++;
			//GANHAR 1 PONTUACAO
		}
	
	} // while loop
}
	if( quit == 1 ) {	
		printf("\nO jogador saiu mais cedo\n");
	} else if (numLives == 0) {
		printf("\nAcabaram as vidas, a palavra era: %s\n",
		guessWords[randomIndex]);
        saveFile(playerName, FORCA, pointsToSave);
	} else  {	
		printf("\nGanhou! Parabens!\n");
        saveFile(playerName, FORCA, pointsToSave);
	}
	
}