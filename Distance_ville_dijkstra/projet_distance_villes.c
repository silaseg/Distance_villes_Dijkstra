#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

#define NombreSommet 34 
#define MAX 10000 

//*********structure Chemin *******//
typedef struct{
	int t;
}Chemin;

//*******structure Sommet********//

typedef struct{
	char nom[55];
	int Nsommet;
	int autoroute;
}Sommet;

//**********structure algorithme Djikstra*****//
typedef struct{
	int t_t;
	int sommet;
	int etat;
	int origine;
}depart;

//******** Initialisation Tableau De Chemins******//

void init_Ch(Chemin C[NombreSommet][NombreSommet])
{
	int i,j;
	
	for(i=0;i<NombreSommet;i++)
	{
		for(j=0;j<NombreSommet;j++)
		{
			C[i][j].t=MAX;
			
		}
	}

}

//********Recuperation des Chemins ***********//

void recuperer_sommetr_Ch(Chemin C[NombreSommet][NombreSommet]){
	
	int check,i,j,t;
	FILE* fichierChemins = NULL;
	
	init_Ch(C);
	
	fichierChemins = fopen("chemin.txt","r");
	
	if (fichierChemins != NULL){
	
		printf("\nRécuperation des données du fichier \n");
		printf("\n");
			while(check!=-1)
			{
					check=fscanf(fichierChemins,"%d %d %d",&i, &j,&t);
					C[i][j].t=t;
					C[j][i].t=t;
				
			}	
				
		fclose(fichierChemins);
	}
	else{
		printf("Erreur lors de l'ouverture du fichier \n");
	}
	
	
}

//**********Affichage des Chemins************//

void afficher_chemin(Chemin C[NombreSommet][NombreSommet])
{
	int a,b;
	
	for(a=0;a<NombreSommet;a++)
	{
		for(b=0;b<NombreSommet;b++)
		{
			printf("%d %d %d\n",a,b,C[a][b].t);
		}
	}
}

//***********Initialisation des Sommets***********//

void initialiser_sommet(Sommet S[NombreSommet])
{
	int i;
	
	for(i=0;i<NombreSommet;i++)
	{
			strcpy(S[i].nom,"nom");
			S[i].Nsommet=i;
			S[i].autoroute=0;
			
	}
}

//********Affichage des Sommets************//

void afficher_sommet(Sommet S[NombreSommet])
{
	int i;
	
	for(i=0;i<NombreSommet;i++)
	{
		printf("%d %d %s \n",i,S[i].autoroute,S[i].nom);
	}
}

//***************Recuperation des Sommets****************//

void recuperer_sommetr_sommet(Sommet S[NombreSommet]){
	
	FILE* fichierSommet;
	
	int i;
	initialiser_sommet(S);
	
	fichierSommet = fopen("sommet.txt","r");
	
		if(fichierSommet != NULL)
		{
			printf("Récuperation des données du fichier\n");
		        printf("\n");
			
			for (i = 0; i < NombreSommet; i++)
			{
				
				fscanf(fichierSommet,"%d",&(S[i].Nsommet));
				fscanf(fichierSommet,"%d",&(S[i].autoroute));
				fscanf(fichierSommet,"%s",S[i].nom);	
				
			}
		
			fclose(fichierSommet);
		}
		
		else{
			printf("Erreur lors de l'ouverture du fichier\n");
		} 
}

//************Affichage de la distace *************//

void afficher_distance(depart D[NombreSommet], int s){
	printf("La distance est de : ");
	printf(" %d km\n", D[s].t_t);
	
}

//***************Initialisation Djikstra**************//

void init_Djikstra(depart D[NombreSommet], int sommet_depart){
	
	int i;
	
	printf("Initialisation tableau Djikstra\n");
	printf("\n");
	
	for (i = 0; i < NombreSommet; i++)
	{
		D[i].sommet = i;
		D[i].etat = 0;
		D[i].origine = -1;
		D[i].t_t = MAX;
	}
	
	D[sommet_depart].sommet = sommet_depart;
	D[sommet_depart].etat = 1;
	D[sommet_depart].origine = -1;
	D[sommet_depart].t_t = 0;
	
	
}

//********Rechercher la distance minimale a partir de sommet_actuel ****//

