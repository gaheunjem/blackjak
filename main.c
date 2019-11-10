#include <stdio.h>
#include <stdlib.h>

#define N_MAX_USER	5

/* run this program using the console pauser or add your own getch, system("pause") or input loop */


int main(void) {
	
	int numpy;
	int start;
	
	printf("######blackjak######\n");
	printf("enter 1 to start game\n");
	scanf("%d",&start);
	if(start==1)
	{
		printf("enter number of player(1~5): ");
	}
	
	scanf("%d",&numpy);
	
	
	bat(numpy);
	
	
	
	
	
	
	
	
	
	return 0;
}


	

