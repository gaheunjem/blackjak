#include <stdio.h>
#include <stdlib.h>
#define N_CARDSET			1
#define N_CARD				52
#define N_MAX_USER	5

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
extern int Card[N_CARDSET*N_CARD];

int main(void) {
	
	int n_user;
	int start;
	
	printf("####################\n");
	printf("######BLACKJAK######\n");
	printf("####################\n\n");
	
	printf("input the number of players (MAX:5) : ");

	scanf("%d",&n_user);
	
	mixCardTray();
	
	betDollar(n_user);
	
	PRINT();
	
		
	
	
	
	
	
	
	
	
	return 0;
}


	

