#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KNIG 100
#define MAX_LUDEY 50
#define MAX_OPER 200

struct Kniga {
    int id;
    char nazvanie[50];
    char avtor[50];
    int god;
    int est;          // ñêîëüêî åñòü â íàëè÷èè
    int vzyato;       // ñêîëüêî âçÿòî
};

// Ñòðóêòóðà äëÿ ÷èòàòåëÿ
struct Chel {
    int id;
    char imya[30];
    char fam[30];
    int kartochka;
    int skolko_vzyal; // ñêîëüêî êíèã íà ðóêàõ
};

// Ñòðóêòóðà äëÿ âûäà÷è
struct Vydacha {
    int id_knigi;
    int id_chel;
    int data;        // óïðîùåííàÿ äàòà (äåíü ìåñÿöà)
    int vernul;      // 0 - íå âåðíóë, 1 - âåðíóë
};

// ãëîáàë ïåðåìåííûå
Kniga knigi[MAX_KNIG];
Chel ludi[MAX_LUDEY];
Vydacha oper[MAX_OPER];
int kolvo_knig = 0;
int kolvo_ludey = 0;
int kolvo_oper = 0;

// Ôóíêöèÿ î÷èñòêè áóôåðà
void ochistit() {
    while (getchar() != '\n');
}

// Ïîêàçàòü ìåíþ
void pokazat_menu() {
    printf("\n=== ÁÈÁËÈÎÒÅÊÀ ===\n");
    printf("1. Äîáàâèòü êíèãó\n");
    printf("2. Ïîêàçàòü âñå êíèãè\n");
    printf("3. Äîáàâèòü ÷èòàòåëÿ\n");
    printf("4. Ïîêàçàòü âñåõ ÷èòàòåëåé\n");
    printf("5. Âûäàòü êíèãó\n");
    printf("6. Âåðíóòü êíèãó\n");
    printf("7. Ñîõðàíèòü â ôàéë\n");
    printf("8. Çàãðóçèòü èç ôàéëà\n");
    printf("0. Âûéòè\n");
    printf("Âûáåðèòå: ");
}

// Äîáàâèòü êíèæêó
void dobavit_knigu() {
    if (kolvo_knig >= MAX_KNIG) {
        printf("Ñëèøêîì ìíîãî êíèã!\n");
        return;
    }

    printf("\n--- Íîâàÿ êíèæêà ---\n");

    knigi[kolvo_knig].id = kolvo_knig + 1;

    printf("Íàçâàíèå: ");
    fgets(knigi[kolvo_knig].nazvanie, 50, stdin);
    knigi[kolvo_knig].nazvanie[strlen(knigi[kolvo_knig].nazvanie) - 1] = '\0';

    printf("Àâòîð: ");
    fgets(knigi[kolvo_knig].avtor, 50, stdin);
    knigi[kolvo_knig].avtor[strlen(knigi[kolvo_knig].avtor) - 1] = '\0';

    printf("Ãîä: ");
    scanf("%d", &knigi[kolvo_knig].god);

    printf("Ñêîëüêî øòóê: ");
    scanf("%d", &knigi[kolvo_knig].est);

    knigi[kolvo_knig].vzyato = 0;
    kolvo_knig++;

    printf("Êíèæêà äîáàâëåíà! ID=%d\n", kolvo_knig);
    ochistit();
}

// Ïîêàçàòü âñå êíèæêè
void pokazat_knigi() {
    printf("\n--- Âñå êíèãè ---\n");
    if (kolvo_knig == 0) {
        printf("Êíèã ïîêà íåò\n");
        return;
    }

    for (int i = 0; i < kolvo_knig; i++) {
        printf("%d. %s (àâòîð: %s) - %d øò, ñâîáîäíî: %d\n",
            knigi[i].id,
            knigi[i].nazvanie,
            knigi[i].avtor,
            knigi[i].est,
            knigi[i].est - knigi[i].vzyato);
    }
}

