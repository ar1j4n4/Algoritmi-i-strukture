#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

typedef struct Cvor;
typedef struct Cvor* Pozicija;

struct Cvor {
	int element;
	Pozicija next;
};

int GeneriranjeBrojeva();
int PushStog(Pozicija, int);
int PopStog(Pozicija);
int EnqueueRed(Pozicija, int);
int DequeueRed(Pozicija);
void IspisListe(Pozicija);
void ObrisiListu(Pozicija);

int main() {

	Cvor stog, red;
	stog.next = NULL;
	red.next = NULL;

	int opcija = 1;
	int rezultat = 0;

	srand((unsigned)time(NULL));

	while (opcija != 0) {
		printf("\nOdaberite opciju:\n");
		printf("0 - zavrsetak programa\n");
		printf("1 - Push na stogu\n");
		printf("2 - Pop sa stoga\n");
		printf("3 - Enqueue (stavi) na red\n");
		printf("4 - Dequeue (makni) s reda\n");
		scanf(" %d", &opcija);

		switch (opcija) {

		case 0:
			printf("Program završen.\n");
			opcija = 0;
			break;

		case 1:
			rezultat = PushStog(&stog, GeneriranjeBrojeva());
			if (rezultat == 0)
				printf("Element uspješno dodan na stog.\n");
			else {
				printf("Element nije dodan!\n");
				ObrisiListu(&stog);
				ObrisiListu(&red);
				return -1;
			}
			IspisListe(stog.next);
			break;

		case 2:
			rezultat = PopStog(&stog);
			if (rezultat == 0)
				printf("Element uspješno skinut sa stoga.\n");
			else
				printf("Stog je prazan, ne možemo skinuti element.\n");
			IspisListe(stog.next);
			break;

		case 3:
			rezultat = EnqueueRed(&red, GeneriranjeBrojeva());
			if (rezultat == 0)
				printf("Element uspješno dodan u red.\n");
			else {
				printf("Element nije dodan!\n");
				ObrisiListu(&stog);
				ObrisiListu(&red);
				return -1;
			}
			IspisListe(red.next);
			break;

		case 4:
			rezultat = DequeueRed(&red);
			if (rezultat == 0)
				printf("Element uspješno maknut iz reda.\n");
			else
				printf("Red je prazan, ne možemo maknuti element.\n");
			IspisListe(red.next);
			break;

		default:
			printf("Opcija %d ne postoji. Pokušajte ponovno.\n", opcija);
		}
	}

	ObrisiListu(&stog);
	ObrisiListu(&red);

	return 0;
}

int GeneriranjeBrojeva() {
	int broj = (rand() % (100 - 10) + 10);
	return broj;
}

void IspisListe(Pozicija P) {
	printf("\nIspis liste:\n");
	while (P) {
		printf(" %d", P->element);
		P = P->next;
	}
	printf("\n");
}

int PushStog(Pozicija P, int broj) {
	Pozicija temp = (Pozicija)malloc(sizeof(struct Cvor));
	if (temp == NULL) return -1;
	temp->element = broj;
	temp->next = P->next;
	P->next = temp;
	return 0;
}

int PopStog(Pozicija P) {
	if (P->next == NULL) return -1;
	Pozicija temp = P->next;
	P->next = temp->next;
	free(temp);
	return 0;
}

int EnqueueRed(Pozicija P, int broj) {
	Pozicija temp = (Pozicija)malloc(sizeof(struct Cvor));
	if (temp == NULL) return -1;
	temp->element = broj;
	temp->next = NULL;
	if (P->next == NULL) P->next = temp;
	else {
		Pozicija zadnji = P->next;
		while (zadnji->next != NULL)
			zadnji = zadnji->next;
		zadnji->next = temp;
	}
	return 0;
}

int DequeueRed(Pozicija P) {
	if (P->next == NULL) return -1;
	Pozicija temp = P->next;
	P->next = temp->next;
	free(temp);
	return 0;
}

void ObrisiListu(Pozicija P) {
	Pozicija temp;
	while (P->next != NULL) {
		temp = P->next;
		P->next = temp->next;
		free(temp);
	}
}

