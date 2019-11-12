#include <stdio.h>
#include <time.h> 
#include <stdlib.h>
#define N_CARDSET			1
#define N_CARD				52
#define N_MAX_USER			5
#define N_MAX_CARDHOLD		10


int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];
int Card[N_CARDSET*N_CARD];
int *cd=Card;
 
void swap(int *A, int *B);                  
void rndCard(int* card, int size);   


int mixCardTray()
{
	int Card[N_CARDSET*N_CARD];                     

    int i;                                             

	srand((unsigned int)time(NULL));    

 	for(i=0;i< N_CARDSET*N_CARD;i++)           
    {
        cd[i] = i;
    }

    rndCard(cd,N_CARDSET*N_CARD);        

    for(i=0;i<N_CARDSET*N_CARD;i++)             

    {
        printf("%d ",cd[i]);
    }

    printf("\n");
   
	printf("--> card is mixed and put into the tray");
}   

void getCardNum(int cardnum)
{	

	
}

//print the card information (e.g. DiaA)
void printCard(int cardnum) 
{
	switch(cardnum/13){
	
	case 0:
		printf("HRT");
		break;
	case 1:
		printf("DIA");
		break;
	case 2:
		printf("CLV");
		break;	
	case 3:
		printf("SPD");
		break;
}
	
	if(cardnum%13==1)
		printf("Ace");
	else if(cardnum%13==2)
		printf("2");	
	else if(cardnum%13==3)
		printf("3");
	else if(cardnum%13==4)
		printf("4");
	else if(cardnum%13==5)
		printf("5");	
	else if(cardnum%13==6)
		printf("6");
	else if(cardnum%13==7)
		printf("7");
	else if(cardnum%13==8)
		printf("8");
	else if(cardnum%13==9)
		printf("9");
	else if(cardnum%13==10)
		printf("10");	
	else if(cardnum%13==11)
		printf("Jack");
	else if(cardnum%13==12)
		printf("Queen");
	else 
		printf("King");
		
							
}


int PRINT()
{	
	int i;
	for(i=0;i<52;i++){
	
		printCard(cd[i]);
		printf("\n");
	}
}


int pullCard()
{
	return Card[rand()%52];//?? 
}


void offerCards(void) {
	
	int n_user;
	int i;
	//1. give two card for each players
	for (i=0;i<n_user;i++)
	{
		cardhold[i][0] = pullCard();
		cardhold[i][1] = pullCard();
	}
	//2. give two card for the operator
	cardhold[n_user][0] = pullCard();
	cardhold[n_user][1] = pullCard();
	
}

void printCardInitialStatus(void) {
	
}

void rndCard(int* card, int size)   
{
    int i; 

 	for(i=0; i<size;i++)
    {
		swap(&card[i],&card[(rand() % (size - i)) + i]);   
    }
}

 
void swap(int* A, int* B)
{
    int temp;
 
	temp = *A;
    *A = *B;
	*B = temp;  
}




