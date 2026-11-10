#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct _cvor;
typedef struct _cvor* Pozicija;
typedef struct _cvor {
    double el;
    Pozicija next;
} Cvor;


int push(Pozicija head, double x) {
    Pozicija novi = (Pozicija)malloc(sizeof(Cvor));
    if (novi == NULL) return -1;
    
    novi->el = x;
    novi->next = head->next;
    head->next = novi;
    
    return 0;
}


double pop(Pozicija head) {
    if (head->next == NULL) return 0;
    
    Pozicija temp = head->next;
    double x = temp->el;
    head->next = temp->next;
    free(temp);
    
    return x;
}


int citaj(Pozicija head, char* filename) {
    FILE* f = fopen(filename, "r");
    if (f == NULL) return -1;
    
    char buffer[50];
    double a, b;
    
    while (fscanf(f, "%s", buffer) == 1) {
        if (strcmp(buffer, "+") == 0) {
            b = pop(head);
            a = pop(head);
            push(head, a + b);
        }
        else if (strcmp(buffer, "-") == 0) {
            b = pop(head);
            a = pop(head);
            push(head, a - b);
        }
        else if (strcmp(buffer, "*") == 0) {
            b = pop(head);
            a = pop(head);
            push(head, a * b);
        }
        else if (strcmp(buffer, "/") == 0) {
            b = pop(head);
            a = pop(head);
            push(head, a / b);
        }
        else {
            push(head, atof(buffer));
        }
    }
    
    fclose(f);
    return 0;
}