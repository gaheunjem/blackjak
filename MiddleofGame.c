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
extern blackjak[N_MAX_USER];
extern winner[N_MAX_USER];
extern win;

extern cardorder;
extern Cardcnt[N_MAX_USER];

//card tray object
extern CardTray[N_CARDSET*N_CARD];
extern cardIndex;	
						

//player info
extern dollar[N_MAX_USER];						//dollars that each player has
extern n_user;									//number of users


//play yard information
extern cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];	//cards that currently the players hold
extern cardSum[N_MAX_USER];					//sum of the cards
extern bet[N_MAX_USER];						//current betting 
extern gameEnd;

int getIntegerInput(void) {
    
	int input, num;
    
    num = scanf("%d", &input);
    fflush(stdin);
    if (num != 1) //if it fails to get integer
        input = -1;
    
    return input;
}

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
		return 10;
			
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
			return 0;
		}		
	else if(input!=0)
		{
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

// calculate the card sum and see if : 1. under 21, 2. over 21, 3. blackjack
int calcStepResult(int user,int cardcnt) {	
	
	int i;
	int sum=0;
	int NumA=0;
	
	for(i=0;i<cardcnt;i++)
	{
		if(getCardNum(cardhold[user][i])!=11)
		{
			sum+=getCardNum(cardhold[user][i]);
		}
		else if(getCardNum(cardhold[user][i])==11)
		{
			NumA++;
		}
	}
	
	if(cardSum[user]==10)
	{
		if(NumA==1)
		{
			sum=sum+11;
		}
		else if(NumA>1)
		{
			sum=sum+NumA;
		}
	}
	else if(cardSum[user]>10)
	{
		if(NumA>0)
		{
			sum=sum+NumA;
		}
	}
	else if(cardSum[user]<10)
	{
		if(NumA==1)
		{
			sum=sum+11;
		}
		else if(NumA>1)
		{
			sum=sum+11+(NumA-1);
		}
	}
	
 	cardSum[user]=sum;
 	
 	return 0;
}


