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


extern gameEnd;
extern Cardcnt[N_MAX_USER];
extern cardSum[N_MAX_USER];
extern cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];
extern n_user;
int roundcnt=1;
extern bet[N_MAX_USER];
extern dollar[N_MAX_USER];
extern blackjak[N_MAX_USER];
extern cardIndex;
extern cardorder;
int Return;
int multiEachdollar=1;


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
	
	
	
	for(i=0;i<n_user;i++)
	{
		dollar[i]=N_DOLLAR;
	}
	

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
					printf(" DEAD (sum:%d) --> -$%d ($%d)\n",cardSum[0],bet[0],dollar[0]);
					break;
				}
				
			
			}
			else if(Return==1) 
			{	
				
				calcStepResult(0,Cardcnt[0]);
				if(Cardcnt[0]==2 && cardSum[0]==21)
				{
					printf("Blackjak!");
					blackjak[0]=1;
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
				
				if(Cardcnt[i]==2 && cardSum[i]==21)
				{
					printf("Blackjak!\n");
					blackjak[i]=1;
					break;
				}
				else if(cardSum[i]<17)
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
					printf(" DEAD (sum:%d) --> -$%d ($%d)\n",cardSum[i],bet[i],dollar[i]);
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
				
				if(Cardcnt[n_user]==2 && cardSum[n_user]==21)
				{
					printf("\n[[[[[[[ server result is blackjak! ]]]]]]]\n\n");
					blackjak[n_user]=1;
					break;
				}
				else if(cardSum[n_user]<17)
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
					printf(" DEAD (sum:%d)\n",cardSum[n_user]);
					printf("[[[[[[[ server result is overflow! ]]]]]]]\n\n");
					break;
				}
				else if(cardSum[n_user]>=17) 
				{
					printf("Stay!\n");
					
					printf("[[[[[[[ server result is %d! ]]]]]]]\n\n",cardSum[i]);
					break;
				}
				
				
					
			}
		//End game
		
		for(i=0;i<n_user;i++)
		{
			multiEachdollar=multiEachdollar*dollar[i]; 
		}
		
		if(multiEachdollar==0)
		{
			
			gameEnd = 1;
		}
		
		if(multiEachdollar==0 && gameEnd ==1)
		{
			printf("someone went bankrupt!\n");
		}
		
		if(gameEnd==1)
		{
			printf("\ncard ran out the tray! finishing the game :(\n");
			break;
		}
		
	
		
		//result
		
		checkResult();
		
		for(i=0;i<n_user+1;i++)
		{
			for(j=0;j<N_MAX_CARDHOLD;j++)
				cardhold[i][j]=N_CARD*N_CARDSET;
		}
		
		for(i=0;i<n_user;i++)
		{
			cardSum[i]=0;
		}
		
		for(i=0;i<n_user+1;i++)
		{
			blackjak[i]=0;
		}
		
		roundcnt++;
		cardIndex=cardorder;
		
		
	} while (gameEnd == 0);
	
	checkWinner();
	
	
	return 0;
}

