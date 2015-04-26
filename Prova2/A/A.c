#include <stdlib.h>
#include <stdio.h>
#define MAX 200

typedef struct strt_evento
{
	
	char verificado;
	int inicio,
		fim;

}reuniao;

reuniao reunioes[MAX];
int conta,
	num_reunioes;


int ordena_asc(const void * a, const void * b)
{
	const reuniao *p1 = (const reuniao *)a,
				 *p2 = (const reuniao *)b;

	if(p1->fim == p2->fim)
	{
		return 0;
	}
	else
		if(p1->fim > p2->fim)
			return 1;
		else
			return -1;
}


void calc()
{
	int i, j;

	conta = 1;
	j = 0;
	for(i = 0 ; i < num_reunioes ; i++)
	{
		if(reunioes[i].inicio >= reunioes[j].fim)
		{
			conta++;
			j = i;
		}
	} 
}

int main()
{
	int i;

	while(scanf("%d",&num_reunioes) != EOF)
	{
		for(i = 0 ; i < num_reunioes ; i++)
		{
			reunioes[i].verificado = 48;
			scanf("%d %d",&reunioes[i].inicio,&reunioes[i].fim);			
		}
		conta = 0;

		qsort(reunioes,num_reunioes,sizeof(reuniao),ordena_asc);
		calc();
		printf("%d\n",conta);
	}

	return 0;

}

