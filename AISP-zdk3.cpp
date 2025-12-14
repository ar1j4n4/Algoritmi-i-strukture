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

int ubaciNaprijed(Pozicija); 
int ubaciNazad(Pozicija); 
int ispisiListu(Pozicija); 
int izbrisiSve(Pozicija);

Pozicija pronadiElement(Pozicija, char*); 
int izbrisiElement(Pozicija, char*); 

//nove funkcije - 3. vjezba
int dodajIza(Pozicija, char*); // a)
int dodajIspred(Pozicija, char*); // b)
int sortirajListu(Pozicija); // c)
int upisiUDatoteku(Pozicija); // d)
int citajDatoteku(Pozicija); // e)

int main() {

	Osoba head;
	head.next = NULL;

	int provjera = 1;
	int opcija = 0;
	int rezultat = 0;

	do {
		printf("Odaberite opciju:\n1 - ubaciNaprijed\n2 - ubaciNazad\n3 - ispisiListu\n4 - pronadiElement\n5 - izbrisiElement\n6 - dodajIza\n7 - dodajIspred\n8 - sortirajListu\n9 - upisiUDatoteku\n10 - citajDatoteku\n");
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

		case 6: {
			char prez[20];
			printf("Upisite element (prezime):\n");
			scanf(" %s", prez);
			dodajIza(&head, prez);
			break;
		}

		case 7: {
			char prez[20];
			printf("Upisite element (prezime):\n");
			scanf(" %s", prez);
			dodajIspred(&head, prez);
			break;
		}

		case 8:
			sortirajListu(&head);
			printf("Lista sortirana po prezimenima.\n");
			break;

		case 9:
			upisiUDatoteku(&head);
			printf("Lista je upisana u datoteku.\n");
			break;

		case 10:
			citajDatoteku(&head);
			printf("Elementi liste procitani.\n");
			break;

		}
	} while (provjera);

	izbrisiSve(&head);

	return 0;
}

Pozicija stvoriCvor() {
	return (Pozicija)malloc(sizeof(Osoba));
}

void ispuniPodacima(Pozicija p) {

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

	return 0;

}

Pozicija pronadiElement(Pozicija p, char* prez) { 

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

int dodajIza(Pozicija head, char* prezime) {

	Pozicija p = pronadiElement(head, prezime);
	if (p == NULL) {
		printf("Element nije pronaden!\n");
		return -1;
	}

	Pozicija novi = stvoriCvor();
	if (novi == NULL) {
		printf("Greska!\n");
		return -1;
	}

	ispuniPodacima(novi);

	novi->next = p->next;
	p->next = novi;

	return 0;

}

int dodajIspred(Pozicija head, char* prezime) {

	Pozicija prev = head;
	Pozicija current = head->next;

	while ((current != NULL) && (strcmp(current->prezime, prezime) != 0)) {
		prev = current;
		current = current->next;
	}

	if (current == NULL) {
		printf("Element nije pronaden.\n");
		return -1;
	}

	Pozicija novi = stvoriCvor();
	if (novi == NULL) {
		printf("Greska!\n");
		return -1;
	}

	ispuniPodacima(novi);

	novi->next = current;
	prev->next = novi;

	return 0;

}

int sortirajListu(Pozicija head) {	//Bubble Sort

	if ((head->next == NULL) || (head->next->next == NULL)) {
		return 0;
	}

	int zamjena;
	do {
		zamjena = 0;
		Pozicija prev = head;
		Pozicija current = head->next;
		while (current->next != NULL) {
			if (strcmp(current->prezime, current->next->prezime) > 0) {
				Pozicija temp = current->next;
				current->next = temp->next;
				temp->next = current;
				prev->next = temp;
				zamjena = 1;
				prev = temp;
			}
			else {
				prev = current;
				current = current->next;
			}
		}
	} while (zamjena);

	return 0;

}

int upisiUDatoteku(Pozicija head) {

	FILE* fp = NULL;
	fp = fopen("datoteka.txt", "w");
	if (fp == NULL) {
		printf("Greska! Datoteka nije otvorena!\n");
		return -1;
	}

	Pozicija current = head->next;
	while (current != NULL) {
		fprintf(fp, " %s %s %d\n", current->ime, current->prezime, current->godRodenja);
		current = current->next;
	}

	fclose(fp);

	return 0;

}

int citajDatoteku(Pozicija head) {

	FILE* fp = NULL;
	fp = fopen("datoteka.txt", "r");
	if (fp == NULL) {
		printf("Greska! Datoteka nije otvorena!\n");
		return -1;
	}

	char _ime[20];
	char _prezime[20];
	int godina = 0;

	while (!feof) {
		Pozicija novi = stvoriCvor();
		if (!novi) {
			printf("Greska!\n");
			return -1;
		}
		strcpy(novi->ime, _ime);
		strcpy(novi->prezime, _prezime);
		novi->godRodenja = godina;
		novi->next = NULL;

		Pozicija temp = head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = novi;
	}

	fclose(fp);
	return 0;
}