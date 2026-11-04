#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct _polin;
typedef struct _polin* Pozicija;
typedef struct _polin {
    int koef;
    int eks;
    Pozicija next;
} Polin;

int Unesi(Pozicija head, int koef, int eks) {
    if (koef == 0) return 0;
    
    Pozicija novi = (Pozicija)malloc(sizeof(Polin));
    if (!novi) return -1;
    novi->koef = koef;
    novi->eks = eks;
    
    Pozicija temp = head;
    while (temp->next != NULL && temp->next->eks > eks) {
        temp = temp->next;
    }
    
    if (temp->next != NULL && temp->next->eks == eks) {
        temp->next->koef += koef;
        free(novi);
        if (temp->next->koef == 0) {
            Pozicija zaBrisanje = temp->next;
            temp->next = zaBrisanje->next;
            free(zaBrisanje);
        }
    } else {
        novi->next = temp->next;
        temp->next = novi;
    }
    return 0;
}

int Citaj(Pozicija head, char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) return -1;
    int k, e;
    while (fscanf(f, "%d %d", &k, &e) == 2) {
        Unesi(head, k, e);
    }
    fclose(f);
    return 0;
}

int Zbroji(Pozicija P1, Pozicija P2, Pozicija R) {
    Pozicija t1 = P1->next;
    Pozicija t2 = P2->next;
    while (t1 != NULL) {
        Unesi(R, t1->koef, t1->eks);
        t1 = t1->next;
    }
    while (t2 != NULL) {
        Unesi(R, t2->koef, t2->eks);
        t2 = t2->next;
    }
    return 0;
}

int Pomnozi(Pozicija P1, Pozicija P2, Pozicija R) {
    Pozicija t1 = P1->next;
    while (t1 != NULL) {
        Pozicija t2 = P2->next;
        while (t2 != NULL) {
            Unesi(R, t1->koef * t2->koef, t1->eks + t2->eks);
            t2 = t2->next;
        }
        t1 = t1->next;
    }
    return 0;
}