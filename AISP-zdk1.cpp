#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char ime[20];
	char prezime[20];
	int bodovi;
	float relativni;
}Student;

int IzbrojiStudente();
void UcitajStudente(Student*, int);
void IspisStudenata(Student*, int, int);
int NadiMaxBrBodova(Student*, int);

int main() {

	int brojStudenata = 0;
	brojStudenata = IzbrojiStudente();
	//printf("\n Broj studenata zapisanih u datoteci: %d\n", brojStudenata);

	if (brojStudenata > 0) {

		Student* studenti = (Student*)malloc(brojStudenata * sizeof(Student));  //(Student*)
		if (studenti == NULL) {
			printf("Greska pri alokaciji memorije!\n");
			return 1;
		}

		UcitajStudente(studenti, brojStudenata);
		int max = 0;
		max = NadiMaxBrBodova(studenti, brojStudenata);
		IspisStudenata(studenti, brojStudenata, max);

		free(studenti);

	}
	else {
		printf("Datoteka nema studente.\n");
	}

	return 0;
}

int IzbrojiStudente() {

	FILE* fp = NULL;
	fp = fopen("studenti.txt", "r");
	if (fp == NULL) {
		printf("Greska! Datoteka nije otvorena!\n");
		return -1;
	}

	int i = 0;
	Student studenti = { 0 };
	while (!feof(fp)) {
		fscanf(fp, "%s %s %d", studenti.ime, studenti.prezime, &studenti.bodovi);
		i++;
	}

	fclose(fp);
	return i;

}

void UcitajStudente(Student* studenti, int n) {

	FILE* fp = NULL;
	fp = fopen("studenti.txt", "r");
	if (fp == NULL) {
		printf("Greska! Datoteka nije otvorena!\n");
		return;
	}

	int i = 0;
	for (i = 0; i < n; i++) {
		fscanf(fp, "%s %s %d", studenti[i].ime, studenti[i].prezime, &studenti[i].bodovi);
	}

	fclose(fp);

}

void IspisStudenata(Student* studenti, int n, int max) {

	FILE* fp = NULL;
	fp = fopen("studenti.txt", "r");
	if (fp == NULL) {
		printf("Greska! Datoteka nije otvorena!\n");
		return;
	}

	int i = 0;
	for (i = 0; i < n; i++) {
		studenti[i].relativni = (studenti[i].bodovi) / (float)max * 100;
	}

	for (i = 0; i < n; i++) {
		printf("%s %s %d %f\n", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi, studenti[i].relativni);
	}

	fclose(fp);

}

int NadiMaxBrBodova(Student* studenti, int n) {

	int najveci = 0;
	int i = 0;

	for (i = 0; i < n; i++) {
		if ((studenti[i].bodovi) > najveci) {
			najveci = studenti[i].bodovi;
		}
	}
	return najveci;
}