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
char ncard;//card number
char scard[4];//card shape

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

	if(cardnum%13==1)
		ncard = 'A';
	else if(cardnum%13==2) 
		ncard = '2';
	else if(cardnum%13==3) 
		ncard = '3';
	else if(cardnum%13==4) 
		ncard = '4';
	else if(cardnum%13==5) 
		ncard = '5';
	else if(cardnum%13==6) 
		ncard = '6';
	else if(cardnum%13==7) 
		ncard = '7';
	else if(cardnum%13==8) 
		ncard = '8';
	else if(cardnum%13==9) 
		ncard = '9';
	else if(cardnum%13==10) 
		ncard = '10';
	else if(cardnum%13==11) 
		ncard = 'J';
	else if(cardnum%13==12) 
		ncard = 'K';
	else  
		ncard = 'Q';
		
	
	if(cardnum%4==1) 
		strcpy(scard,"HRT");
	else if(cardnum%4==2) 
		strcpy(scard,"DIA");
	else if(cardnum%4==3) 
		strcpy(scard,"CLV");	
	else  
		strcpy(scard,"SPD");//??		
	
	
}

//print the card information (e.g. DiaA)
void printCard(int cardnum) 
{
	getCardNum(cd[cardnum]);
	printf("%s%c\n",scard,ncard);
}

int pullCard()
{
	return Card[rand()%52];//?? 
}


/*void offerCards(void) {
	
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
	
}*/
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




