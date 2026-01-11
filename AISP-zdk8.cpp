#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Cvor;
typedef struct Cvor* Pozicija;

struct Cvor {
	int element;
	Pozicija next;
};

int Push(Pozicija, int);
int Pop(Pozicija, int*);
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
	int status;

	while (fscanf(fp, " %s", buffer) == 1) {

		printf(" %s", buffer);

		x = atoi(buffer);

		if ((x == 0) && (buffer[0] != '0')) {
			int q, r, s;

			status = Pop(&head, &q);
			if (status != 0) {
				printf("\nGreška: stog je prazan, nema dovoljno operanada za operator '%c'\n", buffer[0]);
				fclose(fp);
				return -1;
			}

			status = Pop(&head, &r);
			if (status != 0) {
				printf("\nGreška: stog je prazan, nema dovoljno operanada za operator '%c'\n", buffer[0]);
				fclose(fp);
				return -1;
			}

			s = Postfiks(q, buffer[0], r);
			Push(&head, s);

		}
		else {
			status = Push(&head, x);
			if (status != 0) {
				printf("\nGreška: element nije dodan na stog\n");
				fclose(fp);
				return -1;
			}
		}
	}

	fclose(fp);

	if (head.next == NULL) {
		printf("\nGreška: izraz je prazan\n");
		return -1;
	}

	if (head.next->next != NULL) {
		printf("\nGreška: postfiks izraz nije ispravan, stog sadrži više od jednog elementa\n");
		return -1;
	}

	printf("\nRezultat: %d\n", head.next->element);
	free(head.next);

	return 0;
}

int Push(Pozicija P, int n) {
	
	Pozicija q = (Pozicija)malloc(sizeof(struct Cvor));
	if (q == NULL) {
		return -1;
	}

	q->element = n;
	q->next = P->next;
	P->next = q;

	return 0;
}

int Pop(Pozicija P, int* n) {

	if (P->next == NULL) {
		return -1;
	}

	Pozicija temp = P->next;
	*n = temp->element;
	P->next = temp->next;
	free(temp);

	return 0;
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
