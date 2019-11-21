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


int roundcnt=1;								
int blackjack[N_MAX_USER];					//blackjack status
int winner[N_MAX_USER];						//money ranking
int win;

							
int Cardcnt[N_MAX_USER];					//each player's Number of cards received in the game

//card tray object
int CardTray[N_CARDSET*N_CARD];
int cardIndex = 0;	
						

//player info
int dollar[N_MAX_USER];						//dollars that each player has
int n_user;									//number of users


//play yard information
int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];	//cards that currently the players hold
int cardSum[N_MAX_USER];					//sum of the cards
int bet[N_MAX_USER];						//current betting 
int gameEnd = 0; 							//game end flag

int Return;									// receive value of getCardNum()
int multiEachdollar=1;


int main(int argc, char *argv[]) {
	
	int i;
	
	printf("####################\n");
	printf("######blackjack######\n");
	
	printf("####################\n\n");
	
	srand((unsigned)time(NULL));
	
	//set the number of players
	configUser();

	
	//Game initialization --------
	//1. players' dollar
	for(i=0;i<n_user;i++)
	{
		dollar[i]=N_DOLLAR;
	}
	//2. card tray
	mixCardTray();
	

	//Game start --------
	do {
		int i;
		int j;
		
		printf("\n------------------------------------------------\n");
		printf("             ROUND %d (cardIndex:%d)             \n",roundcnt,cardIndex);
		printf("------------------------------------------------\n");
		
		 
		for(i=0;i<n_user+1;i++)
		{
			Cardcnt[i]=2;
		} 
		
		betDollar();
		offerCards(); //1. give cards to all the players
		
		if(gameEnd==1)
		{
			printf("\ncard ran out the tray! finishing the game :(\n");
			break;
		}
		
		printCardInitialStatus();
		printf("\n------------------ GAME start ------------------\n");
		
		
		//my turn
		printf(">>> my turn! -------------\n");
		
		while(1) 
		{	
			
			printUserCardStatus(0,Cardcnt[0]);
			calcStepResult(0,Cardcnt[0]);
			printf("(%d) ",cardSum[0]);
			printf("Action? (0 - go, others - stay) :");
		
			Return = getAction();
			
			if(Return==0)
			{	
				cardhold[0][Cardcnt[0]] = pullCard();
				if(gameEnd==1)
				{
					break;
				}
				
				Cardcnt[0]++;
				calcStepResult(0,Cardcnt[0]);
				
				
				if(cardSum[0]>21)
				{
					printUserCardStatus(0,Cardcnt[0]);
					dollar[0]=dollar[0]-bet[0];
					printf("DEAD (sum:%d) --> -$%d ($%d)\n",cardSum[0],bet[0],dollar[0]);
					break;
				}
				
			
			}
			else if(Return==1) 
			{	
				
				calcStepResult(0,Cardcnt[0]);
				
				if(Cardcnt[0]==2 && cardSum[0]==21)
				{
					printf("blackjack!");
					blackjack[0]=1;
					break;
				}
				break;
			}
						
		}
	
		
		
		//each player's turn
		for (i=1;i<n_user;i++) //each player
		{	
			
			printf("\n>>> player %d turn! -------\n",i);
			while (1)
			{
				printUserCardStatus(i,Cardcnt[i]);
				calcStepResult(i,Cardcnt[i]);
				printf("(%d) ",cardSum[i]);
				
				if(Cardcnt[i]==2 && cardSum[i]==21)
				{
					printf("blackjack!\n");
					blackjack[i]=1;
					break;
				}
				else if(cardSum[i]<N_MAX_GO)
				{
					printf("Go!\n");
					cardhold[i][Cardcnt[i]] = pullCard();
					if(gameEnd==1)
					{
						break;
					}
					Cardcnt[i]++;
					
				}
				else if(cardSum[i]>21)
				{
					dollar[i]=dollar[i]-bet[i];
					printf("DEAD (sum:%d) --> -$%d ($%d)\n",cardSum[i],bet[i],dollar[i]);
					break;
				}
				
				else if(cardSum[i]>=17) 
				{
					printf("Stay!\n");
					
					break;
				}
				
					
			}
			
		}
		
		//server's turn
		printf("\n>>> server turn! ---------\n");
		while (1)
			{
				printUserCardStatus(n_user,Cardcnt[n_user]);
				calcStepResult(n_user,Cardcnt[n_user]);
				printf("(%d) ",cardSum[i]);
				
				if(Cardcnt[n_user]==2 && cardSum[n_user]==21)
				{
					printf("\n[[[[[[[ server result is blackjack! ]]]]]]]\n\n");
					blackjack[n_user]=1;
					break;
				}
				else if(cardSum[n_user]<N_MAX_GO)
				{
					printf("Go!\n");
					cardhold[n_user][Cardcnt[n_user]] = pullCard();
					if(gameEnd==1)
					{
						break;
					}
					Cardcnt[n_user]++;
					
				}
				else if(cardSum[n_user]>21)
				{
					printf("DEAD (sum:%d)\n",cardSum[n_user]);
					printf("[[[[[[[ server result is overflow! ]]]]]]]\n\n");
					break;
				}
				else if(cardSum[n_user]>=N_MAX_GO) 
				{
					printf("Stay!\n");
					
					printf("[[[[[[[ server result is %d! ]]]]]]]\n\n",cardSum[i]);
					break;
				}
				
				
					
			}
		//End game when card ran out the tray!
		
		if(gameEnd==1)
		{
			printf("\ncard ran out the tray! finishing the game :(\n");
			break;
		}
		
	
		
		//result
		
		checkResult();
		
		for(i=0;i<n_user+1;i++) // discard cards each player has
		{
			for(j=0;j<N_MAX_CARDHOLD;j++)
				cardhold[i][j]=N_CARD*N_CARDSET;
		}
		
		for(i=0;i<n_user;i++) // initialization of each player's cardsum
		{
			cardSum[i]=0;
		}
		
		for(i=0;i<n_user+1;i++) // initialization of blackjack status
		{
			blackjack
			[i]=0;
		}
		
		//Endgame when ones go bankrupt
		for(i=0;i<n_user;i++) // multiply each player's dollar[]
		{
			multiEachdollar=multiEachdollar*dollar[i]; 
		}
		
		if(multiEachdollar==0)//one of player's dollar ==0
		{
			
			gameEnd = 1;
		}
		
		if(multiEachdollar==0 && gameEnd ==1)
		{
			printf("\nSomeone went bankrupt!\n");
		}
		
		roundcnt++;
		
		
		
	} while (gameEnd == 0);
	
	checkWinner();
	
	
	return 0;
}

