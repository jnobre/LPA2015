/* Treino A 2015 */
#include <stdio.h>
#include <stdlib.h>

#define Cavaleiro 30
#define MAX 200
#define TAB 400

int numero_cavaleiro,
	movimentos,
	tabuleiro[TAB][TAB];

void init(void)
{
	int i,j;

	for(i = 0 ; i < TAB ; i++)
		for(j = 0 ; j < TAB ; j++)
		{
			tabuleiro[i][j] = 0;
		}
}

int verifica_posicao(int x, int y, int possiveis)
{
	int local = 0;

	if(tabuleiro[x][y] == 1)
		local = 0;
	else
		local = 1;

	tabuleiro[x][y] = 1;

	if(possiveis == movimentos)
		return local;
	else
	{
		return local + verifica_posicao(x-2,y+1,possiveis+1)+
		verifica_posicao(x-2,y-1,possiveis+1)+
		verifica_posicao(x-1,y-2,possiveis+1)+
		verifica_posicao(x+1,y-2,possiveis+1)+
		verifica_posicao(x+2,y-1,possiveis+1)+
		verifica_posicao(x+2,y+1,possiveis+1)+
		verifica_posicao(x+1,y+2,possiveis+1)+
		verifica_posicao(x-1,y+2,possiveis+1);
	}
}

int main(void)
{
	int i,x,y,
		resultado = 0;

	while(scanf("%d",&numero_cavaleiro) != EOF)
	{
		init();
		resultado = 0;
		for(i = 0 ; i < numero_cavaleiro ; i++)
		{
			scanf("%d %d %d",&x,&y,&movimentos);
			x = x + TAB/2;
			y = TAB/2 - y;
			resultado += verifica_posicao(x,y,0);
		}
		printf("%d\n",resultado);
	}

	return 0;
}
