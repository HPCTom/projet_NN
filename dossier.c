#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "dossier.h"

int nombreAleatoire(int nombreMax){
  //srand(time(NULL));
  return (rand() % nombreMax);
}
 int piocherFichier(char *fichierPioche){
    FILE* liste = NULL; // Le pointeur de fichier qui va contenir notre fichier
    int nombreFichiers = 0, numFichierChoisi = 0;
    int caractereLu = 0;
    liste = fopen("liste.txt", "r"); // On ouvre la liste en lecture seule

    // On vérifie si on a réussi à ouvrir la liste
    if (liste == NULL) // Si on n'a PAS réussi à ouvrir le fichier
    {
        printf("\nImpossible de charger la liste");
        return 0; // On retourne 0 pour indiquer que la fonction a échoué
        // À la lecture du return, la fonction s'arrête immédiatement.
    }

    // On compte le nombre de mots dans le fichier (il suffit de compter les
    // entrées \n
    nombreFichiers = 496777; //555047
    // do
    // {
    //     caractereLu = fgetc(liste);
    //     if (caractereLu == '\n'){
    //       nombreFichiers++;
    //     }
    // } while(caractereLu != EOF);

    numFichierChoisi = nombreAleatoire(nombreFichiers); // On pioche un mot au hasard

    // On recommence à lire le fichier depuis le début. On s'arrête lorsqu'on est arrivé au bon mot
    //rewind(liste);
    while (numFichierChoisi > 0)
    {
        caractereLu = fgetc(liste);
        if (caractereLu == '\n')
            numFichierChoisi--;
    }

    /* Le curseur du fichier est positionné au bon endroit.
    On n'a plus qu'à faire un fgets qui lira la ligne */
    fgets(fichierPioche, 100, liste);

    // On vire le \n à la fin
    fichierPioche[strlen(fichierPioche) - 1] = '\0';
    fclose(liste);
    return 1;
}

void lireDossierRec(char* chemin_de_base) {
  DIR*rep;
  struct dirent *ptr_fichier;
  char chemin[1000 ];
  char save[1000];
  FILE* liste=NULL;
  strcpy(save,chemin_de_base);
  strcpy(chemin,chemin_de_base);

  rep = opendir(chemin_de_base);
  if(rep == NULL) {
		perror("opendir: erreur lors de l'ouverture\n");
		printf("%s\n",strerror(errno));
  }
  liste = fopen("liste.txt","a");
  while((ptr_fichier = readdir(rep)) != NULL){
      if((strcmp(ptr_fichier->d_name,"..")) && (strcmp(ptr_fichier->d_name,".")) != 0)  {
        printf("le fichier lu: %s\n", ptr_fichier->d_name);
        strcpy(chemin,chemin_de_base);
        strcat(chemin,"/");
        strcat(chemin,ptr_fichier->d_name);

        if (strstr(chemin,"png")){
          fprintf(liste,"%s\n",chemin);
          strcpy(chemin,save);
          continue;
        }
        fclose(liste);
        lireDossierRec(chemin);
      }
      else {
        continue;
      }
  }

  if((closedir(rep)) == -1){
		printf("erreur lors de la fermeture du dossier");
	}

}
