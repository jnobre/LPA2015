
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10000



int mapa[MAX][MAX];

int tamanho_arvore;

int minimizar()
{

	int i,j;

	for(i = tamanho_arvore - 2; i >= 0 ; i--)
	{
		for(j = 0 ; j <= i ; j++)
		{		
			if(mapa[i][j] != -1)
			{
				if(mapa[i + 1][j] == -1 && mapa[i + 1][j + 1] != -1)
				{
					mapa[i][j] += mapa[i + 1][j + 1];
					continue;
				}
				else if(mapa[i + 1][j] != -1 && mapa[i + 1][j + 1] == -1)
				{
					mapa[i][j] += mapa[i + 1][j];
					continue;
				}
				else if(mapa[i + 1][j] == -1 && mapa[i + 1][j + 1] == -1)
				{
					mapa[i][j] = -1;
					continue;
				}
				else
					mapa[i][j] += mapa[i + 1][j] < mapa[i + 1][j + 1] ? mapa[i + 1][j] : mapa[i + 1][j + 1];
			}
		}
	}

	return mapa[0][0];
}



int main()
{
	int j,k,resultado;

	while(scanf("%d",&tamanho_arvore) != EOF)
	{		
		for(j = 0 ; j < tamanho_arvore ; j++)
		{
			for(k = 0 ; k <= j ; k++)
			{
				scanf("%d",&mapa[j][k]);		
			}
		}
		
		resultado = minimizar();
		if(resultado == -1)
			printf("no way!\n");
		else
			printf("%d\n",resultado);

		memset(mapa,0,sizeof(int)*(tamanho_arvore)*(tamanho_arvore));
		resultado = 0;

	}

	return 0;
	
}


