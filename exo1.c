#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

/*  0     STDIN
 *  1     STDOUT
 *  2     STDERR
 *  3     f[0]
 *  4     f[1]
 *  5
 */


int main(int argc,char **argv){


    // tableau qui comporte la sortie du processus 1 (f[0]) et la sortie du processus 2 (f[1])
    int f[2]; // descripteur de fichier
    int f2[2];
    int x;
    //On crée toujours le pipe en premier
    pipe(f);
    pipe(f2);
    //fork() c'est le processus parent qui sert a lancer la commande ps
    switch(fork()){
        case -1:
            //En cas d'erreur
            perror("fork");
            exit(-1);
        case 0:
            //Comportement du fils si tout marche
            printf("File 1.numero %d\n", getpid());


            //Remplace stdin par l'entrée du pipe
            close(1); // On ferme le stdout du parent
            dup(f[1]); // On remplace le stdout par f[1] (f[1] est un descripteur de fichier)
            close(f[1]); //on ferme f[1]
            close(f[0]); // on ferme f[0] est ouvert en lecture et nous on veut que ecrire f[1]


            close(f2[1]); // On ferme f[1] car on veut pas lire
            close(f2[0]); // On femre f[0] car on l'a ajouté a stdin

            char * tmpTabPS[]={"ps","ax", NULL};
            execvp("ps" , tmpTabPS);

        default:
            //Comportement du pere
            //On recrée un autre processus

            while (wait(NULL)!=-1);
            switch(fork()){
                case -1:
                    //En cas d'erreur
                    perror("fork");
                    exit(-1);
                case 0:
                    //Comportement du fils
                    printf("File 2.numero %d\n", getpid());



                    //Remplace stdin par l'entrée du pipe et remplace stdout par l'entrée d'un autre pipe
                    close(0); //On ferme 0 (stdin)
                    dup(f[0]); // On ajoute f[0] sur la sortie stdin
                    //Si on ne ferme pas, boucle a l'infini
                    close(f[1]); // On ferme f[1] car on veut pas lire
                    close(f[0]); // On femre f[0] car on l'a ajouté a stdin


                    close(1);
                    dup(f2[1]);

                    close(f2[1]); // On ferme f[1] car on veut pas lire
                    close(f2[0]); // On femre f[0] car on l'a ajouté a stdin

                    //On execute la commande
                    char * tmpTabGREP[]={"grep", "bash", NULL};
                    execvp("grep" , tmpTabGREP);

                default:

                    switch(fork()){
                        case -1:
                            //En cas d'erreur
                            perror("fork");
                            exit(-1);
                        case 0:
                            //Comportement du fils
                            printf("File 3.numero %d\n", getpid());

                            close(0);
                            dup(f2[0]);

                            close(f2[1]);
                            close(f2[0]);

                            close(f[1]);
                            close(f[0]);

                            char * tmpTabWC[]={"wc", "-l", NULL};
                            execvp("wc" , tmpTabWC);

                        default:
                            close(f[0]);
                            close(f[1]);
                            close(f2[0]);
                            close(f2[1]);
                            while (wait(NULL)!=-1);
                    }




            }
    }

    return 0;
}

