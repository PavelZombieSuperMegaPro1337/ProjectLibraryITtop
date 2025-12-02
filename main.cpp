#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// Максимальное количество всего
#define MAX_KNIG 100
#define MAX_LUDEY 50
#define MAX_OPER 200

// Структура для книжки
struct Kniga {
    int id;
    char nazvanie[50];
    char avtor[50];
    int god;
    int est;          // сколько есть в наличии
    int vzyato;       // сколько взято
};

// Структура для читателя
struct Chel {
    int id;
    char imya[30];
    char fam[30];
    int kartochka;
    int skolko_vzyal; // сколько книг сейчас у него
};

// Структура для выдачи
struct Vydacha {
    int id_knigi;
    int id_chel;
    int data;        // упрощенная дата (день месяца)
    int vernul;      // 0 - не вернул, 1 - вернул
};

// Глобальные переменные (так проще)
Kniga knigi[MAX_KNIG];
Chel ludi[MAX_LUDEY];
Vydacha oper[MAX_OPER];
int kolvo_knig = 0;
int kolvo_ludey = 0;
int kolvo_oper = 0;

// Функция очистки буфера
void ochistit() {
    while (getchar() != '\n');
}

// Показать меню
void pokazat_menu() {
    printf("\n=== БИБЛИОТЕКА ===\n");
    printf("1. Добавить книгу\n");
    printf("2. Показать все книги\n");
    printf("3. Добавить читателя\n");
    printf("4. Показать всех читателей\n");
    printf("5. Выдать книгу\n");
    printf("6. Вернуть книгу\n");
    printf("7. Сохранить в файл\n");
    printf("8. Загрузить из файла\n");
    printf("0. Выйти\n");
    printf("Выберите: ");
}

// Добавить книжку
void dobavit_knigu() {
    if (kolvo_knig >= MAX_KNIG) {
        printf("Слишком много книг!\n");
        return;
    }

    printf("\n--- Новая книга ---\n");

    knigi[kolvo_knig].id = kolvo_knig + 1;

    printf("Название: ");
    fgets(knigi[kolvo_knig].nazvanie, 50, stdin);
    knigi[kolvo_knig].nazvanie[strlen(knigi[kolvo_knig].nazvanie) - 1] = '\0';

    printf("Автор: ");
    fgets(knigi[kolvo_knig].avtor, 50, stdin);
    knigi[kolvo_knig].avtor[strlen(knigi[kolvo_knig].avtor) - 1] = '\0';

    printf("Год: ");
    scanf("%d", &knigi[kolvo_knig].god);

    printf("Сколько штук: ");
    scanf("%d", &knigi[kolvo_knig].est);

    knigi[kolvo_knig].vzyato = 0;
    kolvo_knig++;

    printf("Книга добавлена! ID=%d\n", kolvo_knig);
    ochistit();
}

// Показать все книги
void pokazat_knigi() {
    printf("\n--- Все книги ---\n");
    if (kolvo_knig == 0) {
        printf("Книг пока нет\n");
        return;
    }

    for (int i = 0; i < kolvo_knig; i++) {
        printf("%d. %s (автор: %s) - %d шт, свободно: %d\n",
            knigi[i].id,
            knigi[i].nazvanie,
            knigi[i].avtor,
            knigi[i].est,
            knigi[i].est - knigi[i].vzyato);
    }
}

// Добавить читателя
void dobavit_chitatelya() {
    if (kolvo_ludey >= MAX_LUDEY) {
        printf("Слишком много читателей!\n");
        return;
    }

    printf("\n--- Новый читатель ---\n");

    ludi[kolvo_ludey].id = kolvo_ludey + 1;

    printf("Имя: ");
    fgets(ludi[kolvo_ludey].imya, 30, stdin);
    ludi[kolvo_ludey].imya[strlen(ludi[kolvo_ludey].imya) - 1] = '\0';

    printf("Фамилия: ");
    fgets(ludi[kolvo_ludey].fam, 30, stdin);
    ludi[kolvo_ludey].fam[strlen(ludi[kolvo_ludey].fam) - 1] = '\0';

    printf("Номер карточки: ");
    scanf("%d", &ludi[kolvo_ludey].kartochka);

    ludi[kolvo_ludey].skolko_vzyal = 0;
    kolvo_ludey++;

    printf("Читатель добавлен! ID=%d\n", kolvo_ludey);
    ochistit();
}

// Показать всех читателей
void pokazat_chitateley() {
    printf("\n--- Все читатели ---\n");
    if (kolvo_ludey == 0) {
        printf("Читателей пока нет\n");
        return;
    }

    for (int i = 0; i < kolvo_ludey; i++) {
        printf("%d. %s %s (карточка: %d) - книг на руках: %d\n",
            ludi[i].id,
            ludi[i].imya,
            ludi[i].fam,
            ludi[i].kartochka,
            ludi[i].skolko_vzyal);
    }
}

