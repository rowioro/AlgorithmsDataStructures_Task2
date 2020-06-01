#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

struct SAuto
{
    string marka, model;
    int pred_maks;
    SAuto* next;
};

SAuto* utworz_liste()
{
    SAuto* glowa, * aktualny, * ogon;

    ifstream we("cars.txt");
    if (!we.good())
    {
        cout << "Problem z otwarciem pliku!" << endl;
        exit(0);
    }

    aktualny = NULL;
    glowa = NULL;

    while (!we.eof())
    {
        ogon = aktualny;
        aktualny = new SAuto;

        we >> aktualny->marka;
        we >> aktualny->model;
        we >> aktualny->pred_maks;

        aktualny->next = NULL;

        if (ogon == NULL)
            glowa = aktualny;
        else
            ogon->next = aktualny;

    }
    we.close();

    return glowa;
}

void drukuj_liste(SAuto* adres)
{
    while (adres != NULL)
    {
        cout << setw(10) << adres->marka << setw(5) << " ";
        cout << setw(10) << adres->model << setw(5) << " ";
        cout << setw(10) << adres->pred_maks << setw(5) << " ";
        adres = adres->next;
        cout << endl;
    }
    cout << endl;
}

void dopisz(SAuto* gdzie, SAuto* nowy)
{
    if (gdzie != NULL)
    {
        SAuto* tmp;
        tmp = gdzie->next;
        gdzie->next = nowy;
        nowy->next = tmp;
    }
}

void usun(SAuto*& glowa)
{
    SAuto* tmp;
    while (glowa != NULL)
    {
        tmp = glowa;
        glowa = glowa->next;
        delete tmp;
    }
}

int main()
{
    SAuto* glowa, * aktualny, * ogon, * nowy;
    int ile, suma;

    glowa = utworz_liste();

    drukuj_liste(glowa);

    cout << "Podaj dane nowego samochodu." << endl;
    nowy = new SAuto;
    cout << "Marka: ";
    cin >> nowy->marka;
    cout << "Model: ";
    cin >> nowy->model;
    cout << "Predkosc maksymalna: ";
    cin >> nowy->pred_maks;
    cout << endl;

    ogon = glowa;
    while (ogon->next != NULL)
        ogon = ogon->next;

    dopisz(ogon, nowy);

    drukuj_liste(glowa);

    ile = 0;
    suma = 0;
    aktualny = glowa;
    while (aktualny != NULL)
    {
        ile++;
        suma += aktualny->pred_maks;
        aktualny = aktualny->next;
    }
    cout << "Srednia predkosc maksymalna samochodow na liscie = " << suma / ile << endl;

    cout << "Modele samochodow o predkosci maksymalnej ponizej sredniej:" << endl;
    aktualny = glowa;
    while (aktualny != NULL)
    {
        if (aktualny->pred_maks < suma / ile)
            cout << aktualny->model << endl;
        aktualny = aktualny->next;
    }

    usun(glowa);
    drukuj_liste(glowa);

    return 0;
}
