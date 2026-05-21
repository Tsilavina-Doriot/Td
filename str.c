#include<stdio.h>
#include<stdlib.h>
struct user
    {
        char *name;
        char *passwd;
        char *role;

    };
    void aff(struct user usr)
{
    printf(" noms: %s\n",usr.name);
    printf("mots de passe: %s\n",usr.passwd);
    printf("role: %s\n",usr.role);
}

void utilisateur  (int nombre)
{
    int i=0,j=0;
    FILE *fich=fopen("utilisateur","w+");

    if (fich!=NULL)
    {
        printf("Dossier crée avec succés\n");

        struct user usr[nombre];   
        while(i<nombre)
        {

          usr[i].name=malloc(100*sizeof(char));
          usr[i].passwd=malloc(100*sizeof(char));
          usr[i].role=malloc(200*sizeof(char));


          printf("Entrer votre noms: ");
          scanf("%s",usr[i].name);
          printf("entrer votre mots de passe: ");
          scanf("%s",usr[i].passwd);
          printf("Quel est votre role ?\n");
          scanf("%s",usr[i].role);
          fprintf(fich,"noms: %s ,mots de passe: %s ,role : %s\n",usr[i].name,usr[i].passwd,usr[i].role);
          i++;
        }
        printf("tous les utilisateur sont crées aec succées!!\n");
        for(i=0;i<nombre;i++)
        {
        printf("utilisateur n°: %d\n",i+1);
        printf("\n");
        aff(usr[i]);
        printf("\n");
        }    
    
        for(j=0;j<nombre;j++)
        {
            free(usr[j].name);
            free(usr[j].passwd);
            free(usr[j].role);
        }
    }
    fclose(fich);
    
}

int main()
{
    int n;
    printf("entrer le nombre d'utilisateur que vouds voulez entrer: ");
    scanf("%d",&n);
    utilisateur(n);
    return 0;
      
}
    
