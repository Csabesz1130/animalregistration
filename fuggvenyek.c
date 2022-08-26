#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "debugmalloc.h"

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


int *azonosito_gen(Allatok *teljes_lista, char const *filename) {
    int azonosito = 0;
    for (Allatok *eleje = teljes_lista; eleje != NULL; eleje=eleje->kov) {
        azonosito++;
    }
    azonosito = azonosito + 2;
    return azonosito;
}



bool oltando_e(int aktualis_ev, int aktualis_honap, int aktualis_nap, int oltas_ev, int  oltas_honap, int oltas_nap) {

  if (aktualis_ev == oltas_ev) {
    return false;
  }
  else {
    if (aktualis_ev < oltas_ev) {
      return false;
    }
    if ((aktualis_ev-oltas_ev) > 1) {
        return true;
    }
    if (aktualis_ev-oltas_ev == 1) {
        if (aktualis_honap<oltas_honap) {
            return false;
        }
        if (aktualis_honap>oltas_honap) {
            return true;
        }
        if (aktualis_honap == oltas_honap) {
            if (aktualis_nap < oltas_nap) {
              //int oltasig_nap = oltas_nap-info->tm_mday;
              return false;
            }
            else {
              return  true;
            }
        }
    }
  }

}


void bevisz_adat(char const *filename, int *azonosito) {
    FILE *fp;
    char allat_neve[30];
    char faj[20];
    char tulaj_vezneve[30];
    char tulaj_keresztnev[30];
    char diagnozis[60];
    char tulaj_elerhetoseg[30];
    int oltas_eve;
    int oltas_honap;
    int oltas_nap;
    //whileba az fprintes fort es az scanf-eket, hogy a megfelelo szamu rekordot lehessen bevinni
    fp = fopen(filename, "at+");
    if (fp == NULL) {
        perror("Sikertelen fajlmegnyitas.");
        exit(1);
    }
    //char buffersor[270];
    Allatok *allat= (Allatok*)malloc(sizeof(Allatok));
    allat->azonosito = azonosito;
    printf("Allat azonositositoja: %d\n", azonosito);
    printf("Vigye be a kovetkezo adatokat:\n\n\n");

    //scanf("%d", &azonosito);

    printf("\nAllat neve:\n");
    scanf("%s", allat_neve);
    strcpy(allat->allat_neve, allat_neve);
    printf("\nAllat faja:\n");
    scanf("%s", faj);
    strcpy(allat->faj, faj);
    printf("\nTulajdonos vezetekneve: \n");
    scanf("%s", tulaj_vezneve);
    strcpy(allat->tulaj_vezneve, tulaj_vezneve);
    printf("\nTulajdonos keresztneve: \n");
    scanf("%s", tulaj_keresztnev);
    strcpy(allat->tulaj_keresztnev, tulaj_keresztnev);
    printf("\nTulajdonos elerhetosege: \n");
    scanf("%s", tulaj_elerhetoseg);
    strcpy(allat->tulaj_elerhetoseg, tulaj_elerhetoseg);
    printf("\nDiagnozis: \n");
    scanf("%s", diagnozis);
    strcpy(allat->diagnozis, diagnozis);
    printf("\nOltas eve: \n");
    scanf("%d", &oltas_eve);
    allat->oltas_eve = oltas_eve;
    printf("\nOltas honapja: \n");
    scanf("%d", &oltas_honap);
    allat->oltas_honap = oltas_honap;
    printf("\nOltas napja: \n");
    scanf("%d", &oltas_nap);
    allat->oltas_nap = oltas_nap;
    //fprintf(fp, "\n%d %s %s %s %s %s %s %d %d %d", allat->azonosito, allat->allat_neve, allat->faj, allat->tulaj_vezneve, allat->tulaj_keresztnev, allat->tulaj_elerhetoseg, allat->diagnozis, allat->oltas_eve, allat->oltas_honap, allat->oltas_nap);
    //allat->kov = NULL;
    if (fp == NULL) {
        perror("\nA fajl megnyitasa sikertelen volt.");
    }
    //fwrite(allat, sizeof(Allatok), 1, fp);
    for (Allatok *elem = allat; elem != NULL; elem = elem->kov) {
        fprintf(fp, "\n%d %s %s %s %s %s %s %d %d %d", elem->azonosito, elem->allat_neve, elem->faj, elem->tulaj_vezneve, elem->tulaj_keresztnev, elem->tulaj_elerhetoseg, elem->diagnozis, elem->oltas_eve, elem->oltas_honap, elem->oltas_nap);
    }
    printf("Az On altal bevitt adatok: \n%d %s %s %s %s %s %s %d %d %d\n", allat->azonosito, allat_neve, allat->faj, allat->tulaj_vezneve, allat->tulaj_keresztnev, allat->tulaj_elerhetoseg, allat->diagnozis, allat->oltas_eve, allat->oltas_honap, allat->oltas_nap);
    fclose(fp);
    lista_felszabadit(allat);
}

