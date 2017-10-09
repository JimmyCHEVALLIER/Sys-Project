#include <stdio.h>
#include "table.c"

int main(){
	//Initialisation de notre Table
	Table_entry *testTable;
	testTable = (PTable_entry) malloc(sizeof(Table_entry));
	testTable->val = NULL;

	//Initialisation valeurs test
	int k=1;
        char v[]="salut";

	//Ajout d'une valeur
	store(&testTable, k, v);
	//Recherche et affichage d'une valeur
	printf("key = %d -> val = %s \n", k,  lookup(testTable, k));
	
	//Initialisation et ajout d'une deuxieme valeur
	int k1=2;
	store(&testTable, k1, v);

	//Recherche et affichage d'une valeur inconnu -> return null
	printf("key = %d -> val = %s \n", 3, lookup(testTable, 3)); 
	
	//Affiche une seul colonne
	displayone(k1, lookup(testTable, k1));

	//Affiche toute la table
	displayall(testTable);
	
	return 0;
}
