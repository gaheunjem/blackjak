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

extern roundcnt;
extern blackjack[N_MAX_USER];
extern winner[N_MAX_USER];
extern win;

extern cardorder;
extern Cardcnt[N_MAX_USER];

extern CardTray[N_CARDSET*N_CARD];
extern cardIndex;	
						
extern dollar[N_MAX_USER];						
extern n_user;									

extern cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];	
extern cardSum[N_MAX_USER];					
extern bet[N_MAX_USER];						 
extern gameEnd;


int checkResult() {
	printf("\n---------------- ROUND %d result ----------------\n",roundcnt);
	//my result 
	printf("  -> your result : ");
		 
		if(cardSum[0]<=21&&cardSum[n_user]<=21)
		{
			if(cardSum[0]>=cardSum[n_user]) 
				{ 
				printf("win!\n");
				dollar[0]=dollar[0]+bet[0];
				printf("(sum:%d) --> +$%d ($%d)\n",cardSum[0],bet[0],dollar[0]);
				}
			else if(cardSum[0]<cardSum[n_user])
			{
				printf("lose!\n");
				dollar[0]=dollar[0]-bet[0];
				printf("(sum:%d) --> -$%d ($%d)\n",cardSum[0],bet[0],dollar[0]);	
			}
			else if(blackjack[n_user]==1)
			{	
				if(blackjack[0]!=1)
				{
					printf("lose!\n");
					dollar[0]=dollar[0]-bet[0];
					printf("(sum:%d) --> -$%d ($%d)\n",cardSum[0],bet[0],dollar[0]);	
				}
				else if(blackjack[0]==1)
				{
					printf("win!\n");
					dollar[0]=dollar[0]+bet[0];
					printf("(sum:%d) --> +$%d ($%d)\n",cardSum[0],bet[0],dollar[0]);
				}
			}
		}	
		else if(cardSum[0]>21)
		{
			printf("lose due to overflow!\n");
			printf("(sum:%d)\n",cardSum[0]);
		}
		else if(cardSum[n_user]>21)
		{
			if(cardSum[0]<=21)
			{
				printf("win!\n");
				dollar[0]=dollar[0]+bet[0];
				printf("(sum:%d) --> +$%d ($%d)\n",cardSum[0],bet[0],dollar[0]);
			}
			else if(cardSum[0]>21)
			{
				printf("lose due to overflow!\n");	
				printf("(sum:%d)\n",cardSum[0]);
			}
			
		}	
	//players result
	int i;
	for(i=1;i<n_user;i++)
	{
		printf("  -> %d'th player's result :",i);
		 
		if(cardSum[i]<=21&&cardSum[n_user]<=21)
		{
			if(cardSum[i]>=cardSum[n_user]) 
			{ 
				printf("win!\n");
				dollar[i]=dollar[i]+bet[i];
				printf("(sum:%d) --> +$%d ($%d)\n",cardSum[i],bet[i],dollar[i]);
			}
			else if(cardSum[i]<cardSum[n_user])
			{
				printf("lose!\n");
				dollar[i]=dollar[i]-bet[i];
				printf("(sum:%d) --> -$%d ($%d)\n",cardSum[i],bet[i],dollar[i]);
			}
			else if(blackjack[n_user]==1)
			{	
				if(blackjack[i]!=1)
				{
					printf("lose!\n");
					dollar[i]=dollar[i]-bet[i];
					printf("(sum:%d) --> -$%d ($%d)\n",cardSum[i],bet[i],dollar[i]);	
				}
				else if(blackjack[i]==1)
				{
					printf("win!\n");
					dollar[i]=dollar[i]+bet[i];
					printf("(sum:%d) --> +$%d ($%d)\n",cardSum[i],bet[i],dollar[i]);
				}
			}
		}
		else if(cardSum[n_user]>21)
		{
			if(cardSum[i]<=21)
			{
				printf("win!\n");
				dollar[i]=dollar[i]+bet[i];
				printf("(sum:%d) --> +$%d ($%d)\n",cardSum[i],bet[i],dollar[i]);
			}
			else if(cardSum[i]>21)
			{
				printf("lose due to overflow!\n");	
				printf("(sum:%d)\n",cardSum[i]);
			}
			
		}
		else if(cardSum[i]>21)
		{
			printf("lose due to overflow!\n");
			printf("(sum:%d)\n",cardSum[i]);
		}
		
		
	
	}	

}

int checkWinner() {
	
	printf("\n\n----------------------------------------------\n\n");
	printf("----------------------------------------------\n\n");
	printf("----------------------------------------------\n\n");
	printf("----------------------------------------------\n\n");
	
	printf("game end! your money :$%d, players's money :",dollar[0]);
	
	int i;
	int j;
	
	for(i=1;i<n_user;i++)//print each player's money result
	{
		printf("$%d ",dollar[i]);
	}
	
	printf("\n");

	for(i=0;i<n_user;i++)//initialize money ranking status
	{
		winner[i]=1;
	}
	
	/* decide money ranking ex) winner[]={1,2,3}
								=> <money ranking>
								 	1. me
								 	2. player 1
								 	3. player 3*/
	for(i=0;i<n_user;i++)
	{
		for(j=i+1;j<n_user;j++)
		{
			if(dollar[i]>dollar[j])
			{
				winner[j]++;	
			}
			else if(dollar[i]<dollar[j])
			{
				winner[i]++;	
			}	
		}	
	}	
	// check who win first place on moneyranking
	for(i=0;i<n_user;i++)
	{
		win=i;
		
		if(winner[i]==1)
			break;
	}
	
	if(win==0)
	{
		printf("\nYou win!\n");
	}	
	else
	{
		printf("\nplayer %d's win!\n",win);
			
	}
	
}