Allatok *lista_beolvas(FILE *fp, char const *filename) {
    Allatok *teljes_lista = NULL;
    Allatok ideiglenes;
    fp = fopen(filename, "rt");

    while(fscanf(fp, "%d %s %s %s %s %s %s %d %d %d", &ideiglenes.azonosito, ideiglenes.allat_neve, ideiglenes.faj, ideiglenes.tulaj_vezneve, ideiglenes.tulaj_keresztnev, ideiglenes.tulaj_elerhetoseg, ideiglenes.diagnozis, &ideiglenes.oltas_eve, &ideiglenes.oltas_honap, &ideiglenes.oltas_nap)==10) {
        Allatok *uj = (Allatok*)malloc(sizeof(Allatok));
        uj->azonosito = ideiglenes.azonosito;
        strcpy(uj->allat_neve, ideiglenes.allat_neve);
        strcpy(uj->faj, ideiglenes.faj);
        strcpy(uj->tulaj_vezneve, ideiglenes.tulaj_vezneve);
        strcpy(uj->tulaj_keresztnev, ideiglenes.tulaj_keresztnev);
        strcpy(uj->tulaj_elerhetoseg, ideiglenes.tulaj_elerhetoseg);
        strcpy(uj->diagnozis, ideiglenes.diagnozis);
        uj->oltas_eve = ideiglenes.oltas_eve;
        uj->oltas_honap = ideiglenes.oltas_honap;
        uj->oltas_nap = ideiglenes.oltas_nap;
        uj->kov = teljes_lista;
        teljes_lista = uj;
        //printf("%d %s %s %s %s %s %s %d %d %d\n\n", uj->azonosito, uj->allat_neve, uj->faj, uj->tulaj_vezneve, uj->tulaj_keresztnev, uj->tulaj_elerhetoseg, uj->diagnozis, uj->oltas_eve, uj->oltas_honap, uj->oltas_nap);
    }
    fclose(fp);

    return teljes_lista;
}



void lista_kiir( Allatok *teljes_lista) {
    //fp = fopen(filename, "rt");
    for (Allatok *eleje = teljes_lista; eleje != NULL; eleje = eleje->kov) {
        printf("%d %s %s %s %s %s %s %d %d %d\n\n", eleje->azonosito, eleje->allat_neve, eleje->faj, eleje->tulaj_vezneve, eleje->tulaj_keresztnev, eleje->tulaj_elerhetoseg, eleje->diagnozis, eleje->oltas_eve, eleje->oltas_honap, eleje->oltas_nap);
    }
    //fclose(fp);
}


void kiir_oltando(Allatok *teljes_lista, int ev, int honap, int nap) {
    printf("Kerem, mielott tovabbhaladna irja be a mai datumot. formatum:(ev honap nap):\n");
    scanf("%d %d %d", &ev, &honap, &nap);
    for (Allatok *eleje = teljes_lista; eleje != NULL; eleje = eleje->kov) {
        if (oltando_e( ev, honap, nap, eleje->oltas_eve, eleje->oltas_honap, eleje->oltas_nap)) {
            printf("%s %s: %s\n", eleje->tulaj_vezneve, eleje->tulaj_keresztnev, eleje->tulaj_elerhetoseg);
            printf("Azonosito, nev, faj, diagnozis: %d %s %s %s\n", eleje->azonosito, eleje->allat_neve, eleje->faj, eleje->diagnozis);
            printf("Utolso oltas idopontja(ev,ho,nap): %d %d %d\n\n", eleje->oltas_eve, eleje->oltas_honap, eleje->oltas_nap);
        }
    }
}

