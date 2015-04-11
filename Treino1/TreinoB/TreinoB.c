#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 150

/** ( -> 40 ; ) -> 41 ; [ -> 91 ; ] -> 93 **/

char string[MAX],
	paren[MAX];


int contador = 0,
	resposta = 0,
	tamanho_string = 0;

int construir_candidatos(char caracter)
{
	int i;
	for(i = 0 ; i < contador ; i++)
	{
		if(paren[i] == caracter)
			return 1;
	}

	return 0;

}


void verifica_lexico()
{
	int i,j,controlador;

	for(i = 0 ; i < tamanho_string ; i++)
	{
		if(string[i] == 40 || string[i] == 91)
		{
			/*printf("%d ",string[i]);*/
			paren[contador] = string[i];
			contador++;

		}
		else if(string[i] == 41)
		{
			if(contador == 0)
			{
				contador = -1;
				break;
			}
			for( j = 0 ; j < contador ; j++)
			{
				if(paren[j] == 40)
				{
					controlador = 1;
				}

			}
			if(controlador)
			{	
				contador--;
			}
			else
			{
				break;
			}
			
		}
		else
		{
			if(contador == 0)
			{
				contador = -1;
				break;
			}
			for( j = 0 ; j < contador ; j++)
			{
				if(paren[j] == 91)
				{
					controlador = 1;
				}
			}
			if(controlador)
			{	
				contador--;
			}
			else
			{
				break;
			}

		}
		controlador = 0;
	}
}


int main(void)
{
	int i,
		numero_strings = 0;

	scanf("%d",&numero_strings);

	for(i = 0 ; i < numero_strings ; i++)
	{
		scanf("%s",string);
		
		tamanho_string = strlen(string);
		verifica_lexico();
		if(contador == 0)
			printf("Yes\n");
		else
			printf("No\n");
		
		contador = 0;
		tamanho_string = 0;
		resposta = 0;
	}

	return 0;
	
}