int iter_dijkstra(depart D[NombreSommet], int sommet_actuel){
	
	int min, i, sommetT;
	
	min = 20000;
	sommetT = -1;

	
	for (i = 0; i < NombreSommet; i++)
	{
		if (D[i].etat != 1 && D[i].t_t < min)
		{
			min = D[i].t_t;
			sommetT = i;
			
			if (D[i].etat == 1)
			{
				printf(" PROBLEME \n");
			}
		}
	}
	
	return sommetT;
}

//**********Tableau Djikstra********//

void afficher_distanceableau_Djikstra(depart D[NombreSommet]){
	
	int i;
	printf("***********************************************\n");
	for (i = 0; i < NombreSommet; i++)
	{
		printf("sommet : %d ,",D[i].sommet);
		printf("etat : %d ,",D[i].etat);
		printf("origine : %d ,",D[i].origine);
		printf("t : %d\n",D[i].t_t);
	}
	printf("***********************************************\n\n");
}


//********** Algorithme Principal Djikstra********//

void Djikstra(int sommet_actuel, depart D[NombreSommet], Sommet S[NombreSommet], Chemin C[NombreSommet][NombreSommet])
{
	int i=0;
	int sommetT;
	
	while(i<NombreSommet)
	{
		
		if(C[sommet_actuel][i].t!=MAX)
		{
		/*if(sommet_actuel == 4){  
			printf("\nsommet : %d ",sommet_actuel);
			printf("t du sommet courant .: %d\n",D[sommet_actuel].t_t);
			printf("t du chemin .: %d\n",C[sommet_actuel][i].t);
			printf("sommet pointé : %d\n",i);
			printf("t du sommet pointé: %d\n",D[i].t_t);
			printf("%d > %d + %d\n\n",D[i].t_t,C[sommet_actuel][i].t, D[sommet_actuel].t_t );
		}*/
			if(D[i].t_t >C[sommet_actuel][i].t + D[sommet_actuel].t_t)
			{
				//printf("Changement du t\n");
				D[i].t_t=C[sommet_actuel][i].t + D[sommet_actuel].t_t;
				D[i].origine=sommet_actuel;
				//printf("%d \n",D[i].origine);
			}
		}
		i++;
	}
	
	D[sommet_actuel].etat = 1;
	//if (sommet_actuel == 4) afficher_distanceableau_Djikstra(D);
	
	sommetT = iter_dijkstra(D,sommet_actuel);
	//printf("%d \n",sommetT);
	
	if (sommetT != -1)
	{
		Djikstra(sommetT,D,S,C);
	}
}

//*******Affichage Du trajet*******//

void afficher_distancerajet(depart D[NombreSommet], Sommet S[NombreSommet],Chemin C[NombreSommet][NombreSommet], int depart, int arrive)
{
	int sommet_suivant=arrive;
	
	printf("Vous etes à %s autoroute %d\n",S[arrive].nom,S[arrive].autoroute); 
	while(sommet_suivant != depart) 
	{	
		sommet_suivant = D[sommet_suivant].origine;
		printf("Prenez l'autoroute %d à %s \n", S[sommet_suivant].autoroute,S[sommet_suivant].nom);
	}
	
	printf("Vous arrivez à %s\n", S[depart].nom);
}



int main(int argc, char * argv[])
{
	Chemin C[NombreSommet][NombreSommet];
	Sommet 	S[NombreSommet];
	depart	D[NombreSommet];
	int  depart, arrive;
	
	recuperer_sommetr_Ch(C);
	recuperer_sommetr_sommet(S);
	
	//afficher_chemin(C);
	afficher_sommet(S);
	
	do{
	printf("\nOù vous trouvez-vous ? \n");
	scanf("%d", &depart);
	}while(depart!=S[depart].Nsommet);
	
		printf("Vous vous trouvez à : %s autoroute %d\n",S[depart].nom,S[depart].autoroute);
		printf("\n"); 
	
	do{
	printf("ou voulez vous allez ? \n");
	scanf("%d", &arrive);
	}while(arrive!=S[arrive].Nsommet);
	
		printf("Vous voulez allez à : %s autoroute %d\n",S[arrive].nom,S[arrive].autoroute);
		printf("\n");
		
	if( depart != arrive){
		
		init_Djikstra(D,arrive);
		Djikstra(arrive,D,S,C);
		
		afficher_distancerajet(D,S,C,arrive,depart);
		afficher_distance(D, depart);
		
		
		printf("Fin du programme \n");
	}
	else 
	{
		printf("Vous y êtes déjà  ...\n");
		printf("\nFin du programme \n");
	}
	 return 0;
}
