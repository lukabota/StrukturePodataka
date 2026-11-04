#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct _polinom;
typedef struct _polinom* Pozicija;
typedef struct _polinom {
    int koef;
    int eks;
    Pozicija next;
} Polinom;

int unos(Pozicija P, int k, int e) {
    if (k == 0) return 0;
    
    Pozicija novi = (Pozicija)malloc(sizeof(Polinom));
    if (!novi) return -1;
    novi->koef = k;
    novi->eks = e;
    
    Pozicija temp = P;
    while (temp->next != NULL && temp->next->eks > e) {
        temp = temp->next;
    }
    
    if (temp->next != NULL && temp->next->eks == e) {
        temp->next->koef += k;
        free(novi);
        if (temp->next->koef == 0) {
            Pozicija obrisi = temp->next;
            temp->next = obrisi->next;
            free(obrisi);
        }
    } else {
        novi->next = temp->next;
        temp->next = novi;
    }
    return 0;
}

int citaj(Pozicija P, char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) return -1;
    int k, e;
    while (fscanf(f, "%d %d", &k, &e) == 2) {
        unos(P, k, e);
    }
    fclose(f);
    return 0;
}

int zbroji(Pozicija P1, Pozicija P2, Pozicija R) {
    Pozicija t1 = P1->next;
    Pozicija t2 = P2->next;
    while (t1 != NULL) {
    unos(R, t1->koef, t1->eks);
    t1 = t1->next;
    }
    while (t2 != NULL) {
        unos(R, t2->koef, t2->eks);
        t2 = t2->next;
    }
    return 0;
}

int pomnozi(Pozicija P1, Pozicija P2, Pozicija R) {
 Pozicija t1 = P1->next;
    while (t1 != NULL) {
    Pozicija t2 = P2->next;
        while (t2 != NULL) {
        unos(R, t1->koef * t2->koef, t1->eks + t2->eks);
        t2 = t2->next;
        }
        t1 = t1->next;
    }
    return 0;
}