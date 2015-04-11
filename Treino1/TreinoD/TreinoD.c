#include <stdio.h>
#include <stdlib.h>

#define MAX 21


typedef struct {

	char palavra[MAX];
	int analisado;

}lista;

lista palavras[MAX],
	  resultado[MAX];

int	numero_palavras,
	numero_letras,
	mudou[MAX];


void printf_lista()
{
	int i;
	for(i = 0 ; i < numero_palavras ; i++)
	{
		printf("%s\n",palavras[i].palavra);
	}
}

void limpa()
{
	int i;
	for(i = 0 ; i < numero_letras ; i++)
	{
		mudou[i] = 0;
	}
}

void morphe()
{
	int j,k,
		contador = 0,
		todo_analisado = 1,
		indice = 0;

	printf("%s\n",palavras[0].palavra);
	while(todo_analisado < numero_palavras)
	{
		/** Estou na palavra palavras[i] **/
		for(j = 0 ; j < numero_palavras ; j++)
		{
			if(palavras[j].analisado == 0)
			{
				for(k = 0 ; k < numero_letras ; k++)
				{
					if(palavras[indice].palavra[k] != palavras[j].palavra[k])
					{
						contador++;
					}
				}

				if(contador == 1)
				{

					todo_analisado++;
					printf("%s\n",palavras[j].palavra);
					palavras[j].analisado = 1;
					break;
				}
				contador = 0;
			}
		}
		indice = j;
	
	}	


}

int main()
{
	int i;

	while(scanf("%d %d",&numero_palavras,&numero_letras) != EOF)
	{
		limpa();
		for(i = 0 ; i < numero_palavras ; i++)
		{
			scanf(" %[^\n]", palavras[i].palavra);
			palavras[i].analisado = 0;
		}

		morphe();

		numero_palavras = 0;
		numero_letras = 0;
	}

	return 0;

}

