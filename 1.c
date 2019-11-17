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

extern roundcnt;
int blackjak[N_MAX_USER];

int cardorder=0;
int Cardcnt[N_MAX_USER];

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

//some utility functions

//get an integer input from standard input (keyboard)
//return : input integer value
//         (-1 is returned if keyboard input was not integer)
int getIntegerInput(void) {
    
	int input, num;
    
    num = scanf("%d", &input);
    fflush(stdin);
    if (num != 1) //if it fails to get integer
        input = -1;
    
    return input;
}

void swap(int* A, int* B) {//used in MixCardTray()
    int temp;
 
	temp = *A;
    *A = *B;
	*B = temp;  
}

void rndCard(int* CardTray, int size) //used in MixCardTray()  
{
    int i; 

 	for(i=0;i<size;i++)
    {
		swap(&CardTray[i],&CardTray[(rand()%(size - i))+i]); 	  
    }
}

 
//card processing functions ---------------

//calculate the actual card number in the blackjack game
int getCardNum(int cardnum) {
	
	
	if(cardnum%13==1)
		return 11; 
	else if(cardnum%13==2)
		return 2;	
	else if(cardnum%13==3)
		return 3;
	else if(cardnum%13==4)
		return 4;
	else if(cardnum%13==5)
		return 5;	
	else if(cardnum%13==6)
		return 6;
	else if(cardnum%13==7)
		return 7;
	else if(cardnum%13==8)
		return 8;
	else if(cardnum%13==9)
		return 9;
	else if(cardnum%13==10)
		return 10;	
	else if(cardnum%13==11)
		return 10;
	else if(cardnum%13==12)
		return 10;
	else if(cardnum%13==0)
		{
			if(cardnum==N_CARDSET*N_CARD)
				return 0;
			else
			    return 10;
		}
		
		
	
}

//print the card information (e.g. DiaA)
void printCard(int cardnum) {
	
	switch(cardnum/(N_CARDSET*13)){
	
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


//card array controllers -------------------------------

//mix the card sets and put in the array
int mixCardTray(void) {
	
	int i;                                             

	srand((unsigned int)time(NULL));    

 	for(i=0;i< N_CARDSET*N_CARD;i++)           
    {
        CardTray[i] = i;
    }

    rndCard(CardTray,N_CARDSET*N_CARD);        

//    for(i=0;i<N_CARDSET*N_CARD;i++)             
//
//    {
//        printf("%d ",CardTray[i]);
//    }

    printf("\n");
   
	printf("--> card is mixed and put into the tray\n");
}

//get one card from the tray
int pullCard(void) {
	
   	cardorder++;	
	
	return CardTray[cardorder-1];
}


//playing game functions -----------------------------

//player settiing
int configUser(void) {
	
	printf("input the number of players (MAX:5) : ");

	scanf("%d",&n_user);
}


//betting
int betDollar(void) {
	
	int i;
	
	printf("\n-------batting step-------\n");
	
	printf("-> your betting (total:$%d) : ",dollar[0]);
	
	scanf("%d",&bet[0]);
	
	srand((unsigned int)time(NULL));
	

	for (i=1;i<n_user;i++)
	{
		bet[i] = rand()% N_MAX_BET+1;
		printf("-> player%d bets $%d (out of $%d)\n",i,bet[i],dollar[i]);
	}


}


//offering initial 2 cards / 한 사람당 한 장씩 두 번 나눠주는 걸로 바꿔 
void offerCards(void) {
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
	
	return;
}

//print initial card status
void printCardInitialStatus(void) {
	
	int i;
	
	printf("----------- CARD OFFERING ---------------\n");
	
	printf("--- server      : X ");
	printCard(cardhold[n_user][1]);
	printf("\n");
	
	printf("  -> you        : ");
	printCard(cardhold[0][0]);
	printf(" ");
	printCard(cardhold[0][1]);
	printf("\n");
	
	for(i=1;i<n_user;i++)
	{	
		printf("  -> player %d   : ",i);
		printCard(cardhold[i][0]);
		printf(" ");
		printCard(cardhold[i][1]); 
		printf("\n");		 
	}
		
	
}

int getAction(void) {
	
	int input;
	
	input = getIntegerInput();
	
	if(input==0)
		{
			
			cardhold[0][Cardcnt[0]] = pullCard();
			Cardcnt[0]++;
			
			
			
			return 0;
		}		
	else
		{
			calcStepResult(0,Cardcnt[0]);
			return 1;	
		}
}


void printUserCardStatus(int user, int cardcnt) {
	int i;
	
	printf("   -> card : ");
	for (i=0;i<cardcnt;i++)
		{
			printCard(cardhold[user][i]);
			printf(" ");	
		}
	
	printf("\t ::: ");
}

//*A 1or11 생각
// calculate the card sum and see if : 1. under 21, 2. over 21, 3. blackjack
int calcStepResult(int user,int cardcnt) {	
	
	int i;
	int sum=0;
	
	for(i=0;i<cardcnt;i++)
	{
	sum+=getCardNum(cardhold[user][i]);//카드 수만큼 실제 숫자 더하기	
	}	
	
 	cardSum[user]=sum;
}

int checkResult() {
	printf("-------------------- ROUND %d result ....\n",roundcnt);
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
				printf("lose!\n");
				dollar[i]=dollar[i]-bet[i];
				printf("(sum:%d) --> -$%d ($%d)\n",cardSum[i],bet[i],dollar[i]);
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
	
}




