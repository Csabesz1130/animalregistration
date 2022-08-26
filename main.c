#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debugmalloc.h"
#include "fuggvenyek.h"

int main(void)
{
    FILE *fp;
    char const *filename = "allatokadatbazis.txt";
    //Allatok *teljes_lista;
    Allatok *teljes_lista = lista_beolvas(fp, filename);
    int valasz;
    do {
        printf("**********************************************\n\n");
        printf("Valassza ki a listabol, hogy mit szeretne csinalni.\n\n");
        printf("(1) - Kiirathatja az osszes allatot (egesz lista).\n");
        printf("(2) - Kereshet az allatok kozott.\n");
        printf("(3) - Bevihet uj allatot a listaba.\n");
        printf("(4) - Torolhet allatot a listabol.\n");
        printf("(5) - Modosithatja adott allat adatait.\n");
        printf("(6) - Kiirathatja a beoltando allatokat tulajdonos szerint.\n");
        printf("(7) - Kilepes.\n");
        printf("\n**********************************************\n\n");
        printf("A On valasza:\n");
        scanf("%d", &valasz);
        int kereses_modja;
        int azonosito = azonosito_gen(teljes_lista, filename);
        /*if (teljes_lista == NULL) {
            perror("Hiba adodott.");
            exit(1);
        }*/
        char allat_neve[30];
        char telefonszam[20];
        Allatok *teljes_lista = lista_beolvas(fp, filename);
        switch(valasz) {
            case 1:
                    printf("\n");
                    lista_kiir(teljes_lista);
                    break;
            case 2:
                    printf("Hogyan szeretne keresni (mi alapjan)?\n");
                    printf("(11) - Allat neve es telefonszam.\n");
                    printf("(12) - Allat neve es tulajdnos neve (vezeteknev, keresztnev).\n");
                    printf("(13) - Allat neve es faja.\n");
                    printf("Az On valasza: ");
                    scanf("%d", &kereses_modja);
                    if (kereses_modja == 11) {
                        char allat_neve[30];
                        char telefonszam[20];
                        //printf("Adja meg az allat nevet es a telefonszamot.(szokozzel elvalasztva)\n");
                        //scanf("%s %s", allat_neve, telefonszam);
                        keres_allatnev_telefon(teljes_lista, allat_neve, telefonszam);
                    }
                    else if (kereses_modja == 12) {
                        char allat_neve[30];
                        char tulaj_vezneve[30];
                        char tulaj_keresztneve[30];
                        printf("Adja meg az allat nevet es tulajdonos vezetek-, keresztnevet:\n");
                        printf("Allat neve:\n");
                        scanf("%s", allat_neve);
                        printf("Tulajdonos vezetekneve:\n");
                        scanf("%s", tulaj_vezneve);
                        printf("Tulajdonos keresztneve:\n");
                        scanf("%s", tulaj_keresztneve);
                        keres_allatnev_tulajnev(teljes_lista, allat_neve, tulaj_vezneve, tulaj_keresztneve);
                    }
                    else if (kereses_modja == 13) {
                        char allat_neve[30];
                        char faj[30];
                        printf("Adja meg az allat fajat es nevet.\n");
                        printf("Allat neve:\n");
                        scanf("%s", allat_neve);
                        printf("Adja meg a fajat:\n");
                        scanf("%s", faj);
                        keres_faj_allatneve(teljes_lista, allat_neve, faj);
                    }
                    else {
                        valasz=7;
                    }
                    break;
            case 3:
                bevisz_adat(filename, azonosito);
                printf("\n");
                break;
            case 4:
                printf("Allat neve:\n");
                scanf("%s", allat_neve);
                printf("Tulajdonos telefonszama:\n");
                scanf("%s", telefonszam);
                torol_adat(teljes_lista, allat_neve, telefonszam);
                lista_kiir(teljes_lista);
                visszair(teljes_lista ,fp, filename);
                break;
            case 5:
                fflush(stdin);
                printf("Torlendo allat neve:\n");
                gets(allat_neve);
                printf("Tulajdonosanak telefonszama:\n");
                gets(telefonszam);
                allat_modosit(teljes_lista, telefonszam ,allat_neve);
                visszair(teljes_lista, fp, filename);
                break;
            case 6:
                printf("Oltando allatok listaja:\n\n");
                int ev, honap, nap;
                kiir_oltando(teljes_lista, ev, honap, nap);
                break;

        }

    } while(valasz != 7);
    printf("Bezarhatja az ablakot, befejezte a muveleteket.");
    lista_felszabadit(teljes_lista);
    return 0;
}