// Äîáàâèòü ÷èòàòåëÿ
void dobavit_chitatelya() {
    if (kolvo_ludey >= MAX_LUDEY) {
        printf("Ñëèøêîì ìíîãî ÷èòàòåëåé!\n");
        return;
    }

    printf("\n--- Íîâûé ÷èòàòåëü ---\n");

    ludi[kolvo_ludey].id = kolvo_ludey + 1;

    printf("Èìÿ: ");
    fgets(ludi[kolvo_ludey].imya, 30, stdin);
    ludi[kolvo_ludey].imya[strlen(ludi[kolvo_ludey].imya) - 1] = '\0';

    printf("Ôàìèëèÿ: ");
    fgets(ludi[kolvo_ludey].fam, 30, stdin);
    ludi[kolvo_ludey].fam[strlen(ludi[kolvo_ludey].fam) - 1] = '\0';

    printf("Íîìåð êàðòî÷êè: ");
    scanf("%d", &ludi[kolvo_ludey].kartochka);

    ludi[kolvo_ludey].skolko_vzyal = 0;
    kolvo_ludey++;

    printf("×èòàòåëü äîáàâëåí! ID=%d\n", kolvo_ludey);
    ochistit();
}

// Ïîêàçàòü âñåõ ÷èòàòåëåé
void pokazat_chitateley() {
    printf("\n--- Âñå ÷èòàòåëè ---\n");
    if (kolvo_ludey == 0) {
        printf("×èòàòåëåé ïîêà íåò\n");
        return;
    }

    for (int i = 0; i < kolvo_ludey; i++) {
        printf("%d. %s %s (êàðòî÷êà: %d) - êíèã íà ðóêàõ: %d\n",
            ludi[i].id,
            ludi[i].imya,
            ludi[i].fam,
            ludi[i].kartochka,
            ludi[i].skolko_vzyal);
    }
}

// Âûäàòü êíèæêó
void vydat_knigu() {
    int id_kn, id_ch;

    printf("\n--- Âûäà÷à êíèãè ---\n");

    printf("ID êíèãè: ");
    scanf("%d", &id_kn);

    printf("ID ÷èòàòåëÿ: ");
    scanf("%d", &id_ch);

    ochistit();

    // Ïðîâåðÿåì
    if (id_kn < 1 || id_kn > kolvo_knig) {
        printf("Íåò òàêîé êíèãè!\n");
        return;
    }

    if (id_ch < 1 || id_ch > kolvo_ludey) {
        printf("Íåò òàêîãî ÷èòàòåëÿ!\n");
        return;
    }

    // Èíäåêñû â ìàññèâå
    int idx_kn = id_kn - 1;
    int idx_ch = id_ch - 1;

    // Ïðîâåðÿåì åñòü ëè ñâîáîäíûå
    if (knigi[idx_kn].est - knigi[idx_kn].vzyato <= 0) {
        printf("Íåò ñâîáîäíûõ ýêçåìïëÿðîâ ýòîé êíèæêè!\n");
        return;
    }

    // Ïðîâåðÿåì íå ìíîãî ëè ó ÷èòàòåëÿ
    if (ludi[idx_ch].skolko_vzyal >= 5) {
        printf("Ó ÷èòàòåëÿ óæå 5 êíèã! Áîëüøå íåëüçÿ.\n");
        return;
    }

    // Âûäàåì
    knigi[idx_kn].vzyato++;
    ludi[idx_ch].skolko_vzyal++;

    // Çàïîìèíàåì îïåðàöèþ
    oper[kolvo_oper].id_knigi = id_kn;
    oper[kolvo_oper].id_chel = id_ch;
    oper[kolvo_oper].data = 15; // ïðîñòî ïðèìåð äàòû
    oper[kolvo_oper].vernul = 0;
    kolvo_oper++;

    printf("Êíèãà âûäàíà óñïåøíî!\n");
}

