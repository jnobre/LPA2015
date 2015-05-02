
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/time.h>

#define TRUE	'1'
#define FALSE	'0'

#define MAX_SUPERMARKETS 13	/* 12 SuperMarkets plus Depot*/

typedef struct _node node;
typedef struct _dist dist;

struct _dist {
	node *n ;
	int d;
};

struct _node {
	float x;
	float y;
	char visited;
	dist distances[MAX_SUPERMARKETS];
	int weight;
	float lbValue;
};



int compare_dist_asc(const void *p1, const void *p2);

node nodes[MAX_SUPERMARKETS];
int numNodes, numVisitedNodes;
int minDist = 0;
int truckWeight;

float calcLowerBound(node *n) {
	int i;
	float lb = 0;

	for (i = 0; i < numNodes; ++i)
		if (&nodes[i] == n || nodes[i].visited == FALSE)
			lb += nodes[i].lbValue;

	return lb;
}

void calcUpperBound() {
	int i, j, aux = truckWeight, nVisitedNodes = 0;
	node *n = &nodes[0];

	while (nVisitedNodes != numNodes-1) {
		if (n != &nodes[0])
			nVisitedNodes++;

		n->visited = TRUE;
		for(i=1; i< numNodes; i++) {
			if(n->distances[i].n->visited == FALSE) {
				if(aux - n->distances[i].n->weight >= 0) {
					/*minima distancia*/
					minDist += n->distances[i].d;
					aux -= n->distances[i].n->weight;
					n = n->distances[i].n;
					break;
				} else {
					for(j=1; j < numNodes; j++) {
						if(n->distances[j].n == &nodes[0]) {
							minDist += n->distances[j].d;
						}
					}
					aux = truckWeight;
					n = &nodes[0];
					break;
				}
			}
		}
	}

	for(i=1; i < numNodes; i++) {
		if(n->distances[i].n == &nodes[0]) {
			minDist += n->distances[i].d;
		}
	}

	for (i = 0; i < numNodes; ++i) {
		nodes[i].visited = FALSE;
	}

}

void findShortestPath(node *n, int dist, int weight) {
	int i, j, counter = 0;
	float lb;

	if (n != &nodes[0]) {
		if (++numVisitedNodes == numNodes-1) {
			for (j = 1; j < numNodes; ++j) {
				if (n->distances[j].n == &nodes[0]) {
					dist += n->distances[j].d;
					break;
				}
			}
			if (dist < minDist)
				minDist = dist;
			--numVisitedNodes;
			return;
		}
		n->visited = TRUE;
	} else
		weight = truckWeight;
	
	lb = dist + calcLowerBound(n);
	if (lb >= minDist) {
		if (n != &nodes[0])
			--numVisitedNodes;
		n->visited = FALSE;
		return;
	}


	for (i = 1; i < numNodes; ++i) {
		if (n->distances[i].n->visited == TRUE)
			continue;
		if (weight >= n->distances[i].n->weight) {
			findShortestPath(n->distances[i].n, dist + n->distances[i].d, weight - n->distances[i].n->weight);
		}
		counter++;
	}

	n->visited = FALSE;
	if (n != &nodes[0])
		--numVisitedNodes;
}

int euclideanDistance(node *n1, node *n2) {
	float c1, c2;

	c1 = n1->x - n2->x;
	c2 = n1->y - n2->y;

	c1 = sqrt(c1*c1 + c2*c2);
	return c1 - (int) c1 >= 0.5f ? ceil(c1) : floor(c1);
}

void createGraph() {
	int i, j;

	for (i = 0; i < numNodes; ++i) {
		for (j = 0; j < numNodes; ++j) {
			if (i == j) {
				nodes[i].distances[j].d = 0;
				nodes[i].distances[j].n = &nodes[i];
				continue;
			}
			nodes[i].distances[j].d = euclideanDistance(&nodes[i], &nodes[j]);
			nodes[i].distances[j].n = &nodes[j];
			minDist += nodes[i].distances[j].d;
		}
		qsort(nodes[i].distances, numNodes, sizeof(dist), compare_dist_asc);
		nodes[i].lbValue = (nodes[i].distances[1].d + nodes[i].distances[2].d)/2.0;
	}
}

int main(int argc, char **argv) {
	int i;

	while (scanf("%d\n", &numNodes) != EOF) {
		numNodes++;
		for (i = numNodes-1; i >= 0; --i) {
			scanf("%f %f %d\n", &nodes[i].x, &nodes[i].y, &nodes[i].weight);
			nodes[i].visited = FALSE;
		}
		scanf("%d\n", &truckWeight);
		minDist = 0;
		createGraph();

		/*calcUpperBound();*/
		numVisitedNodes = 0;

		findShortestPath(&nodes[0], 0, truckWeight);

		printf("%d\n", minDist);
	}

	return 0;
}

int compare_dist_asc(const void *p1, const void *p2) 
{

	const dist *elem1 = (const dist *)p1;
    const dist *elem2 = (const dist *)p2;

	if ( elem1->d < elem2->d)
		return -1;
	else if (elem1->d > elem2->d)
		return 1;
	else
		return 0;

}

