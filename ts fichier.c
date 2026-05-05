#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fonction pour l'addition
void addition(int a, int b) {
    int c;
    int *pa, *pb, *pc;
    FILE *somme = NULL;
    
    // Correction du mode : "w+" au lieu de "wr+"
    somme = fopen("somme.s", "w+");
    if (somme == NULL) {
        printf("ERREUR DE CREATION DU FICHIER\n");
        exit(0);
    } else {
        pa = &a;
        pb = &b;
        pc = &c;
        *pc = *pa + *pb;
        fprintf(somme, " la somme de %d et %d est égale à %d", *pa, *pb, *pc);
        fclose(somme);
    }
}

// Fonction qui écrit les 50 premiers nombres premiers
int premiers() {
    int n = 1, count = 0, i, premier;
    FILE *np;
    np = fopen("premiers.p", "w+");
    if (np == NULL) return 1;

    fprintf(np, ". Et les 50 nombres premiers sont: \n");
    while (count < 50) {
        n++;
        premier = 1;
        for (i = 2; i < n; i++) {
            if (n % i == 0) {
                premier = 0;
                break;
            }
        }
        if (premier == 1) {
            fprintf(np, "%d\n", n);
            count++;
        }
    }
    fclose(np);
    return 0;
}

// Fonction qui change les '5' en 'v'
int modify() {
    FILE *mod = NULL;
    FILE *temp = NULL;
    int ligne = 0; // Initialisé à 0
    char buffer[1024];

    mod = fopen("premiers.p", "r");
    temp = fopen("temporaires.p", "w"); // Mode "w" pour créer le fichier

    if (mod != NULL && temp != NULL) {
        while (fgets(buffer, sizeof(buffer), mod)) {
            ligne++;
            // On traite toutes les lignes sauf celles divisibles par 3 (selon ta logique)
            if (ligne % 3 != 0) {
                for (int i = 0; buffer[i] != '\0'; i++) {
                    if (buffer[i] == '5') {
                        buffer[i] = 'v';
                    }
                }
            }
            fputs(buffer, temp);
        }
    }
    
    if (mod) fclose(mod);
    if (temp) fclose(temp);
    
    remove("premiers.p");
    rename("temporaires.p", "premiers.p");
    return 0;
}

// Fonction qui efface les lignes divisibles par 3
int rmv() {
    FILE *rm = NULL;
    FILE *par = NULL;
    char buf[1024];
    int line = 1;

    rm = fopen("premiers.p", "r");
    par = fopen("par.p", "w"); // Mode "w" obligatoire ici

    if (rm == NULL || par == NULL) {
        printf("Erreur lors de l'ouverture pour suppression\n");
        if (rm) fclose(rm);
        return 0;
    }

    while (fgets(buf, sizeof(buf), rm)) {
        // Correction logique : on garde la ligne si elle n'est PAS divisible par 3
        if (line % 3 != 0) {
            fputs(buf, par);
        } else {
            printf("Ligne %d supprimée\n", line);
        }
        line++;
    }

    fclose(rm);
    fclose(par);
    remove("premiers.p");
    rename("par.p", "premiers.p");
    printf("Traitement terminé\n");
    return 0;
}

int main() {
    int a, b;
    FILE *lecture = NULL;
    FILE *read = NULL;
    int c, s; // Utilisation de int pour fgetc (gestion de EOF)

    printf("Entrer a: ");
    scanf("%d", &a);
    printf("Entrer b: ");
    scanf("%d", &b);

    addition(a, b);
    premiers();
    rmv();
    modify();

    lecture = fopen("somme.s", "r");
    read = fopen("premiers.p", "r");

    if (lecture != NULL && read != NULL) {
        while ((c = fgetc(lecture)) != EOF) {
            printf("%c", c);
        }
        printf("\n");
        while ((s = fgetc(read)) != EOF) {
            printf("%c", s);
        }
        fclose(lecture);
        fclose(read);
    } else {
        printf("Erreur de lecture du fichier final\n");
    }

    return 0;
}