// Âåðíóòü êíèæêó
void vernut_knigu() {
    int id_kn, id_ch;

    printf("\n--- Âîçâðàò êíèãè ---\n");

    printf("ID êíãè: ");
    scanf("%d", &id_kn);

    printf("ID ÷èòàòåëÿ: ");
    scanf("%d", &id_ch);

    ochistit();

    // Ïðîâåðÿåì
    if (id_kn < 1 || id_kn > kolvo_knig) {
        printf("Íåò òàêîé êíèãè!\n");
        return;
    }

    if (id_ch < 1 || id_ch > kolvo_ludey) {
        printf("Íåò òàêîãî ÷èòàòåëÿ!\n");
        return;
    }

    // Èíäåêñû
    int idx_kn = id_kn - 1;
    int idx_ch = id_ch - 1;

    // Ïðîâåðÿåì áûëà ëè òàêàÿ âûäà÷à
    int naideno = 0;
    for (int i = 0; i < kolvo_oper; i++) {
        if (oper[i].id_knigi == id_kn &&
            oper[i].id_chel == id_ch &&
            oper[i].vernul == 0) {
            oper[i].vernul = 1; // îòìå÷àåì êàê âîçâðàùåííóþ
            naideno = 1;
            break;
        }
    }

    if (!naideno) {
        printf("Òàêîé âûäà÷è íå íàéäåíî!\n");
        return;
    }

    // Îáíîâëÿåì ñ÷åò÷èêè
    if (knigi[idx_kn].vzyato > 0) knigi[idx_kn].vzyato--;
    if (ludi[idx_ch].skolko_vzyal > 0) ludi[idx_ch].skolko_vzyal--;

    printf("Êíèæêà âîçâðàùåíà!\n");
}

// Ñîõðàíèòü â ôàéë (î÷åíü ïðîñòî)
void sohranit() {
    FILE* f;

    // Ñîõðàíÿåì êíèæêè
    f = fopen("knigi.dat", "wb");
    if (f != NULL) {
        fwrite(&kolvo_knig, sizeof(int), 1, f);
        fwrite(knigi, sizeof(Kniga), kolvo_knig, f);
        fclose(f);
        printf("Êíèãè ñîõðàíåíû\n");
    }

    // Ñîõðàíÿåì ÷èòàòåëåé
    f = fopen("ludi.dat", "wb");
    if (f != NULL) {
        fwrite(&kolvo_ludey, sizeof(int), 1, f);
        fwrite(ludi, sizeof(Chel), kolvo_ludey, f);
        fclose(f);
        printf("×èòàòåëè ñîõðàíåíû\n");
    }
}

// Çàãðóçèòü èç ôàéëà
void zagruzit() {
    FILE* f;

    // Çàãðóæàåì êíèæêè
    f = fopen("knigi.dat", "rb");
    if (f != NULL) {
        fread(&kolvo_knig, sizeof(int), 1, f);
        fread(knigi, sizeof(Kniga), kolvo_knig, f);
        fclose(f);
        printf("Çàãðóæåíî êíèã: %d\n", kolvo_knig);
    }
    else {
        printf("Ôàéë ñ êíèæêàìè íå íàéäåí\n");
    }

    // Çàãðóæàåì ÷èòàòåëåé
    f = fopen("ludi.dat", "rb");
    if (f != NULL) {
        fread(&kolvo_ludey, sizeof(int), 1, f);
        fread(ludi, sizeof(Chel), kolvo_ludey, f);
        fclose(f);
        printf("Çàãðóæåíî ÷èòàòåëåé: %d\n", kolvo_ludey);
    }
    else {
        printf("Ôàéë ñ ÷èòàòåëÿìè íå íàéäåí\n");
    }
}

// Ãëàâíàÿ ôóíêöèÿ
int main() {
    int vibor;

    printf("ÁÈÁËÈÎÒÅ×ÍÀß ÑÈÑÒÅÌÀ v1.0\n");
    printf("Àâòîðû: Àë¸õèí Ïàâåë è Ãàíè÷åâ Àäðåé\n\n");

    do {
        pokazat_menu();
        scanf("%d", &vibor);
        ochistit();

        switch (vibor) {
        case 1: dobavit_knigu(); break;
        case 2: pokazat_knigi(); break;
        case 3: dobavit_chitatelya(); break;
        case 4: pokazat_chitateley(); break;
        case 5: vydat_knigu(); break;
        case 6: vernut_knigu(); break;
        case 7: sohranit(); break;
        case 8: zagruzit(); break;
        case 0:
            printf("Ñîõðàíÿþ ïåðåä âûõîäîì...\n");
            sohranit();
            printf("Äî ñâèäàíèÿ!\n");
            break;
        default:
            printf("Íåâåðíûé âûáîð! Ïîïðîáóéòå ñíîâà.\n");
        }
    } while (vibor != 0);

    return 0;

}
