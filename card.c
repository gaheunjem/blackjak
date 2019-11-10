#include <stdio.h>
#include <time.h> 
#include <stdlib.h>


 



void CardTray()
{
	
	
	int cardnum[]={'A','2','3','4','5','6','7','8','9','10','J','Q','K',
	'A','2','3','4','5','6','7','8','9','10','J','Q','K',
	'A','2','3','4','5','6','7','8','9','10','J','Q','K',
	'A','2','3','4','5','6','7','8','9','10','J','Q','K'};
	int cardshape[] = {'H','S','C','D','H','S','C','D','H','S','C','D','H','S','C','D'
	,'H','S','C','D','H','S','C','D','H','S','C','D','H','S','C','D','H','S','C','D'
	,'H','S','C','D','H','S','C','D','H','S','C','D','H','S','C','D'};
	
	srand(time(NULL));
	
	int temp1;
	int rn1;
	int i;
	for (i=0;i<52;i++)
	{
		rn1 = rand()% 52;
		temp1 = cardnum[i];
		cardnum[i] = cardnum[rn1];
		cardnum[rn1] = temp1;
	}
	// switch array order 
	int temp2;
	int rn2;
	int j;
	
	for (j=0;j<52;j++)
	{
		rn2 = rand()% 52;
		temp2 = cardshape[j];
		cardshape[j] = cardshape[rn2];
		cardshape[rn2] = temp2;
	}
	
	printf ("%c%c",cardshape[1],cardnum[1]);
	
	
	
	
}
