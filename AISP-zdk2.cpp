#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct Osoba;				//typedef struct _Osoba Osoba;
typedef struct Osoba* Pozicija;

struct Osoba {
	char ime[20];
	char prezime[20];
	int godRodenja;

	Pozicija next;
};

Pozicija stvoriCvor();
void ispuniPodacima(Pozicija);

int ubaciNaprijed(Pozicija); // a)
int ubaciNazad(Pozicija); // c)
int ispisiListu(Pozicija); // b)
int izbrisiSve(Pozicija);

Pozicija pronadiElement(Pozicija, char*); // d) 
int izbrisiElement(Pozicija, char*); // e)

int main() {

	Osoba head;
	head.next = NULL;

	int provjera = 1;
	int opcija = 0;
	int rezultat = 0;

	do {
		printf("Odaberite opciju:\n1 - ubaciNaprijed\n2 - ubaciNazad\n3 - ispisiListu\n4 - pronadiElement\n5 - izbrisiElement\n");
		scanf(" %d", &opcija);

		switch (opcija) {
		case 1:
			rezultat = ubaciNaprijed(&head);
			if (rezultat == 0) {
				printf("Element prebacen!\n");
			}
			else {
				printf("Element nije prebacen!!\n");
				provjera = 0;
			}
			break;

		case 2:
			rezultat = ubaciNazad(&head);
			if (rezultat == 0) {
				printf("Element prebacen!\n");
			}
			else {
				printf("Element nije prebacen!\n");
				provjera = 0;
			}
			break;

		case 3:
			ispisiListu(&head);
			break;

		case 4: {
			char prez[20];
			printf("Upisite prezime:\n");
			scanf(" %s", prez);

			Pozicija nadeno = pronadiElement(&head, prez);
			if (nadeno != NULL)
				printf("Nadeni element: %s %s %d\n", nadeno->ime, nadeno->prezime, nadeno->godRodenja);
			else
				printf("Nije pronaden element.\n");
			break;
		}

		case 5: {
			char prez[20];
			printf("Upisite element (prezime):\n");
			scanf(" %s", prez);

			if (izbrisiElement(&head, prez) == 0)
				printf("Element izbrisan.\n");
			else
				printf("Element nije pronaden.\n");
			break;
		}

		}
	} while (provjera);

	izbrisiSve(&head);

	return 0;
}

Pozicija stvoriCvor() {
	return (Pozicija)malloc(sizeof(Osoba));
}

void ispuniPodacima(Pozicija p) {

	/*strcpy(p->ime, "Arijana");
	strcpy(p->prezime, "Radeljak");
	p->godRodenja = 2004;*/

	printf("Upisite podatke (ime prezime godina):\n");
	scanf(" %s %s %d", p->ime, p->prezime, &p->godRodenja);

}

int ubaciNaprijed(Pozicija prev) {

	//Pozicija p = (Pozicija)malloc(sizeof(Osoba)); 
	Pozicija p = stvoriCvor();

	if (p == NULL) {
		printf("Greska!\n");
		return -1;
	}

	ispuniPodacima(p);

	p->next = prev->next;
	prev->next = p;

	return 0;
	
}

int ubaciNazad(Pozicija prev) {

	while (prev->next != NULL) {
		prev = prev->next;
	}

	return ubaciNaprijed(prev);

}

int ispisiListu(Pozicija p) {

	if (p->next == NULL) {
		printf("Lista je prazna!\n");
		return 0;
	}

	while (p->next != NULL) {
		p = p->next;
		printf(" %s %s %d\n", p->ime, p->prezime, p->godRodenja);
	}

	printf("\n");

	/*p = p->next;
	while (p != NULL) {
		printf(" %s %s %d\n", p->ime, p->prezime, p->godRodenja);
		p = p->next;
	}*/

	return 0;

}

Pozicija pronadiElement(Pozicija p, char* prez) { //po prezimenu

	p = p->next;

	while (p != NULL) {
		if (strcmp(p->prezime, prez) == 0) {
			return p;
		}
		p = p->next;
	}

	return 0;

}

int izbrisiElement(Pozicija head, char* prez) {

	Pozicija prev = head;
	Pozicija current = head->next;

	while (current != NULL) {

		if (strcmp(current->prezime, prez) == 0) {
			prev->next = current->next;
			free(current);
			return 0;
		}
		prev = current;
		current = current->next;
	}
	return -1;
}

int izbrisiSve(Pozicija p) {

	while (p->next != NULL) {
		Pozicija target = p->next;
		p->next = target->next;
		free(target);
	}

	return 0;

}

