#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int n_user;

int main(int argc, char *argv[]) {
	
	int roundIndex = 0;
	int max_user;
	int i;
	
	printf("####################\n");
	printf("######BLACKJAK######\n");
	printf("####################\n\n");
	
	printf("input the number of players (MAX:5) : ");

	scanf("%d",&n_user);
	
	
	
	srand((unsigned)time(NULL));
	
	//set the number of players
	configUser();


	//Game initialization --------
	//1. players' dollar
	
	//2. card tray
	mixCardTray();



	//Game start --------
	/*do {
		
		betDollar();
		offerCards(); //1. give cards to all the players
		
		printCardInitialStatus();
		printf("\n------------------ GAME start --------------------------\n");
		
		//each player's turn
		for () //each player
		{
			while () //do until the player dies or player says stop
			{
				//print current card status printUserCardStatus();
				//check the card status ::: calcStepResult()
				//GO? STOP? ::: getAction()
				//check if the turn ends or not
			}
		}
		
		//result
		checkResult();
	} while (gameEnd == 0);
	
	checkWinner();*/
	
	
	return 0;
}

