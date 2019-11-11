#include <stdio.h>
#include <time.h> 
#include <stdlib.h>
#define N_MAX_USER			5
#define N_MAX_BET			5

	int fund[N_MAX_USER]={50,50,50,50,50};
	int coin[N_MAX_USER];
	int *fc=fund;

void betDollar(int numpy){
	
	printf("\n-------batting step-------\n");
	int coin1;
	

	
	printf("-> your betting (total:$%d) : ",fc[0]);
	scanf("%d", &coin[0]);
	
	srand((unsigned int)time(NULL));
	
	coin[1] = rand()% N_MAX_BET+1;
	coin[2] = rand()% N_MAX_BET+1;
	coin[3] = rand()% N_MAX_BET+1;
	coin[4] = rand()% N_MAX_BET+1;
	
	
	int i;
	for (i=1;i<numpy;i++)
	{
		printf("-> player%d bets $%d (out of $%d)\n",i,coin[i],fc[i]);
	}
	
	
	fc[0] -= coin[0];
	fc[1] -= coin[1];
	fc[2] -= coin[2];
	fc[3] -= coin[3];
	fc[4] -= coin[4];
	

		 
}
