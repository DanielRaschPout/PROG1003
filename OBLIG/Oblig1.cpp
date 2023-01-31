/**
 * @file Oblig1.cpp
 * @author Daniel Fernando Petter Rasch-Pout (dfraschp@gmail.com)
 * @brief 
 * @version 0.1
 * @date 31-01-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>                //  cout, cin
#include <string>                  //  string-klassen
#include <vector>                  //  vector
#include "LesData2.h"              //  Verkt�ykasse for lesing av diverse data
using namespace std;

const vector <string> UKEDAG { "Man", "Tirs", "Ons", "Tors",
                               "Fre", "Lor", "Son" };

struct Gjoremaal {
    string beskrivelse, // Beskrivelse av gjøremålet.
    ukedag; // Ukedagen det skjer.
    float tid; // Tiden det tar (0.5 til 12.0 timer) – ikke klokkeslett
    };

vector <Gjoremaal*> gGjoremaalene; ///< Oversikt over alle gjøremålene.
void fjernAlleGjoremaal();
void fjernEttGjoremaal();
void gjoremaalLesData(Gjoremaal & gjoremaal);
void gjoremaalSkrivData(const Gjoremaal* gjoremaal);
void nyttGjoremaal();
void skrivAlleGjoremaal(const string dag = "Alle");
void skrivEnDagsGjoremaal();
void skrivMeny();

/**
 * Hovedprogrammet:
 */
int main() {

    char kommando;
    skrivMeny();
    kommando = lesChar("\nKommando");

    while (kommando != 'Q') {

        switch (kommando) {
            case 'N': nyttGjoremaal();        break;
            case 'A': skrivAlleGjoremaal();   break;
            case 'D': skrivEnDagsGjoremaal(); break;
            case 'F': fjernEttGjoremaal();    break;
            default:  skrivMeny();            break;
        } // switch end

    kommando = lesChar("\nKommando");
    } // while end
    fjernAlleGjoremaal();

    return 0;
} // main end

/**
 * @brief Fjerner alle gjøremålene.
 * 
 */
void skrivMeny() {
    cout << "N: Nytt gj�rem�l" << '\n';
    cout << "A: Skriv alle gj�rem�l" << '\n';
    cout << "D: Skriv en dags gj�rem�l" << '\n';
    cout << "F: Fjern et gj�rem�l" << '\n';
    cout << "Q: Avslutt" << '\n';
} // skrivMeny end

/**
 * @brief Legger til et nytt gjøremål.
 * 
 */
void nyttGjoremaal() {
    Gjoremaal* gjoremaal = new Gjoremaal;
    gjoremaalLesData(*gjoremaal);
    gGjoremaalene.push_back(gjoremaal);
} // nyttGjoremaal end

/**
 * @brief Leser inn data for et nytt gjøremål.
 * 
 */
void gjoremaalLesData(Gjoremaal & gjoremaal) {
    cout << "Beskrivelse: ";
    getline(cin, gjoremaal.beskrivelse);
    cout << "Ukedag: ";
    getline(cin, gjoremaal.ukedag);
    gjoremaal.tid = lesFloat("Tid", 0.5, 12.0);
} // gjoremaalLesData end

/**
 * @brief Skriver all data til ett gjøremål.
 * 
 */
void gjoremaalSkrivData(const Gjoremaal* gjoremaal) {
    cout << "Beskrivelse: " << gjoremaal->beskrivelse << '\n';
    cout << "Ukedag: " << gjoremaal->ukedag << '\n';
    cout << "Tid: " << gjoremaal->tid << '\n';
} // gjoremaalSkrivData end

/**
 * @brief Skriver ut alle gjøremålene.
 * 
 */
void skrivAlleGjoremaal(const string dag = "Alle") {
    if (gGjoremaalene.size() == 0) {
        cout << "Ingen gj�rem�l � skrive ut" << '\n';
    } // if end
    
    else {
        for (int i = 0; i < gGjoremaalene.size(); i++) {
            if (dag == "Alle" || gGjoremaalene[i]->ukedag == dag) {
                gjoremaalSkrivData(gGjoremaalene[i]);
                cout << '\n';
            } // if end
        } // for end
    } // else end
} // skrivAlleGjoremaal end

void skrivEnDagsGjoremaal() {
    int dagNr = lesInt("Dag", 1, 7);
    skrivAlleGjoremaal(dag);
} // skrivEnDagsGjoremaal end

void fjernEttGjoremaal() {
    if (gGjoremaalene.size() == 0) {
        cout << "Ingen gj�rem�l � fjerne" << '\n';
        return;
    } // if end
    else {
        int index = lesInt("Gj�rem�lsnummer", 1, gGjoremaalene.size());
        delete gGjoremaalene[index - 1];
        gGjoremaalene.erase(gGjoremaalene.begin() + index - 1);
    } // else end
} // fjernEttGjoremaal end

void fjernAlleGjoremaal() {
    for (int i = 0; i < gGjoremaalene.size(); i++) {
        delete gGjoremaalene[i];
    } // for end
    gGjoremaalene.clear();
} // fjernAlleGjoremaal end