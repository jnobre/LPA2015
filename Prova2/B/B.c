
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10000



int mapa[MAX][MAX];

int tamanho_arvore;

int maximizar()
{

	int i,j;

	for(i = tamanho_arvore - 2; i >= 0 ; i--)
	{
		for(j = 0 ; j <= i ; j++)
		{		
			mapa[i][j] += mapa[i + 1][j] > mapa[i + 1][j + 1] ? mapa[i + 1][j] : mapa[i + 1][j + 1];
		}
	}

	return mapa[0][0];
}

int main()
{
	int j,k;

	while(scanf("%d",&tamanho_arvore) != EOF)
	{		
		for(j = 0 ; j < tamanho_arvore ; j++)
		{
			for(k = 0 ; k <= j ; k++)
			{
				scanf("%d",&mapa[j][k]);		
			}
		}
		
		printf("%d\n",maximizar());
		memset(mapa,0,sizeof(int)*(tamanho_arvore)*(tamanho_arvore));

	}

	return 0;
	
}


