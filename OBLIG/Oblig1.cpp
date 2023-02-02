/**
 * 
 *    Programmet:
 *      - har oversikt over og skriver ut gjøremål
 *     - lar en bruker legge inn nye og fjerne gjøremål
 * 
 * @file Oblig1.cpp
 * @author Daniel Fernando Petter Rasch-Pout (dfraschp@gmail.com)
 * @brief 
 * @version 1.0
 * @date 02-02-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>                //  cout, cin
#include <string>                  //  string-klassen
#include <vector>                  //  vector
#include "LesData2.h"              //  Verktøykasse for lesing av diverse data
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
 * Printer ut menyen.
 * 
 */
void skrivMeny() {
    cout << "N: Nytt gjøremål" << '\n';
    cout << "A: Skriv alle gjøremål" << '\n';
    cout << "D: Skriv en dags gjøremål" << '\n';
    cout << "F: Fjern et gjøremål" << '\n';
    cout << "Q: Avslutt" << '\n';
} // skrivMeny end

/**
 * Legger til et nytt gjøremål.
 * 
 */
void nyttGjoremaal() {
    Gjoremaal* gjoremaal = new Gjoremaal;
    gjoremaalLesData(*gjoremaal);
    gGjoremaalene.push_back(gjoremaal);
    cout << "Gjøremål nr." << gGjoremaalene.size() << " lagt til" << '\n';
} // nyttGjoremaal end

/**
 * Leser inn data for et nytt gjøremål.
 * 
 * @param gjoremaal Gjøremalet som skal leses inn.
 */
void gjoremaalLesData(Gjoremaal & gjoremaal) {
    cout << "Beskrivelse: ";
    getline(cin, gjoremaal.beskrivelse);

    int dagNr = lesInt("Ukedag", 1, 7);
    gjoremaal.ukedag = UKEDAG[dagNr - 1];
    gjoremaal.tid = lesFloat("Tid", 0.5, 12.0);
} // gjoremaalLesData end

/**
 * Skriver all data til ett gjøremål.
 * 
 * @param gjoremaal Gjøremalet som skal skrives ut.
 */
void gjoremaalSkrivData(const Gjoremaal* gjoremaal) {
    cout << "Beskrivelse: " << gjoremaal->beskrivelse << '\n';
    cout << "Ukedag: " << gjoremaal->ukedag << '\n';
    cout << "Tid: " << gjoremaal->tid << '\n';
} // gjoremaalSkrivData end

/**
 * Skriver ut alle gjøremålene.
 * 
 * @param dag Hvilken dag som skal skrives ut. Hvis "Alle" skrives alle ut.
 */
void skrivAlleGjoremaal(const string dag) {
    
    // Hvis det ikke er noen gjøremål å skrive ut.
    if (gGjoremaalene.size() == 0) {
        cout << "Ingen gjøremål å skrive ut" << '\n';
    } // if end
    
    // Hvis dag er "Alle".
    else if (dag == "Alle") {
        for (int i = 0; i < gGjoremaalene.size(); i++) {

            cout << "Gjøremål nr." << i + 1 << '\n';
            gjoremaalSkrivData(gGjoremaalene[i]);
            cout << '\n';
        } // for end
    } // else if end

    // Hvis dag er en ukedag.
    else {
        for (int i = 0; i < gGjoremaalene.size(); i++) {
            if (gGjoremaalene[i]->ukedag == dag) {
                cout << "Gjøremål nr." << i + 1 << '\n';
                gjoremaalSkrivData(gGjoremaalene[i]);
                cout << '\n';
            } // if end
        } // for end
    } // else end
} // skrivAlleGjoremaal end

/**
 * Skriver ut alle gjøremålene for en gitt dag.
 * 
 */
void skrivEnDagsGjoremaal() {
    int dagNr = lesInt("Dag", 1, 7);
    skrivAlleGjoremaal(UKEDAG[dagNr - 1]);
} // skrivEnDagsGjoremaal end

/**
 * Fjerner et gjøremål.
 * 
 */
void fjernEttGjoremaal() {
    if (gGjoremaalene.size() == 0) {
        cout << "Ingen gjøremål å fjerne" << '\n';
        return;
    } // if end
    else {
        int index = lesInt("Gjøremålsnummer", 1, gGjoremaalene.size());
        delete gGjoremaalene[index - 1];
        gGjoremaalene.erase(gGjoremaalene.begin() + index - 1);
    } // else end
} // fjernEttGjoremaal end

/**
 * Fjerner alle gjøremål.
 * 
 */
void fjernAlleGjoremaal() {
    for (int i = 0; i < gGjoremaalene.size(); i++) {
        delete gGjoremaalene[i];
    } // for end
    gGjoremaalene.clear();
} // fjernAlleGjoremaal end