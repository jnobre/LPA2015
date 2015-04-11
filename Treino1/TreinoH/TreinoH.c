/** Treino H 2015 **/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 100
#define MAX 200
#define MAX_STR 300

typedef struct {

	int	ligacao_0,
		ligacao_1;
	char estado_final;

}estados;

estados automato[MAX];
int conta_caminhos = 0,
	tamanho_cadeia = 0,
	numero_estados = 0,
	calculos_aux[MAX][MAX_STR],
	contador = 0;


int estado_aceitador(numero_niveis,id_automato)
{		

	if(calculos_aux[id_automato][numero_niveis] != -1)
	{
		/** Esta em cache? **/
		return calculos_aux[id_automato][numero_niveis];
	}
	else if(numero_niveis >= tamanho_cadeia)
	{

		/** Caso Base de o nivel == ao tamanho da suposta cadeia**/
		if(automato[id_automato].estado_final == 49)
		{

			calculos_aux[id_automato][numero_niveis] = 1;
			conta_caminhos++;
			return 1;
		} 
	}
	else
	{
		/** Caso Recursivo **/	
		int p0 = 0,
			p1 = 0;

		p0 = estado_aceitador(numero_niveis+1,automato[id_automato].ligacao_0-1);

		p1 = estado_aceitador(numero_niveis+1,automato[id_automato].ligacao_1-1);	

		calculos_aux[id_automato][numero_niveis] = p0+p1;

		return p0 + p1;
	}

	return 0;

}

void initi()
{
	int i = 0,
		j = 0;

	for(i = 0 ; i < numero_estados ; i++)
	{
		for(j = 0 ; j <= tamanho_cadeia ; j++)
		{
			calculos_aux[i][j] = -1;
		}

	}
}


int main()
{
	
	char linha[SIZE],
		estado_final;
	int i = 0;
	
	/** Input dos testes**/
	while(scanf("%d %d\n",&numero_estados, &tamanho_cadeia) != EOF)
	{

			initi();
			for(i = 0 ; i < numero_estados ; i++)
			{
				scanf(" %[^\n]", linha);
				if(sscanf(linha,"%d %d %c",&automato[i].ligacao_0,&automato[i].ligacao_1,&estado_final) == 3)
				{
					automato[i].estado_final = 49;
				}
				else
				{
					automato[i].estado_final = 48;
				}
			}
			
			estado_aceitador(0,0);
		
		printf("%d\n",calculos_aux[0][0]);
		contador = 0;
		conta_caminhos = 0;	
	}
	

	return 0;

}
