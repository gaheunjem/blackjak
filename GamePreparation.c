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

extern Cardcnt[N_MAX_USER];

extern CardTray[N_CARDSET*N_CARD];
extern cardIndex;	
						
extern dollar[N_MAX_USER];						
extern n_user;									

extern cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];	
extern cardSum[N_MAX_USER];					
extern bet[N_MAX_USER];						 
extern gameEnd; 	

void swap(int* A, int* B) //used in MixCardTray()
{
    int temp;
 
	temp = *A;
    *A = *B;
	*B = temp;  
}
//used in MixCardTray(), exchange random values from the first value of the array in order
void rndCard(int* CardTray, int size)   
{
    int i; 

 	for(i=0;i<size;i++)
    {
		swap(&CardTray[i],&CardTray[(rand()%(size - i))+i]); 	  
    }
}

//mix the card sets and put in the array
int mixCardTray(void) {
	
	int i;                                             

	srand((unsigned int)time(NULL));    

 	for(i=0;i< N_CARDSET*N_CARD;i++)           
    {
        CardTray[i] = i;
    }

    rndCard(CardTray,N_CARDSET*N_CARD);        
    
    printf("\n");
   
	printf("--> card is mixed and put into the tray\n");
}

//get one card from the tray
int pullCard(void) {
	
	if(cardIndex<N_CARDSET*N_CARD)
	{
		cardIndex++;
	}  
	else if(cardIndex==N_CARDSET*N_CARD)
	{
		gameEnd=1;
	}
	return CardTray[cardIndex-1];
	
}

//betting
int betDollar(void) {
	
	int i;
	do
	{
		if(bet[0]>dollar[0])
		{
			printf("You're short of money :(");
		}
		
		printf("\n-------batting step-------\n");
	
		printf("-> your betting (total:$%d) : ",dollar[0]);
	
		scanf("%d",&bet[0]);
	
	}while(bet[0]>dollar[0]);	
		
	srand((unsigned int)time(NULL));
	

	for (i=1;i<n_user;i++)
	{
		bet[i] = rand()% N_MAX_BET+1;
		printf("-> player%d bets $%d (out of $%d)\n",i,bet[i],dollar[i]);
	}	



}

//offering initial 2 cards   
void offerCards(void) {
	int i,j;
	//give a card for each players and server twice, one by one
	for(i=0;i<=1;i++)
	{
		for(j=0;j<n_user;j++)
			{
				cardhold[j][i]=pullCard();
			}
		cardhold[n_user][i]=pullCard();
	}	
	
	return;
}

//player settiing
int configUser(void) {
	
	
	do
	{
		if(n_user>N_MAX_USER)
		{
			printf("I told you MAX number of players is %d :(\n",N_MAX_USER);
		}
		
		printf("input the number of players (MAX:5) : ");
		scanf("%d",&n_user);
		
	}while(n_user>N_MAX_USER);


}

