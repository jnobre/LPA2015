

#include <stdio.h>
#include <stdlib.h>

#define N 12
#define M 40

/**
- n ≤ 12 
- m ≤ 40
- k ≤ n
**/


typedef struct strt_mov
{
	char verificado;
	int origem,
		destino,
		peso;
}movimentos;

typedef struct strt_point point;

struct strt_point
{
	char verificado;
	int n_ligacoes,
		aux_n_ligacoes,
		ligacoes[N];
};


point ligacoes_point[N] = {{0,0,0,{0}}};
point * ptr_ligacoes_point [N] = {0};


int num_point,
	num_ligacoes,
	grau,	
	adj[N][N],
	melhor_rede,
	peso_total,
	contador,
	flag;



void limpa_matriz()
{
	int i,j;
	for(i = 0 ; i < num_point ; i++)
	{
		for(j = 0 ; j < num_point ; j++)
			adj[i][j] = 0;
		ptr_ligacoes_point[i]->verificado = 0;
		ptr_ligacoes_point[i]->aux_n_ligacoes = 0;
		ptr_ligacoes_point[i]->n_ligacoes = 0;
	}
}


int compara_pesos(const void * a, const void * b)
{	
	const movimentos *p1 = (const movimentos *)a, 
  		  *p2 = (const movimentos *)b;
 	if(p1->peso == p2->peso)
    	return 0;
 	else
	    if(p1->peso < p2->peso)
	    	return -1;
	    else
	    	return 1;
}

void limpa_rede()
{
	int i = 0;

	for(i = 0 ; i < num_point ; i++)
	{
		ptr_ligacoes_point[i]->verificado = 0;
		ptr_ligacoes_point[i]->aux_n_ligacoes = 0;
	}
}

int construi_possibilidades(int peso_local,movimentos mov[num_ligacoes])
{
	int i,j,
		ncandidatos = 0;
	
	for(i = 0 ; i < num_point ; i++)
	{
		if(ptr_ligacoes_point[i]->verificado == 0) /*Se ainda nao esta na rede */
		{
			for(j = 0 ; j < ptr_ligacoes_point[i]->n_ligacoes ; j++) /** verifica ligacoes possiveis **/
			{
				/** Se tem ligacao que ja esta na rede e o seu peso + o peso ja somado nao ultrapassar o melhor peso adiciona **/
				if(ptr_ligacoes_point[ptr_ligacoes_point[i]->ligacoes[j]]->verificado == 1 && (adj[ptr_ligacoes_point[i]->ligacoes[j]][i]+peso_local) < melhor_rede) 
				{

					mov[ncandidatos].origem = ptr_ligacoes_point[i]->ligacoes[j]; 
					mov[ncandidatos].destino = i;
					mov[ncandidatos].peso = adj[ptr_ligacoes_point[i]->ligacoes[j]][i];
					mov[ncandidatos].verificado = 0;
					ncandidatos = ncandidatos + 1;

				}			
			}	
		}	
	}

	/** Ordena as possibilidades **/
	qsort(mov,ncandidatos,sizeof(movimentos),compara_pesos);

	return ncandidatos;
}

void printfarray(int ncandidatos, movimentos mov[num_ligacoes])
{
	int i;

	for(i = 0 ; i < ncandidatos ; i++)
		printf(" (%d,%d)=%d ",mov[i].origem+1,mov[i].destino+1,mov[i].peso);
					
	printf("\n");

}



void criar_rede(int peso_local,int nos_visitados)
{
	int i,
		ncandidatos;
	movimentos  mov[num_ligacoes];


	if( nos_visitados == num_point )
	{
		/** Caso Base **/
		if(peso_local < melhor_rede)
			melhor_rede = peso_local;
		flag = 1; /** flag que verifica se o grafo e conexo **/
	}
	else
	{
		
		ncandidatos = construi_possibilidades(peso_local,mov); /** Construi as possibilidades **/
		
		for(i = 0 ; i < ncandidatos ; i++)
		{
			if((ptr_ligacoes_point[mov[i].origem]->aux_n_ligacoes + 1 <= grau) && (ptr_ligacoes_point[mov[i].destino]->aux_n_ligacoes + 1 <= grau))	
			{	
					
				ptr_ligacoes_point[mov[i].destino]->verificado = 1;
				ptr_ligacoes_point[mov[i].origem]->aux_n_ligacoes++;
				ptr_ligacoes_point[mov[i].destino]->aux_n_ligacoes++;
					
				if((mov[i].peso+peso_local) < melhor_rede)
					criar_rede(mov[i].peso+peso_local,nos_visitados+1);
					
				ptr_ligacoes_point[mov[i].destino]->verificado = 0;
				ptr_ligacoes_point[mov[i].origem]->aux_n_ligacoes--;
				ptr_ligacoes_point[mov[i].destino]->aux_n_ligacoes--;
				
			}
		}		
	}
}




int main()
{

	int i,a,b,peso,
		a_nl,b_nl;

	melhor_rede = 0;

	while(scanf("%d %d %d",&num_point,&num_ligacoes,&grau) != EOF)
	{	
		contador = 0;
		for(i = 0 ; i < num_ligacoes ; i++)
		{
			scanf("%d %d %d",&a,&b,&peso);
			a = a - 1;
			b = b - 1;
			adj[a][b] = peso;
			adj[b][a] = peso;
			ptr_ligacoes_point[a] = &ligacoes_point[a];
			ptr_ligacoes_point[b] = &ligacoes_point[b];
			a_nl = ligacoes_point[a].n_ligacoes;
			b_nl = ligacoes_point[b].n_ligacoes;
			ligacoes_point[a].verificado = 0;
			ligacoes_point[b].verificado = 0;
			ligacoes_point[a].ligacoes[a_nl] = b;
			ligacoes_point[b].ligacoes[b_nl] = a;
			ligacoes_point[a].n_ligacoes = ligacoes_point[a].n_ligacoes + 1;
			ligacoes_point[b].n_ligacoes = ligacoes_point[b].n_ligacoes + 1;
			ligacoes_point[a].aux_n_ligacoes = 0;
			ligacoes_point[b].aux_n_ligacoes = 0;
			melhor_rede += peso; 
		}	
		melhor_rede += 1;
		flag = 0;
			
		ptr_ligacoes_point[0]->verificado = 1;
		criar_rede(0,1);
		
		if(flag)
			printf("%d\n",melhor_rede);
		else
			printf("NO WAY!\n");

		limpa_matriz();
		melhor_rede = 0;
	}


	return 0;
}



