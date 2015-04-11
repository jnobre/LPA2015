/* Treino R 2015 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_PEERS 35
#define MAX_PEER_LINKS MAX_PEERS-1

typedef struct strt_peer peer;

struct strt_peer {
	char has_printer;
	char checked;
	int n_links;
	int aux_n_links;
	peer * link[MAX_PEER_LINKS];
};

peer net_peers[MAX_PEERS] = {{0,0,0,0,{0}}};
peer * ptr_net_peers[MAX_PEERS] = {0};
int num_peers;

int compute();
int compute_possibility(int left_printers);
int compare_peers_desc(const void * a, const void * b);

int main(void) {

	int a,b;
	int a_nl,b_nl;

	scanf("%d",&num_peers);
	while(scanf("%d %d",&a,&b) != EOF) {
		a = a - 1;
		b = b - 1;
		ptr_net_peers[a] = &net_peers[a];
		ptr_net_peers[b] = &net_peers[b];
		a_nl = net_peers[a].n_links;
		b_nl = net_peers[b].n_links;
		net_peers[a].checked = 0;
		net_peers[b].checked = 0;
		net_peers[a].has_printer = 0;
		net_peers[b].has_printer = 0;
		net_peers[a].link[a_nl] = ptr_net_peers[b];
		net_peers[b].link[b_nl] = ptr_net_peers[a];
		net_peers[a].n_links++;
		net_peers[b].n_links++;
		net_peers[a].aux_n_links++;
		net_peers[b].aux_n_links++;
	}

	if (num_peers == 0) printf("0\n");
	else if (num_peers == 1) printf("1\n");
	else printf("%d\n",compute());

	return EXIT_SUCCESS;
}

int compute() {
	int i;

	int try_n_printers;
	int printer_temp = num_peers;

	qsort(ptr_net_peers,num_peers,sizeof(peer*),compare_peers_desc);

	/* choose the n_printers has the least possible value given the maximum degree of the nodes*/
	for (i = 0 ;printer_temp > 0 && i<num_peers;i++) {
		printer_temp = printer_temp - ptr_net_peers[i]->n_links - 1;
	}
	try_n_printers = i;
	if (try_n_printers == 1) return try_n_printers;

	for (i = try_n_printers; i < num_peers-1; ++i) {
		if (compute_possibility(i) > 0) return i;
	}

	return num_peers;

}

int compute_possibility(int left_printers) {
	int i,j,k;
	char flag;

	for (i = 0; i < num_peers; ++i) {
		/* ignore all nodes with printers and checked nodes with 0 unchecked links  */
		if (ptr_net_peers[i]->has_printer == 0 && (ptr_net_peers[i]->aux_n_links > 0 || ptr_net_peers[i]->checked == 0)) {

			/* choose this possibility, check it and all nodes linked to it */
			left_printers--;
			ptr_net_peers[i]->has_printer = 1;
			for (j = 0; j < ptr_net_peers[i]->n_links; ++j) {
				ptr_net_peers[i]->link[j]->aux_n_links--;
				if (ptr_net_peers[i]->link[j]->checked == 0) {
					ptr_net_peers[i]->link[j]->checked = i+1;
					for (k = 0; k < ptr_net_peers[i]->link[j]->n_links; ++k) {
						ptr_net_peers[i]->link[j]->link[k]->aux_n_links--;
					}
				}
			}


			if (left_printers == 0) {
				for (j = 0,flag = 0; j < num_peers; ++j) {
					if (ptr_net_peers[j]->checked == 0 && ptr_net_peers[j]->has_printer == 0) {
						flag = 1;
						break;
					}
				}
				if (!flag) return 1;
			} else {
				if (compute_possibility(left_printers) > 0) return 1; /* if this possibility was successful exit */
			}

			/* replace the network */
			left_printers++;
			ptr_net_peers[i]->has_printer = 0;
			for (j = 0; j < ptr_net_peers[i]->n_links; ++j) {
				ptr_net_peers[i]->aux_n_links++;
				if (ptr_net_peers[i]->link[j]->checked == i+1) {
					ptr_net_peers[i]->link[j]->checked = 0;
					for (k = 0; k < ptr_net_peers[i]->link[j]->n_links; ++k) {
						ptr_net_peers[i]->link[j]->link[k]->aux_n_links++;
					}
				}
			}

		}
	}
	return -1;

}

/* Order peers in descending order */
int compare_peers_desc(const void * a, const void * b) {
	int sum_a = 0,sum_b = 0,i,imax;
	const peer ** pa = (const peer **) a;
	const peer ** pb = (const peer **) b;
	if ((*pa)->n_links < (*pb)->n_links) return 1;
	if ((*pa)->n_links > (*pb)->n_links) return -1;
	if ((*pa)->n_links == 0) return 0;
	if ((*pa)->checked < (*pb)->checked) return 1;
	if ((*pa)->checked > (*pb)->checked) return -1;
	for (i = 0, imax = (*pa)->n_links; i < imax; ++i) {
		if ((*pa)->link[i] != NULL) {
			sum_a = sum_a + (*pa)->link[i]->checked;
		} else
			imax++;
	}
	for (i = 0, imax = (*pb)->n_links; i < imax; ++i) {
		if ((*pb)->link[i] != NULL) {
			sum_b = sum_b + (*pb)->link[i]->checked;
		} else
			imax++;
	}
	if (sum_a < sum_b) return 1;
	if (sum_a > sum_b) return -1;
	return 0;
}
