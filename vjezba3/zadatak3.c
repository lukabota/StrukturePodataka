#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

struct _osoba;
typedef struct _osoba* Pozicija;
typedef struct _osoba {
    char ime[MAX];
    char prezime[MAX];
    int god;
    Pozicija next;
} Osoba;

int DodajIza(Pozicija head, char* prez, char* i, char* p, int g) {
    Pozicija t = head->next;
    while (t != NULL && strcmp(t->prezime, prez) != 0) {
        t = t->next;
    }
    if (t == NULL) return -1;
    
    Pozicija novi = (Pozicija)malloc(sizeof(Osoba));
    if (!novi) return -1;
    strcpy(novi->ime, i);
    strcpy(novi->prezime, p);
    novi->god = g;

    novi->next = t->next;
    t->next = novi;
    return 0;
}

int DodajIspred(Pozicija head, char* prez, char* i, char* p, int g) {
    Pozicija t = head;
    while (t->next != NULL && strcmp(t->next->prezime, prez) != 0) {
        t = t->next;
    }
    if (t->next == NULL) return -1;

    Pozicija novi = (Pozicija)malloc(sizeof(Osoba));
    if (!novi) return -1;
    strcpy(novi->ime, i);
    strcpy(novi->prezime, p);
    novi->god = g;

    novi->next = t->next;
    t->next = novi;
    return 0;
}

int Sortiraj(Pozicija head) {
    Pozicija i, j, prev_j, kraj = NULL;
    while (head->next != kraj) {
        prev_j = head;
        j = head->next;
        while (j->next != kraj) {
            if (strcmp(j->prezime, j->next->prezime) > 0) {
                Pozicija pom = j->next;
                prev_j->next = pom;
                j->next = pom->next;
                pom->next = j;
                j = pom;
            }
            prev_j = j;
            j = j->next;
        }
        kraj = j;
    }
    return 0;
}

int Upisi(Pozicija head, char* fileName) {
    FILE* f = fopen(fileName, "w");
    if (!f) return -1;
    Pozicija t = head->next;
    while (t != NULL) {
        fprintf(f, "%s %s %d\n", t->ime, t->prezime, t->god);
        t = t->next;
    }
    fclose(f);
    return 0;
}

int Citaj(Pozicija head, char* fileName) {
    FILE* f = fopen(fileName, "r");
    if (!f) return -1;
    char i[MAX], p[MAX];
    int g;
    while (fscanf(f, "%s %s %d", i, p, &g) == 3) {
        Pozicija novi = (Pozicija)malloc(sizeof(Osoba));
        if (!novi) { fclose(f); return -1; }
        strcpy(novi->ime, i);
        strcpy(novi->prezime, p);
        novi->god = g;

        novi->next = head->next;
        head->next = novi;
    }
    fclose(f);
    return 0;
}