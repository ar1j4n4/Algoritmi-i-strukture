#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct Cvor;
typedef struct Cvor* Pozicija;

struct Cvor {
	int element;
	Pozicija next;
};

int citanjeDatoteke(Pozicija);
void ispisListe(Pozicija);
int unija(Pozicija, Pozicija, Pozicija);
int presjek(Pozicija, Pozicija, Pozicija);
void obrisiListu(Pozicija);

int main() {

	Pozicija head1 = NULL, head2 = NULL, headU = NULL, headP = NULL;

	head1 = (Pozicija)malloc(sizeof(struct Cvor));
	head2 = (Pozicija)malloc(sizeof(struct Cvor));
	headU = (Pozicija)malloc(sizeof(struct Cvor));
	headP = (Pozicija)malloc(sizeof(struct Cvor));

	if (!head1 || !head2 || !headU || !headP) {
		if (head1) free(head1);
		if (head2) free(head2);
		if (headU) free(headU);
		if (headP) free(headP);
		printf("Greska pri alokaciji!\n");
		return -1;
	}

	head1->next = NULL;
	head2->next = NULL;
	headU->next = NULL;
	headP->next = NULL;

	if (citanjeDatoteke(head1) != 0 || citanjeDatoteke(head2) != 0) {
		obrisiListu(head1);
		obrisiListu(head2);
		obrisiListu(headU);
		obrisiListu(headP);
		free(head1);
		free(head2);
		free(headU);
		free(headP);
		return -1;
	}

	printf("\nPrva lista:\n");
	ispisListe(head1->next);

	printf("\nDruga lista:\n");
	ispisListe(head2->next);

	if (unija(head1->next, head2->next, headU) != 0) {
		obrisiListu(head1);
		obrisiListu(head2);
		obrisiListu(headU);
		obrisiListu(headP);
		free(head1);
		free(head2);
		free(headU);
		free(headP);
		return -1;
	}

	printf("\nUnija:\n");
	ispisListe(headU->next);

	if (presjek(head1->next, head2->next, headP) != 0) {
		obrisiListu(head1);
		obrisiListu(head2);
		obrisiListu(headU);
		obrisiListu(headP);
		free(head1);
		free(head2);
		free(headU);
		free(headP);
		return -1;
	}

	printf("\nPresjek:\n");
	ispisListe(headP->next);

	obrisiListu(head1);
	obrisiListu(head2);
	obrisiListu(headU);
	obrisiListu(headP);

	free(head1);
	free(head2);
	free(headU);
	free(headP);

	return 0;
}

int citanjeDatoteke(Pozicija P) {

	FILE* fp = NULL;
	char datoteka[20];

	printf("Unesite ime datoteke:\n");
	scanf(" %s", datoteka);

	fp = fopen(datoteka, "r");
	if (fp == NULL) {
		printf("Greska! Datoteka nije otvorena!\n");
		return 1;
	}

	Pozicija q, temp;
	while (fscanf(fp, " %d", &((q = (Pozicija)malloc(sizeof(struct Cvor)))->element)) == 1) {

		if (!q) {
			fclose(fp);
			return 2;
		}

		temp = P;

		while ((temp->next != NULL) && (temp->next->element > q->element)) {
			temp = temp->next;
		}

		q->next = temp->next;
		temp->next = q;
	}

	fclose(fp);
	return 0;
}

void ispisListe(Pozicija P) {

	while (P != NULL) {
		printf(" %d", P->element);
		P = P->next;
	}
}

int unija(Pozicija L1, Pozicija L2, Pozicija U) {

	Pozicija q, temp;
	int elementU = 0;

	while ((L1 != NULL) && (L2 != NULL)) {
		if (L1->element > L2->element) {
			elementU = L1->element;
			L1 = L1->next;
		}
		else if (L1->element < L2->element) {
			elementU = L2->element;
			L2 = L2->next;
		}
		else {
			elementU = L1->element;
			L1 = L1->next;
			L2 = L2->next;
		}

		q = (Pozicija)malloc(sizeof(struct Cvor));
		if (!q) return 1;

		q->element = elementU;
		q->next = U->next;
		U->next = q;
		U = q;
	}

	if (L1 == NULL)
		temp = L2;
	else
		temp = L1;

	while (temp != NULL) {
		q = (Pozicija)malloc(sizeof(struct Cvor));
		if (!q) return 1;

		q->element = temp->element;
		q->next = U->next;
		U->next = q;
		U = q;
		temp = temp->next;
	}

	return 0;
}

int presjek(Pozicija L1, Pozicija L2, Pozicija P) {

	Pozicija q;

	while ((L1 != NULL) && (L2 != NULL)) {
		if (L1->element > L2->element)
			L1 = L1->next;
		else if (L1->element < L2->element)
			L2 = L2->next;
		else {
			q = (Pozicija)malloc(sizeof(struct Cvor));
			if (!q) return 1;

			q->element = L1->element;
			q->next = P->next;
			P->next = q;
			P = q;

			L1 = L1->next;
			L2 = L2->next;
		}
	}

	return 0;
}

void obrisiListu(Pozicija head) {

	Pozicija temp;

	while (head->next != NULL) {
		temp = head->next;
		head->next = temp->next;
		free(temp);
	}
}
```
