#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct Cvor;
typedef struct Cvor* Pozicija;

struct Cvor {
    int koeficijent;
    int eksponent;
    Pozicija next;
};

void ucitajPolinom(Pozicija);
void ispisPolinoma(Pozicija);
void zbrojPolinoma(Pozicija, Pozicija, Pozicija);
void umnozakPolinoma(Pozicija, Pozicija, Pozicija);

int main() {

    struct Cvor head1;
    struct Cvor head2;
    struct Cvor head3;
    struct Cvor head4;

    head1.next = NULL;
    head2.next = NULL;
    head3.next = NULL;
    head4.next = NULL;

    ucitajPolinom(&head1);
    ucitajPolinom(&head2);

    printf("Polinom 1:\n");
    ispisPolinoma(head1.next);

    printf("Polinom 2:\n");
    ispisPolinoma(head2.next);

    zbrojPolinoma(head1.next, head2.next, &head3);
    printf("Zbroj polinoma:\n");
    ispisPolinoma(head3.next);

    umnozakPolinoma(head1.next, head2.next, &head4);
    printf("Umnozak polinoma:\n");
    ispisPolinoma(head4.next);

    return 0;
}

void ucitajPolinom(Pozicija head) {

    FILE* fp = fopen("vjezba4.txt", "r");
    if (fp == NULL) {
        printf("Greska! Datoteka nije otvorena!\n");
        return;
    }

    Pozicija q, i;
    int k, e;

    while (!feof(fp)) {
        q = (Pozicija)malloc(sizeof(struct Cvor));

        fscanf(fp, " %d %d", &q->koeficijent, &q->eksponent);

        if (q->koeficijent == 0) {
            free(q);
        }
        else {
            i = head;

            while ((i->next != NULL) && (i->next->eksponent > q->eksponent))
                i = i->next;

            if ((i->next != NULL) && (i->next->eksponent == q->eksponent)) {
                i->next->koeficijent += q->koeficijent;
                free(q);
                if (i->next->koeficijent == 0) {
                    q = i->next;
                    i->next = q->next;
                    free(q);
                }
            }
            else {
                q->next = i->next;
                i->next = q;
            }
        }
    }

    fclose(fp);
}

void ispisPolinoma(Pozicija p) {

    int flag = 1;

    while (p != NULL) {
        if (flag == 1) {
            if ((p->koeficijent == 1) && (p->eksponent == 0))
                printf("1");
            else if ((p->koeficijent == -1) && (p->eksponent == 0))
                printf("-1");
            else if ((p->koeficijent == 1) && (p->eksponent != 0))
                printf("x^%d", p->eksponent);
            else if ((p->koeficijent == -1) && (p->eksponent != 0))
                printf("-x^%d", p->eksponent);
            else if (p->eksponent == 0)
                printf("%d", p->koeficijent);
            else
                printf("%dx^%d", p->koeficijent, p->eksponent);

            flag = 0;
        }
        else {
            if (p->koeficijent > 0)
                printf(" + ");
            else {
                printf(" - ");
                p->koeficijent = -p->koeficijent;
            }

            if (p->koeficijent == 1 && p->eksponent != 0)
                printf("x^%d", p->eksponent);
            else if (p->eksponent == 0)
                printf("%d", p->koeficijent);
            else
                printf("%dx^%d", p->koeficijent, p->eksponent);
        }
        p = p->next;
    }
    print
