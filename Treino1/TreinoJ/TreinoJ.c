/* Treino J 2015 */
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int sticks[MAX],
	num_sticks,
	contador_somas,
	total,
	usados[MAX],
	valores[MAX][MAX];



int verifica_quad(int lado1, int lado2, int lado3, int lado4, int indice)
{

	if( (indice == num_sticks) && (lado1 == lado2) && (lado2 == lado3) && (lado3 == lado4) && (indice != 0))
		return 1;
	else if(indice < num_sticks)
	{
		if(lado1+sticks[indice] < total + 1)
			if(verifica_quad(lado1+sticks[indice], lado2, lado3, lado4, indice+1) == 1) 
					return 1;

		if(lado2+sticks[indice] < total + 1)
			if(verifica_quad(lado1, lado2+sticks[indice], lado3, lado4, indice+1) == 1) 
					return 1;

		if(lado3+sticks[indice] < total + 1)
			if(verifica_quad(lado1, lado2, lado3+sticks[indice], lado4, indice+1) == 1) 
					return 1;

		if(lado4+sticks[indice] < total + 1)
			if(verifica_quad(lado1, lado2, lado3, lado4+sticks[indice], indice+1) == 1) 
					return 1;
	}

	return 0;

}


int main()
{

	int i,j,num_testes;


	scanf("%d",&num_testes);

	for(i = 0 ; i < num_testes ; i++)
	{
		contador_somas = 0;
		total = 0;
		scanf("%d", &num_sticks);
		for(j=0 ; j < num_sticks ; j++)
        {
            scanf("%d", &sticks[j]);
            total += sticks[j];
        }
		
	
		if(total%4 != 0)
		{
			printf("no\n");
			continue;
		}

		total /=4;

		if(verifica_quad(0,0,0,0,0) == 1)
			printf("yes\n");
		else
			printf("no\n");

	}

	return 0;

}


