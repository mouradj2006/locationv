
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//les donnees
typedef struct Personne Personne;
typedef struct Voiture Voiture;
typedef struct Location Location;

struct Personne
{
    char cin[8];
    char nom[50];
    char prenom[50];
};
struct Voiture
{
    char matricule[8];
    char marque[50];
    int prix_j;
    int duree_loc;
};
struct Location
{
    int id_loc;
    Personne client;
    Voiture voiture_louee[50];
    int n;
};
//implementation de la liste
typedef struct Element Element;
struct Element
{
    Location val;
    Element *suivant;
};
typedef Element *LISTE;
LISTE l = NULL;
void ajouter(LISTE *l, Location e)
{
    Element *new = (Element *)malloc(sizeof(Element));
    new->suivant = NULL;
    new->val = e;
    if (*l)
    {
        LISTE p = *l;
        while (p->suivant)
        {
            p = p->suivant;
        }
        p->suivant = new;
    }
    else
    {

        *l = new;
    }
}
void supprimer(LISTE *l, int id)
{

    LISTE p, q;
    p = *l;
    q = p;
    if (p->val.id_loc == id)
    {
        *l = p->suivant;
        free(p);
        return;
    }
    while ((p) && (p->val.id_loc != id))
    {
        q = p;
        p = p->suivant;
    }
    if (p)
    {
        q->suivant = p->suivant;
        free(p);
    }
}
int identifiant()
{
    LISTE p = l;
    int c = 0;
    while (p)
    {
        c++;
        p = p->suivant;
    }
    return c;
}
void affiche(LISTE l)
{
    LISTE p = l;
    while (p)
    {
        printf("%s %s %s\n", p->val.client.cin, p->val.client.nom, p->val.client.prenom);
        p = p->suivant;
    }
}
//saisie location
void saisie_location(Location *e)
{
    int n, i;

    printf("CIN CLIENT\n");
    scanf("%s", e->client.cin);
    printf("NOM CLIENT\n");
    scanf("%s", e->client.nom);
    printf("PRENOM CLIENT\n");
    scanf("%s", e->client.prenom);
    printf("NOMBRE DE VOITURE POUR CE CLIENT\n");
    scanf("%d", &e->n);
    for (i = 0; i < e->n; i++)
    {

        printf("MATRICULE DE LA VOITURE %d \n", i + 1);
        scanf("%s", e->voiture_louee[i].matricule);
        printf("MARQUE DE LA VOITURE %d \n", i + 1);
        scanf("%s", e->voiture_louee[i].marque);
        printf("PRIX JOUR DE LA VOITURE %d \n", i + 1);
        scanf("%d", &e->voiture_louee[i].prix_j);
        printf("DUREE LOCATION DE LA VOITURE %d \n", i + 1);
        scanf("%d", &e->voiture_louee[i].duree_loc);
    }
}

int prix_tot(Location e)
{
    int prix = 0;
    for (int i = 0; i < e.n; i++)
    {
        prix += e.voiture_louee[i].prix_j * e.voiture_louee[i].duree_loc;
    }
    return prix;
}
void afficher_location(Location e)
{
    int i;
    printf("ID: %d\n", e.id_loc);
    printf("CLIENT: %s %s %s \n", e.client.cin, e.client.nom, e.client.prenom);
    printf("VOITURES: \n");
    printf("MATRICULE MARQUE PRIX DUREE \n");
    for (i = 0; i < e.n; i++)
    {
        printf("%-9s %-6s %-4d %-5d \n", e.voiture_louee[i].matricule, e.voiture_louee[i].marque, e.voiture_louee[i].prix_j, e.voiture_louee[i].duree_loc);
    }
    printf("\n");
}

int menu_general()
{
    int choix;

    printf("MENU PRINCIPAL\n");
    printf("1-AJOUTER LOCATION\n");
    printf("2-AFFICHER LOCATIONS\n");
    printf("3-RECHERCHER LOCATION\n");
    printf("4-SUPPRIMER LOCATION\n");
    printf("5-ENREGISTRER LOCATION\n");

    do
    {
        printf("CHOIX=");
        scanf("%d", &choix);
    } while ((choix < 1) || (choix > 5));
    return choix;
}
void ajouter_location()
{
    Location loc;
    loc.id_loc = identifiant() + 1;
    saisie_location(&loc);
    ajouter(&l, loc);
}
void rechercher_location()
{
    int id;
    printf("DONNER ID DE LA LOCATION\n");
    scanf("%d", &id);
    LISTE p = l;
    while ((p) && (p->val.id_loc != id))
    {
        p = p->suivant;
    }
    if (p)
    {
        afficher_location(p->val);
    }
    else
    {
        printf("LOCATION INTROUVABLE\n\n");
    }
}
void all_locations()
{

    LISTE p = l;
    if (p)
    {
        while (p)
        {
            afficher_location(p->val);
            p = p->suivant;
        }
    }
    else
    {
        printf("LA LISTE DES LOCATIONS EST VIDE \n\n\n");
    }
}
void supprimer_location()
{
    int id;
    printf("DONNER ID DE LA LOCATION A SUPPRIMER \n");
    scanf("%d", &id);
    supprimer(&l, id);
}
void enregistrer()
{
    char nom[50];
    int id;
    printf("DONNER ID DE LA LOCATION\n");
    scanf("%d", &id);
    LISTE p = l;
    while ((p) && (p->val.id_loc != id))
    {
        p = p->suivant;
    }
    if (p)
    {
        printf("ENREGISTRER SOUS LE NOM ");
        scanf("%s", nom);
        FILE *fichier = fopen(nom, "w");
        Location e = p->val;
        if (fichier)
        {
            fprintf(fichier, "ID DE LA LOCATION:%d \n", e.id_loc);
            fprintf(fichier, "INFORMATION CLIENT:\nCIN :%s \nNOM :%s \nPRENOM : %s \n", e.client.cin, e.client.nom, e.client.prenom);
            fprintf(fichier, "VOITURES LOUEE: \n");
            fprintf(fichier, "MATRICULE MARQUE PRIX DUREE \n");
            for (int i = 0; i < e.n; i++)
            {
                fprintf(fichier, "%-9s %-6s %-4d %-5d \n", e.voiture_louee[i].matricule, e.voiture_louee[i].marque, e.voiture_louee[i].prix_j, e.voiture_louee[i].duree_loc);
            }
            fprintf(fichier, "PRIX A PAYER :%d", prix_tot(e));
            fclose(fichier);
        }
        else
        {
            printf("IMPOSSIBLE DE CREE LE FICHIER ");
        }
    }
    else
    {
        printf("LOCATION INTROUVABLE\n\n");
    }
}
//programme principal

int main(int argc, char const *argv[])
{
    int choix;
menu:
    choix = menu_general();
    if (choix == 1)
    {
        ajouter_location();
        system("@cls||clear");
        printf("AJOUT DE LA LOCATION EST TERMINEE AVEC SUCCEE\n\n");
        goto menu;
    }
    else if (choix == 2)
    {
        all_locations();
        goto menu;
    }
    else if (choix == 3)
    {
        system("@cls||clear");
        rechercher_location();
        goto menu;
    }
    else if (choix == 4)
    {
        system("@cls||clear");
        supprimer_location();
        goto menu;
    }
    else if (choix == 5)
    {
        system("@cls||clear");
        enregistrer();
        goto menu;
    }
    return 0;
}
