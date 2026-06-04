#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct informations
{
    char *nom;
    char *prenoms;
    char *niveau;
    char *age;
};

void mamaky()
{
    int i = 0;
    struct informations e[100];
    while(i<=100)
{
    e[i].noms=malloc(100*sizeof(char));
     e[i].prenoms=malloc(150*sizeof(char));
     e[i].age=malloc(20*sizeof(char));
     e[i].niveau=malloc(2*sizeof(char));
    i++;
}

    FILE *mamaky = fopen("etudiant", "r");
    if (mamaky == NULL) 
    {
        printf("Erreur : Impossible d'ouvrir le fichier 'etudiant'.\n");
        return;
    }

    // 1. Lecture et chargement de tout le fichier en mémoire
    while(i < 100 && fscanf(mamaky, "%100s %150s %20s %2s", e[i].nom, e[i].prenoms, e[i].age, e[i].niveau) == 4)
    {
        i++;
    }
    fclose(mamaky);

    int total_etudiants = i; 

    // 2. Tri à bulles par ordre DÉCROISSANT de l'âge
    for (i = 0; i < total_etudiants - 1; i++)
    {
        for (int j = 0; j < total_etudiants - i - 1; j++)
        {
            // Correction ici : on utilise bien le tableau 'e'
            if (atoi(e[j].age) < atoi(e[j + 1].age)) 
            {
                // Échange des structures complètes
                struct informations temp = e[j];
                e[j] = e[j + 1];
                e[j + 1] = temp;
            }
        }
    }

    // 3. Affichage du résultat trié
    printf("\n============= LISTE DES ÉTUDIANTS (TRIÉS PAR ÂGE DÉCROISSANT) =============");
    for(i = 0; i < total_etudiants; i++)
    {
        printf("\n--- Étudiant %d ---\n", i + 1);
        printf(" Nom     : %s\n", e[i].nom);
        printf(" Prénoms : %s\n", e[i].prenoms);
        printf(" Âge     : %s ans\n", e[i].age);
        printf(" Niveau  : %s\n", e[i].niveau);
    }
    while(i<=100)
{
    free(e[i]->nom);
    free(e[i]->prenoms);
    free(e[i]->age);
    free(e[i]->niveau);
  i++;
}
}
void enregistre(struct informations *etudiant)
{
    etudiant->nom=malloc(100*sizeof(char));
    etudiant->prenoms=malloc(150*sizeof(char));
    etudiant->age=malloc(20*sizeof(char));
    etudiant->niveau=malloc(2*sizeof(char));
    FILE *fichier = fopen("etudiant", "a");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
        return;
    }
    fprintf(fichier, "%s %s %s %s\n", etudiant->nom, etudiant->prenoms, etudiant->age, etudiant->niveau);
    fclose(fichier);  
    printf("Enregistrement reussi !\n");
    free(etudiant->nom);
    free(etudiant->prenoms);
    free(etudiant->age);
    free(etudiant->niveau);
}

void inscription(struct informations *etudiant)
{
    printf("Noms : ");
    fgets(etudiant->nom, 100, stdin);
    etudiant->nom[strcspn(etudiant->nom, "\n")] = '\0'; 

    printf("Prenoms : ");
    fgets(etudiant->prenoms, 150, stdin);
    etudiant->prenoms[strcspn(etudiant->prenoms, "\n")] = '\0';

    printf("Niveau : ");
    fgets(etudiant->niveau, 10, stdin);
    etudiant->niveau[strcspn(etudiant->niveau, "\n")] = '\0';

    printf("Age : ");
    fgets(etudiant->age, 20, stdin);
    etudiant->age[strcspn(etudiant->age, "\n")] = '\0';
}

void moteur_insc()
{
    struct informations etudiant; 
    inscription(&etudiant);
    enregistre(&etudiant);
}

int main()
{
    char choix;
    printf("Entrer 'r' pour lire et trier, 'i' pour inscription : ");
    scanf("%c", &choix);
    getchar(); 

    if (choix == 'i') {
        moteur_insc();
    } else if (choix == 'r') {
        mamaky();
    } else {
        printf("Choix invalide\n");
    }
    
    return 0;
}
