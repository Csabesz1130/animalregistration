#ifndef FUGGVENYEK_H_INCLUDED
#define FUGGVENYEK_H_INCLUDED

#include "debugmalloc.h"
#include <stdbool.h>

typedef struct Allatok {
    int azonosito;
    char allat_neve[30];
    char faj[20];
    char tulaj_vezneve[30];
    char tulaj_keresztnev[30];
    char diagnozis[60];
    char tulaj_elerhetoseg[30];
    int oltas_eve;
    int oltas_honap;
    int oltas_nap;
    struct Allatok *kov;
}Allatok;


int *azonosito_gen(Allatok *teljes_lista, char const *filename);

bool oltando_e(int aktualis_ev, int aktualis_honap, int aktualis_nap, int oltas_ev, int  oltas_honap, int oltas_nap);

void bevisz_adat(char const *filename, int *azonosito);

Allatok *lista_beolvas(FILE *fp, char const *filename);

void lista_kiir( Allatok *teljes_lista);

void kiir_oltando(Allatok *teljes_lista, int ev, int honap, int nap);

void lista_felszabadit(Allatok *teljes_lista);

void torol_adat(Allatok *teljes_lista, char const *allat_neve, char const *telefonszam);

void visszair(Allatok *teljes_lista, FILE *fp, char const *filename);

void keres_allatnev_telefon(Allatok *teljes_lista, char *allat_neve, char *telefonszam);

void keres_allatnev_tulajnev(Allatok *teljes_lista, char *allat_neve, char *tulaj_vezneve, char *tulaj_keresztnev);

void keres_faj_allatneve(Allatok *teljes_lista, char *allat_neve, char *allat_faja);

void allat_modosit(Allatok *teljes_lista, char const *telefonszam, char const *allat_neve);

#endif // FUGGVENYEK_H_INCLUDED
