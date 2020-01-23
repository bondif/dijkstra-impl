#include<stdio.h>
#include<conio.h>
#define INFINI 9999
#define MAX 20

void dijkstra(int G[MAX][MAX], int n, int sommet_depart);

int main() {
	int G[MAX][MAX],i,j,n,u;
	printf("Entrer le nombre de sommets : ");
	scanf("%d",&n);
	printf("\nEntrer la matrice d'adjacence : \n");

	for(i=0; i<n; i++)
		for(j=0; j<n; j++)
			scanf("%d", &G[i][j]);

	printf("\nEntrer le sommets de depart : ");
	scanf("%d", &u);
	u--;
	
	dijkstra(G, n, u);

	return 0;
}

void dijkstra(int G[MAX][MAX], int n, int sommet_depart) {

	int dijkstra[MAX][MAX], longueurs[MAX], chemins[MAX];
	int visite[MAX], nb, min_longueur, sommet_suivant, i, j;
	
	// copie la matrice d'adjacence dans dijikstra
	// et remplace les 0 par l'INFINI 
	for(i=0; i<n; i++)
		for(j=0; j<n; j++)
			if(G[i][j] == 0)
				dijkstra[i][j] = INFINI;
			else
				dijkstra[i][j] = G[i][j];

	// initialise chemins[], longueurs[] and visite[]
	for(i=0; i<n; i++) {
		// initialise longueurs par la premiere ligne
		longueurs[i] = dijkstra[sommet_depart][i];
		
		// initialise chemins par le sommet de depart
		chemins[i] = sommet_depart;
		
		// zero c-a-d n'est pas encore visité
		visite[i] = 0;
	}
	
	// longueur vers le meme sommet est nulle
	longueurs[sommet_depart] = 0;
	
	// le sommet de depart est déjà visité
	visite[sommet_depart] = 1;
	
	// donc on commence à 1
	nb=1;

	while(nb < n-1) {
		min_longueur = INFINI;

		// on trouve le minimum de chaque ligne
		// on a l'indice du minimum dans sommet_suivant
		for(i=0; i<n; i++)
			if(longueurs[i] < min_longueur && !visite[i]) {
				min_longueur = longueurs[i];
				sommet_suivant = i;
			}

		// Le sommet est devenu maintenant visité
		visite[sommet_suivant] = 1;
		
		// Vérifier si un meilleur chemin existe à travers sommet_suivant
		for(i=0; i<n; i++)
			if(!visite[i])
				if(min_longueur + dijkstra[sommet_suivant][i] < longueurs[i]) {
					longueurs[i] = min_longueur + dijkstra[sommet_suivant][i];
					chemins[i] = sommet_suivant;
				}
		nb++;
	}

	// Affichage des chemins
	for(i=0; i<n; i++)
		if(i != sommet_depart) {
			printf("\nDistance vers %d est %d", i+1, longueurs[i]);
			printf("\nChemin vers %d", i+1);

			j=i;
			do {
				j = chemins[j];
				printf(" <- %d", j+1);
			} while(j != sommet_depart);
		}
}

