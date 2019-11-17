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
int Cardcnt[N_MAX_USER];
extern cardSum[N_MAX_USER];
extern cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];
extern n_user;
int roundcnt=1;
extern bet[N_MAX_USER];
extern dollar[N_MAX_USER];
extern blackjak[N_MAX_USER];

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
		 
		for(i=0;i<n_user;i++)
		{
			Cardcnt[i]=2;
		} 
		
		betDollar();
		offerCards(); //1. give cards to all the players
		
		printCardInitialStatus();
		printf("\n------------------ GAME start --------------------------\n");
		
		
		//my turn
		printf(">>> my turn! -------------\n");
		
		while(1)
		{	
			printUserCardStatus(0,Cardcnt[0]);
			
			if(getAction()==0)
			{	
				calcStepResult(0,Cardcnt[0]);
					if(cardSum[0]>21)
				{
					dollar[0]=dollar[0]-bet[0];
					printf(" DEAD (sum:%d) --> -$%d ($%d)\n",cardSum[0],bet[0],dollar[0]);
					break;
				}	
			}
			else if(getAction()==1)//something wrong 
			{	
				
				if(Cardcnt[n_user]==1 && cardSum[n_user]==21)
				{
					printf("Blackjak!");
					blackjak[0]=1;
				}
				printf("why why");
				calcStepResult(0,Cardcnt[0]);
				break;
			}
						
		}
	
		
		printf("\n");
		//each player's turn
		for (i=1;i<n_user;i++) //each player
		{	
			
			printf(">>> player %d turn! -------\n",i);
			while (1)
			{
				printUserCardStatus(i,Cardcnt[i]);
				calcStepResult(i,Cardcnt[i]);
				
				if(Cardcnt[n_user]==1 && cardSum[n_user]==21)
				{
					printf("Blackjak!");
					blackjak[i]=1;
					break;
				}
				else if(cardSum[i]<17)
				{
					printf("Go!\n");
					cardhold[i][Cardcnt[i]] = pullCard();
					Cardcnt[i]++;
					printf("%d\n",cardSum[i]);
				}
				else if(getCardNum()==11 && cardSum[i]>21)
				{
					cardSum[i]=cardSum[i]-10;
					
					if(cardSum[i]>21)
						printf(" DEAD (sum:%d)",cardSum[n_user]);
						break;
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
					printf("%d\n",cardSum[i]);
					break;
				}
					
			}
			
		}
		
		//server's turn
		printf(">>> server turn! ----------\n");
		while (1)
			{
				printUserCardStatus(n_user,Cardcnt[n_user]);
				calcStepResult(n_user,Cardcnt[n_user]);
				
				if(Cardcnt[n_user]==1 && cardSum[n_user]==21)
				{
					printf("Blackjak!");
					blackjak[n_user]=1;
					break; 
				}
				else if(getCardNum()==11 && cardSum[i]>21)
				{
					cardSum[i]=cardSum[i]-10;
					
					if(cardSum[i]>21)
						printf(" DEAD (sum:%d)",cardSum[n_user]);
						break;
				}
				else if(cardSum[n_user]<17)
				{
					printf("Go!\n");
					cardhold[n_user][Cardcnt[n_user]] = pullCard();
					Cardcnt[n_user]++;
					printf("%d\n",cardSum[n_user]);
				}
				else if(cardSum[n_user]>21)
				{
					printf(" DEAD (sum:%d)\n",cardSum[n_user]);
					break;
				}
				else if(cardSum[i]>=17) 
				{
					printf("Stay!\n");
					printf("%d\n",cardSum[i]);
					break;
				}
				
					
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
		
		roundcnt++;
		
	} while (gameEnd == 0);
	
	checkWinner();
	
	
	return 0;
}

