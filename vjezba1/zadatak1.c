#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char ime[50];
    char prezime[50];
    float bodovi;
} Student;

int main() {
    FILE *fp;
    int n, i;
    Student *studenti;
    float max_bodovi = 0;

    fp = fopen("studenti.txt", "r");
    if (fp == NULL) {
        printf("greska\n");
        return 1;
    }

    fscanf(fp, "%d", &n);

    studenti = (Student *)malloc(n * sizeof(Student));
    if (studenti == NULL) {
        printf("greska\n");
        fclose(fp);
        return 1;
    }

    for (i = 0; i < n; i++) {
        fscanf(fp, "%s %s %f", studenti[i].ime, studenti[i].prezime, &studenti[i].bodovi);
        if (studenti[i].bodovi > max_bodovi) {
            max_bodovi = studenti[i].bodovi;
        }
    }

    fclose(fp);

    for (i = 0; i < n; i++) {
        printf("%s %s %.2f %.2f\n", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi, (studenti[i].bodovi / max_bodovi) * 100);
    }

    free(studenti);

    return 0;
}