#include <stdlib.h>
#include <string.h>
#include "table.h"

//Stocke dans table la valeur v sous la cle k
void store(PTable_entry *table, int k, char v[]) {
	PTable_entry te = (PTable_entry) malloc(sizeof(Table_entry));
	te->key = k;
	te->val = (char*) malloc(strlen(v) + 1 );
	strcpy(te->val, v);
	te->next = *table;
	*table = te;
}

//Retourne la valeur se trouvant dans la table sous la cle k ou NULL si la cle n existe pas
char* lookup(PTable_entry table, int k) {
	PTable_entry pe = table;
	while (pe != NULL && pe->key != k) {
	pe = pe->next;
	}
	if (pe!= NULL) 
	{return pe->val;}
	else 
	{
	return NULL;
	}
}

void displayone(int key, char v[]) {
	printf("key = %d -> val = %s \n", key, v);
} 

void displayall(PTable_entry table) {
	int endListe=0;
        PTable_entry pe = table;
        printf("Table: [\n");
	while (pe != NULL && endListe == 0) {
		if(pe->val){	
                	printf(" key = %d -> value = %s \n", pe->key, pe->val);
			pe = pe->next;
		}
		else
		{
			endListe = 1;
			printf("	]\n");	
		}	
        }

}