// Выдать книгу
void vydat_knigu() {
    int id_kn, id_ch;

    printf("\n--- Выдача книжки ---\n");

    printf("ID книжки: ");
    scanf("%d", &id_kn);

    printf("ID читателя: ");
    scanf("%d", &id_ch);

    ochistit();

    // Проверяем
    if (id_kn < 1 || id_kn > kolvo_knig) {
        printf("Нет такой книжки!\n");
        return;
    }

    if (id_ch < 1 || id_ch > kolvo_ludey) {
        printf("Нет такого читателя!\n");
        return;
    }

    // Индексы в массиве
    int idx_kn = id_kn - 1;
    int idx_ch = id_ch - 1;

    // Проверяем есть ли свободные
    if (knigi[idx_kn].est - knigi[idx_kn].vzyato <= 0) {
        printf("Нет свободных экземпляров этой книжки!\n");
        return;
    }

    // Проверяем не много ли у читателя
    if (ludi[idx_ch].skolko_vzyal >= 5) {
        printf("У читателя уже 5 книг! Больше нельзя.\n");
        return;
    }

    // Выдаем
    knigi[idx_kn].vzyato++;
    ludi[idx_ch].skolko_vzyal++;

    // Запоминаем операцию
    oper[kolvo_oper].id_knigi = id_kn;
    oper[kolvo_oper].id_chel = id_ch;
    oper[kolvo_oper].data = 15; // просто пример даты
    oper[kolvo_oper].vernul = 0;
    kolvo_oper++;

    printf("Книжка выдана успешно!\n");
}

// Вернуть книжку
void vernut_knigu() {
    int id_kn, id_ch;

    printf("\n--- Возврат книжки ---\n");

    printf("ID книжки: ");
    scanf("%d", &id_kn);

    printf("ID читателя: ");
    scanf("%d", &id_ch);

    ochistit();

    // Проверяем
    if (id_kn < 1 || id_kn > kolvo_knig) {
        printf("Нет такой книги!\n");
        return;
    }

    if (id_ch < 1 || id_ch > kolvo_ludey) {
        printf("Нет такого читателя!\n");
        return;
    }

    // Индексы
    int idx_kn = id_kn - 1;
    int idx_ch = id_ch - 1;

    // Проверяем была ли такая выдача
    int naideno = 0;
    for (int i = 0; i < kolvo_oper; i++) {
        if (oper[i].id_knigi == id_kn &&
            oper[i].id_chel == id_ch &&
            oper[i].vernul == 0) {
            oper[i].vernul = 1; // отмечаем как возвращенную
            naideno = 1;
            break;
        }
    }

    if (!naideno) {
        printf("Такой выдачи не найдено!\n");
        return;
    }

    // Обновляем счетчики
    if (knigi[idx_kn].vzyato > 0) knigi[idx_kn].vzyato--;
    if (ludi[idx_ch].skolko_vzyal > 0) ludi[idx_ch].skolko_vzyal--;

    printf("Книжка возвращена!\n");
}

// Сохранить в файл
void sohranit() {
    FILE* f;

    // Сохраняем книги
    f = fopen("knigi.dat", "wb");
    if (f != NULL) {
        fwrite(&kolvo_knig, sizeof(int), 1, f);
        fwrite(knigi, sizeof(Kniga), kolvo_knig, f);
        fclose(f);
        printf("Книги сохранены\n");
    }

    // Сохраняем читателей
    f = fopen("ludi.dat", "wb");
    if (f != NULL) {
        fwrite(&kolvo_ludey, sizeof(int), 1, f);
        fwrite(ludi, sizeof(Chel), kolvo_ludey, f);
        fclose(f);
        printf("Читатели сохранены\n");
    }
}

// Загрузить из файла
void zagruzit() {
    FILE* f;

    // Загружаем книги
    f = fopen("knigi.dat", "rb");
    if (f != NULL) {
        fread(&kolvo_knig, sizeof(int), 1, f);
        fread(knigi, sizeof(Kniga), kolvo_knig, f);
        fclose(f);
        printf("Загружено книг: %d\n", kolvo_knig);
    }
    else {
        printf("Файл с книгами не найден\n");
    }

    // Загружаем читателей
    f = fopen("ludi.dat", "rb");
    if (f != NULL) {
        fread(&kolvo_ludey, sizeof(int), 1, f);
        fread(ludi, sizeof(Chel), kolvo_ludey, f);
        fclose(f);
        printf("Загружено читателей: %d\n", kolvo_ludey);
    }
    else {
        printf("Файл с читателями не найден\n");
    }
}

// Главная функция
int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    int vibor;

    printf("БИБЛИОТЕЧНАЯ СИСТЕМА v1.0\n");
    printf("Автор: Алёхин Павел \n\n");

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
            printf("Сохраняю перед выходом...\n");
            sohranit();
            printf("До свидания!\n");
            break;
        default:
            printf("Неверный выбор! Попробуйте снова.\n");
        }
    } while (vibor != 0);

    return 0;
}
