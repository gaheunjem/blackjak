#include <stdio.h>
#include <time.h> 
#include <stdlib.h>
#define N_CARDSET			1
#define N_CARD				52

void swap(int*A,int*B)
{
	int temp;
	
	temp =*A;
	*A=*B;
	*B=temp;
}

void randomCard(int*card, int CARDSIZE)
{
	int i;
	
	for(i=0;i<CARDSIZE;i++)
	{
		swap(&card[i],&card[rand()%51+i]);
	}
}
	
int PrintCard(int n)
{
	
}


void mixCardTray()
{
	
	int Card[52];
	int i;
	
	srand((unsigned int)time(NULL));
	
	for(i=0;i<52;i++)
	{
		Card[i]=i;
	}
	
	randomCard(Card,52);
	
	for(i=0;i<52;i++)
	{
	printf("%d\n",Card[i]);
	}
	
	printf("--> card is mixed and put into the tray");
	
	
}

 	
	

void offerCard()
{
	
}
