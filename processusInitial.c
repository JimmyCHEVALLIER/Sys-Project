#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

void boucleprocessusfils(int N) {
        for(int i =0; i<N; i++)
        {
        	switch(fork())
		{
                	case -1:
                        	//En cas d'erreur
                        	exit(-1);
                	case 0:
                        	//Comportement du fils
				printf("fils %d cree\n", i);
				printf("Process ID fils -> %d \n", getpid());
                                printf("Process ID parent -> %d \n", getppid());
                	default:
                        	//Comportement du pere
				//printf("Boucle for i = %d \n", i);
				//printf("Le fils %d est mort\n",wait(NULL));
				printf("");
		}
        }
}

/*
 * La fonction execute un processus Initial char pCommande[], char *pTab[], 
 */
void forkfunc(int N){
    switch(fork()){
        case -1:
            //En cas d'erreur
            exit(-1);
        case 0:
            //Comportement du fils

        default:
            //Comportement du pere
		//printf("%d\n", getpid());
		switch(fork()){
				case -1:
				    //En cas d'erreur
				    exit(-1);
				case 0:
				    //Comportement du fils
					printf("1 %d\n", getpid());
					printf("1parent  %d\n", getppid());
					//boucleprocessusfils(3);
				default:
				    //Comportement du pere
					//printf("%d\n", getpid());
					switch(fork()){
					case -1:
					    //En cas d'erreur
					    exit(-1);
					case 0:
					    //Comportement du fils
						printf("2 %d\n", getpid());
						printf("2parent  %d\n", getppid());
						//boucleprocessusfils(3);
					default:
					    //Comportement du pere
						//printf("%d\n", getpid());
	
						while (wait(NULL)!=-1);
		
				    }
						//while (wait(NULL)!=-1);
		
				    }
		

		//while (wait(NULL)!=-1);
	        
    }
}



int main(int argc,char **argv){
    //Creation du processus initial
    //char * tmpTabWho[]={"who",NULL}; "who",tmpTabWho,
    forkfunc(3);
    return 0;
}
