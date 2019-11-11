#include <stdio.h>
#include <stdlib.h>
#define N_CARDSET			1
#define N_CARD				52
#define N_MAX_USER	5

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
extern int Card[N_CARDSET*N_CARD];

int main(void) {
	
	int numpy;
	int start;
	
	printf("####################\n");
	printf("######BLACKJAK######\n");
	printf("####################\n\n");
	
	printf("input the number of players (MAX:5) : ");

	scanf("%d",&numpy);
	
	mixCardTray();
	
	betDollar(numpy);
	betDollar(numpy);

	int i;
	
	for(i=0;i<52;i++)
		printCard(i);
	
		
	
	
	
	
	
	
	
	
	return 0;
}


	

