#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Cvor;
typedef struct Cvor* Pozicija;

struct Cvor {
	int element;
	Pozicija next;
};

void Push(Pozicija, int);
int Pop(Pozicija);
int Postfiks(int, char, int);

int main() {

	struct Cvor head;
	head.next = NULL;

	printf("\nIzraz:\n");

	FILE* fp = NULL;
	fp = fopen("datoteka.txt", "r");
	if (fp == NULL) {
		printf("Datoteka nije otvorena!\n");
		return -1;
	}

	char buffer[32] = { 0 };
	int x;

	while (!feof(fp)) {

		if (fscanf(fp, " %s", buffer) != 1)
			break;

		printf(" %s", buffer);

		x = atoi(buffer); //string u int

		if ((x == 0) && (buffer[0] != '0')) {	// !='0' jer atoi('+')->0
			int q, r, s;

			q = Pop(&head);
			r = Pop(&head);
			s = Postfiks(q, buffer[0], r);
			Push(&head, s);

		}
		else {
			Push(&head, x);
		}
	}

	printf("\nRezultat: %d\n", head.next->element);
	free(head.next);

	fclose(fp);

	return 0;
}

void Push(Pozicija P, int n) {
	
	Pozicija q;
	q = (Pozicija)malloc(sizeof(struct Cvor));
	if (q == NULL) {
		printf("Greska pri alokaciji memorije!\n");
		return;
	}

	if (q) {
		q->element = n;
		q->next = P->next;
		P->next = q;
	}

}

int Pop(Pozicija P) {

	Pozicija temp;
	int n = 0;

	if (P->next != NULL) {
		temp = P->next;
		P->next = temp->next;
		n = temp->element;
		free(temp);
	}
	return n;
}

int Postfiks(int x, char operacija, int y) {

	int n = 0;
	switch (operacija) {
	case '+':
		n = x + y;
		break;
	case '-':
		n = x - y;
		break;
	case '*':
		n = x * y;
		break;
	case '/':
		if (y != 0)
			n = x / y;
		else
			printf("Nema dijeljenja s nulom!\n");
		break;
	default:
		printf("Nepoznat operator u postfiks izrazu!\n");
	}
	return n;
}
