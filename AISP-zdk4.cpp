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

int ucitajPolinom(Pozicija, const char*);
void ispisPolinoma(Pozicija);
int zbrojPolinoma(Pozicija, Pozicija, Pozicija);
int umnozakPolinoma(Pozicija, Pozicija, Pozicija);
void obrisiListu(Pozicija);

int ubaciSortiranu(Pozicija, int, int);

int main() {

    struct Cvor head1;
    struct Cvor head2;
    struct Cvor head3;
    struct Cvor head4;

    head1.next = NULL;
    head2.next = NULL;
    head3.next = NULL;
    head4.next = NULL;

    int st1 = ucitajPolinom(&head1, "polinom1.txt");
    int st2 = ucitajPolinom(&head2, "polinom2.txt");

    if (st1 != 0 || st2 != 0) {
        printf("Greska pri ucitavanju polinoma\n");
        obrisiListu(&head1);
        obrisiListu(&head2);
        obrisiListu(&head3);
        obrisiListu(&head4);
        return 1;
    }

    printf("Polinom 1:\n");
    ispisPolinoma(head1.next);

    printf("Polinom 2:\n");
    ispisPolinoma(head2.next);

    if (zbrojPolinoma(head1.next, head2.next, &head3) != 0) {
        obrisiListu(&head1);
        obrisiListu(&head2);
        obrisiListu(&head3);
        obrisiListu(&head4);
        return 1;
    }

    printf("Zbroj polinoma:\n");
    ispisPolinoma(head3.next);

    if (umnozakPolinoma(head1.next, head2.next, &head4) != 0) {
        obrisiListu(&head1);
        obrisiListu(&head2);
        obrisiListu(&head3);
        obrisiListu(&head4);
        return 1;
    }

    printf("Umnozak polinoma:\n");
    ispisPolinoma(head4.next);

    obrisiListu(&head1);
    obrisiListu(&head2);
    obrisiListu(&head3);
    obrisiListu(&head4);

    return 0;
}

int ucitajPolinom(Pozicija head, const char* ime) {

    FILE* fp = fopen(ime, "r");
    if (!fp)
        return 1;

    Pozicija q, i;

    while (fscanf(fp, "%d %d", &((q = (Pozicija)malloc(sizeof(struct Cvor)))->koeficijent), &q->eksponent) == 2) {

        if (!q) {
            fclose(fp);
            return 2;
        }

        if (q->koeficijent == 0) {
            free(q);
            continue;
        }

        i = head;

        while (i->next != NULL && i->next->eksponent > q->eksponent)
            i = i->next;

        if (i->next != NULL && i->next->eksponent == q->eksponent) {
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

    fclose(fp);
    return 0;
}

int ubaciSortiranu(Pozicija head, int koef, int exp)
{
    if (koef == 0) return 0;

    Pozicija novi = (Pozicija)malloc(sizeof(struct Cvor));
    if (!novi) return 1;

    novi->koeficijent = koef;
    novi->eksponent = exp;

    Pozicija i = head;

    while (i->next != NULL && i->next->eksponent > exp)
        i = i->next;

    if (i->next != NULL && i->next->eksponent == exp) {
        i->next->koeficijent += koef;
        free(novi);
        if (i->next->koeficijent == 0) {
            Pozicija temp = i->next;
            i->next = temp->next;
            free(temp);
        }
    }
    else {
        novi->next = i->next;
        i->next = novi;
    }

    return 0;
}

int zbrojPolinoma(Pozicija p1, Pozicija p2, Pozicija head)
{
    while (p1) {
        if (ubaciSortiranu(head, p1->koeficijent, p1->eksponent) != 0)
            return 1;
        p1 = p1->next;
    }

    while (p2) {
        if (ubaciSortiranu(head, p2->koeficijent, p2->eksponent) != 0)
            return 1;
        p2 = p2->next;
    }

    return 0;
}

int umnozakPolinoma(Pozicija p1, Pozicija p2, Pozicija head)
{
    if (!p1 || !p2) return 1;

    for (; p1; p1 = p1->next) {
        for (Pozicija b = p2; b; b = b->next) {
            int k = p1->koeficijent * b->koeficijent;
            int e = p1->eksponent + b->eksponent;

            if (ubaciSortiranu(head, k, e) != 0)
                return 2;
        }
    }

    return 0;
}

void ispisPolinoma(Pozicija p)
{
    int flag = 1;

    while (p != NULL) {
        if (flag) {
            if (p->eksponent == 0)
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

            if (p->eksponent == 0)
                printf("%d", p->koeficijent);
            else
                printf("%dx^%d", p->koeficijent, p->eksponent);
        }
        p = p->next;
    }
    printf("\n");
}

void obrisiListu(Pozicija head)
{
    Pozicija temp;
    while (head->next != NULL) {
        temp = head->next;
        head->next = temp->next;
        free(temp);
    }
}
