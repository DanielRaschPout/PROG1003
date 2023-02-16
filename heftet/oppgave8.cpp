/**
 * 
 *  Programmet:
 *     - har leser inn og skriver ut kamper
 * 
 * @file oppgave8.cpp
 * @author Daniel Fernando Petter Rasch-Pout (dfraschp@gmail.com)
 * @brief 
 * @version 0.1
 * @date 16-02-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */
 * @file oppgave8.cpp
 * @author Daniel Fernando Petter Rasch-Pout (dfraschp@gmail.com)
 * @brief 
 * @version 0.1
 * @date 16-02-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>                //  cout, cin
#include <string>                  //  string-klassen
#include <vector>                  //  vector
#include "LesData2.h"              //  Verktøykasse for lesing av diverse data
using namespace std;

struct Kamp {
    string hjemmelag, bortelag;
    int hjemmescoringer, bortescoringer;
};

void skrivMeny();
void nyKamp();
void kampLesData(Kamp & kamp);
void kampSkrivData(const Kamp* kamp);
void skrivAlleKamper();
void slettAlleKamper();

vector <Kamp*> gKampene;

int main () {

    char kommando;
    skrivMeny();
    kommando = lesChar("\nKommando");

    while (kommando != 'Q') {

        switch (kommando) {
            case 'N': nyKamp();            break;
            case 'A': skrivAlleKamper();   break;
            default:  skrivMeny();         break;
        } // switch end

        skrivMeny();
        kommando = lesChar("\nKommando");
    }

    slettAlleKamper();
    return 0;
}

void skrivMeny() {
    cout << "N: Ny kamp" << '\n';
    cout << "A: Skriv alle kamper" << '\n';
    cout << "Q: Avslutt" << '\n';
}

void nyKamp() {
    Kamp* kamp = new Kamp;
    kampLesData(*kamp);
    gKampene.push_back(kamp);
}

void kampLesData(Kamp & kamp) {
    cout << "Hjemmelag: ";
    getline(cin, kamp.hjemmelag);
    cout << "Bortelag: ";
    getline(cin, kamp.bortelag);
    kamp.hjemmescoringer = lesInt("Hjemmescoringer", 0, 100);
    kamp.bortescoringer = lesInt("Bortescoringer", 0, 100);
}

void kampSkrivData(const Kamp* kamp) {
    cout << kamp->hjemmelag << " - " << kamp->bortelag << " " << kamp->hjemmescoringer << " - " << kamp->bortescoringer << '\n';
}

void skrivAlleKamper() {
    for (auto kamp : gKampene) {
        kampSkrivData(kamp);
    }
}

void slettAlleKamper() {
    for (auto kamp : gKampene) {
        delete kamp;
    }
}