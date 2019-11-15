#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_CARDSET			1
#define N_CARD				52
#define N_DOLLAR			50


#define N_MAX_CARDNUM		13
#define N_MAX_USER			5
#define N_MAX_CARDHOLD		10
#define N_MAX_GO			17
#define N_MAX_BET			5

#define N_MIN_ENDCARD		30


extern gameEnd = 0;
int Cardcnt[N_MAX_USER]={2,2,2,2,2};
extern cardSum[N_MAX_USER];
extern cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];
extern n_user;
int roundcnt=1;

int main(int argc, char *argv[]) {
	
	int roundIndex = 0;
	int max_user;
	int i;
	
	printf("####################\n");
	printf("######BLACKJAK######\n");
	printf("####################\n\n");
	
	srand((unsigned)time(NULL));
	
	//set the number of players
	configUser();

	
	//Game initialization --------
	//1. players' dollar
	
	//2. card tray
	mixCardTray();

	//Game start --------
	do {
		int i;
		 
		betDollar();
		offerCards(); //1. give cards to all the players
		
		printCardInitialStatus();
		printf("\n------------------ GAME start --------------------------\n");
		
		
		//my turn
		printf(">>> my turn! -------------\n");
		
		int input;
		
		while(input==0 && cardSum[0]<21)
		{	
			printUserCardStatus(0,Cardcnt[0]);
			printf("Action? (0 - go, others - stay) :");
			input = getIntegerInput();
			
			
			cardhold[0][Cardcnt[0]] = pullCard();
			calcStepResult(0,Cardcnt[0]);
			printf("%d",cardSum[0]);
			Cardcnt[0]++;		
		}
		
		
		//each player's turn
		for (i=1;i<n_user;i++) //each player
		{	
			
			printf(">>> player %d turn! -------\n",i);
			while () //do until the player dies or player says stop
			{
				printUserCardStatus(i,cardcnt);//print current card status
				calcStepResult(int user,int cardcnt);//check the card status :::
				getAction();//GO? STOP? :::
				cardhold[0][cardcnt] = pullCard(); 
				//check if the turn ends or not
			}
		}
		
		//server's turn
		printf(">>> server turn! ----------\n")
		while()//cardsum<17 
		{	
			
			printUserCardStatus(i,cardcnt[n_user]);
			calcStepResult();
			getAction();
			if(getAction==1)
			{
			cardhold[n_user][cardcnt] = pullCard();	
			}
			
		}
		
		//result
		checkResult();
		roundcnt++;
		
	} while (gameEnd == 0);
	
	checkWinner();
	
	
	return 0;
}

