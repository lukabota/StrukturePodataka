#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cvor {
    char ime[20];
    char prezime[20];
    int godina;
    struct cvor *next;
} Osoba;

Osoba* dodajPocetak(Osoba *g, char *i, char *p, int god) {
    Osoba *novi = (Osoba*)malloc(sizeof(Osoba));
    strcpy(novi->ime, i);
    strcpy(novi->prezime, p);
    novi->godina = god;
    novi->next = g;
    return novi;
}

void ispisi(Osoba *g) {
    while (g != NULL) {
        printf("%s %s (%d)\n", g->ime, g->prezime, g->godina);
        g = g->next;
    }
}

Osoba* dodajKraj(Osoba *g, char *i, char *p, int god) {
    Osoba *novi = (Osoba*)malloc(sizeof(Osoba));
    strcpy(novi->ime, i);
    strcpy(novi->prezime, p);
    novi->godina = god;
    novi->next = NULL;
    
    if (g == NULL) return novi;
    
    Osoba *temp = g;
    while (temp->next != NULL) temp = temp->next;
    temp->next = novi;
    return g;
}

Osoba* trazi(Osoba *g, char *p) {
    while (g != NULL) {
        if (strcmp(g->prezime, p) == 0) return g;
        g = g->next;
    }
    return NULL;
}

Osoba* obrisi(Osoba *g, char *p) {
    if (g == NULL) return NULL;
    
    if (strcmp(g->prezime, p) == 0) {
        Osoba *temp = g->next;
        free(g);
        return temp;
    }
    
    Osoba *temp = g;
    while (temp->next != NULL && strcmp(temp->next->prezime, p) != 0) {
        temp = temp->next;
    }
    
    if (temp->next != NULL) {
        Osoba *zaBrisanje = temp->next;
        temp->next = zaBrisanje->next;
        free(zaBrisanje);
    }
    return g;
}

int main() {
    Osoba *glava = NULL;
    
    glava = dodajPocetak(glava, "Ana", "Anic", 2001);
    glava = dodajPocetak(glava, "Ivo", "Ivic", 1999);
    glava = dodajKraj(glava, "Marko", "Maric", 2002);
    
    ispisi(glava);
    
    glava = obrisi(glava, "Ivic");
    printf("\nNakon brisanja:\n");
    ispisi(glava);
    
    return 0;
}