void lista_felszabadit(Allatok *teljes_lista) {
    if (teljes_lista == NULL) {
        return;
    }
    lista_felszabadit(teljes_lista->kov);
    free(teljes_lista);
}


void torol_adat(Allatok *teljes_lista, char const *allat_neve, char const *telefonszam) {
    Allatok *lemarado = NULL;
    Allatok *futo = teljes_lista;
    while(futo != NULL && futo->allat_neve != allat_neve && futo->tulaj_elerhetoseg != telefonszam) {
        lemarado = futo;
        futo = futo->kov;
    }
    if (futo == NULL) {

    }
    else if (lemarado == NULL) {
        Allatok *seged = futo->kov;
        free(futo);
        teljes_lista = seged;
    }
    else {
        lemarado->kov = futo->kov;
        free(futo);
    }
}


void allat_modosit(Allatok *teljes_lista, char const *telefonszam, char const *allat_neve) {

    Allatok ideiglenes;
    Allatok *allat = teljes_lista;
    printf("\nAllat neve:\n");
    scanf("%s", ideiglenes.allat_neve);
    strcpy(allat->allat_neve, ideiglenes.allat_neve);
    printf("\nAllat faja:\n");
    scanf("%s", ideiglenes.faj);
    strcpy(allat->faj, ideiglenes.faj);
    printf("\nTulajdonos vezetekneve: \n");
    scanf("%s", ideiglenes.tulaj_vezneve);
    strcpy(allat->tulaj_vezneve, ideiglenes.tulaj_vezneve);
    printf("\nTulajdonos keresztneve: \n");
    scanf("%s", ideiglenes.tulaj_keresztnev);
    strcpy(allat->tulaj_keresztnev, ideiglenes.tulaj_keresztnev);
    printf("\nTulajdonos elerhetosege: \n");
    scanf("%s", ideiglenes.tulaj_elerhetoseg);
    strcpy(allat->tulaj_elerhetoseg, ideiglenes.tulaj_elerhetoseg);
    printf("\nDiagnozis: \n");
    scanf("%s", ideiglenes.diagnozis);
    strcpy(allat->diagnozis, ideiglenes.diagnozis);
    printf("\nOltas eve: \n");
    scanf("%d", &ideiglenes.oltas_eve);
    allat->oltas_eve = ideiglenes.oltas_eve;
    printf("\nOltas honapja: \n");
    scanf("%d", &ideiglenes.oltas_honap);
    allat->oltas_honap = ideiglenes.oltas_honap;
    printf("\nOltas napja: \n");
    scanf("%d", &ideiglenes.oltas_nap);
    allat->oltas_nap = ideiglenes.oltas_nap;

    for (Allatok *futo = teljes_lista; futo != NULL; futo = futo->kov) {
        if (strcmp(futo->allat_neve, allat_neve)==0 && strcmp(futo->tulaj_elerhetoseg, telefonszam)==0) {
            Allatok *uj = (Allatok*)malloc(sizeof(Allatok));
            *uj = ideiglenes;
            *futo = *uj;
            //felszabadit(uj);
        }
    }
    printf("Megtortent a modositas.");
}


void visszair(Allatok *teljes_lista, FILE *fp, char const *filename) {
    fp = fopen(filename, "wt");
    if (fp == NULL) {
        perror("Hiba a fajl megnyitasakor.");
    }
    Allatok *eleje = teljes_lista;
    for (; eleje != NULL; eleje = eleje->kov) {
        fprintf(fp, "%d %s %s %s %s %s %s %d %d %d\n", eleje->azonosito, eleje->allat_neve, eleje->faj, eleje->tulaj_vezneve, eleje->tulaj_keresztnev, eleje->tulaj_elerhetoseg, eleje->diagnozis, eleje->oltas_eve, eleje->oltas_honap, eleje->oltas_nap);
    }
    fclose(fp);
}




void keres_allatnev_telefon(Allatok *teljes_lista, char *allat_neve, char *telefonszam) {
    printf("Allat neve:\n");
    scanf("%s", allat_neve);
    printf("Telefonszam:\n");
    scanf("%s", telefonszam);
    Allatok *eleje = teljes_lista;
    int talalatok_szama = 0;
    for (Allatok *eleje = teljes_lista; eleje != NULL; eleje= eleje->kov)   {
        if (strcmp(eleje->allat_neve, allat_neve)==0 && strcmp(eleje->tulaj_elerhetoseg, telefonszam)==0) {
            talalatok_szama++;
            printf("%s %s: %s\n", eleje->tulaj_vezneve, eleje->tulaj_keresztnev, eleje->tulaj_elerhetoseg);
            printf("Azonosito, nev, faj, diagnozis: %d %s %s: %s\n", eleje->azonosito, eleje->allat_neve, eleje->faj, eleje->diagnozis);
            printf("Utolso oltas idopontja(ev,ho,nap): %d.%d.%d\n", eleje->oltas_eve, eleje->oltas_honap, eleje->oltas_nap);
        }
    }
    if (talalatok_szama == 0) {
        printf("Nincs talalat.");
    }

}

void keres_allatnev_tulajnev(Allatok *teljes_lista, char *allat_neve, char *tulaj_vezneve, char *tulaj_keresztnev) {
    printf("Allat neve:\n");
    scanf("%s", allat_neve);
    printf("Tulajdonos vezetek- es keresztneve:\n");
    scanf("%s %s", tulaj_vezneve, tulaj_keresztnev);
    Allatok *eleje = teljes_lista;
    int talalatok_szama = 0;
    for (Allatok *eleje = teljes_lista; eleje != NULL; eleje= eleje->kov)   {
        if (strcmp(eleje->allat_neve, allat_neve)==0 && strcmp(eleje->tulaj_vezneve, tulaj_vezneve)==0 && strcmp(eleje->tulaj_keresztnev, tulaj_keresztnev)==0) {
            talalatok_szama++;
            printf("%s %s: %s\n", eleje->tulaj_vezneve, eleje->tulaj_keresztnev, eleje->tulaj_elerhetoseg);
            printf("Azonosito, nev, faj, diagnozis: %d %s %s: %s\n", eleje->azonosito, eleje->allat_neve, eleje->faj, eleje->diagnozis);
            printf("Utolso oltas idopontja(ev,ho,nap): %d.%d.%d\n", eleje->oltas_eve, eleje->oltas_honap, eleje->oltas_nap);
        }
    }
    if (talalatok_szama == 0) {
        printf("Nincs talalat.");
    }

}

void keres_faj_allatneve(Allatok *teljes_lista, char *allat_neve, char *allat_faja) {
    printf("Allat neve:\n");
    scanf("%s", allat_neve);
    printf("Allat faja:\n");
    scanf("%s", allat_faja);
    Allatok *eleje = teljes_lista;
    int talalatok_szama = 0;
    for (Allatok *eleje = teljes_lista; eleje != NULL; eleje= eleje->kov)   {
        if (strcmp(eleje->allat_neve, allat_neve)==0 && strcmp(eleje->faj, allat_faja)==0) {
            talalatok_szama++;
            printf("%s %s: %s\n", eleje->tulaj_vezneve, eleje->tulaj_keresztnev, eleje->tulaj_elerhetoseg);
            printf("Azonosito, nev, faj, diagnozis: %d %s %s: %s\n", eleje->azonosito, eleje->allat_neve, eleje->faj, eleje->diagnozis);
            printf("Utolso oltas idopontja(ev,ho,nap): %d.%d.%d\n", eleje->oltas_eve, eleje->oltas_honap, eleje->oltas_nap);
        }
    }
    if (talalatok_szama == 0) {
        printf("Nincs talalat.");
    }
}
