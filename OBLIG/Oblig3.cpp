/**
 *  Starten på oblig nr 3 - Hotellrombookinger.
 *
 *  Programmet:
 *    - skriver ut på skjermen:
 *          - alle hotellets bookede rom
 *          - status/fakturaen for ett gitt rom
 *    - sjekker en gjest inn/ut
 *    - leser/skriver hele datastrukturen fra/til fil
 
 *  @file Oblig3.cpp
 *  @author  av den innledende/startende koden: 
 *           Malin Foss,  Markus Olsvik,  Øystein Qvigstad  &  FrodeH, NTNU
 */


#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include "LesData2.h"
using namespace std;


const int MAXDOGN            =   14,    ///<  Max.antall døgn mulig å booke.
        LAVESTEROMNR         =  100,    ///<  Hotellets laveste romnummer.
        HOYESTEROMNR         =  999,    ///<  Hotellets høyeste romnummer.
        PRISENKELTROM        = 1000,    ///<  Døgnpris for enkeltrom.
        PRISDOBBELTROM       = 1500,    ///<  Døgnpris for dobbeltrom.
        PRISALLINCLUSIVE     = 1200,    ///<  Døgnpris for 2 stk all inclus.
        PRISFILMPAKKE        =   50,    ///<  Døgnpris for filmpakke.
        PRISFROKOST          =  170,    ///<  Frokostpris - KUN enkeltrom.
        STUDENTRABATTPROSENT =   40;    ///<  Studentrabatt i prosent
                                        //        (gjelder KUN enkeltrom).

/**
 *  Operasjonene som utføres på et rom (ser kundataene eller sjekker ut).
 */
enum romOperasjon  {  seData,  sjekkUt  };


/**
 *  Baseklassen 'Hotellrom' (med gjestens navn og antall bookede døgn).
 */
class Hotellrom {
    protected:
        string navn;                           //  Bookers/gjestens navn.
        int antallDager;                       //  Oppholdets varighet.

    public:
        Hotellrom() {  }
        Hotellrom(ifstream & inn);
        virtual ~Hotellrom()  {  }
        string hentNavn() const  {  return navn;  }
        virtual void lesData();
        virtual void skrivData() const = 0;  // Pure virtual - dvs. subklasser
        virtual void skrivHoveddata() const = 0; // MÅ lage disse funksjonene.
        virtual void skrivTilFil(ofstream & ut) const;
};


/**
 *  Avledet klasse 'Enkeltrom' (med om har frokost og evt studentrabatt).
 */
class Enkeltrom : public Hotellrom {
    private:
        bool frokost,                    //  Bare enkeltrom har studentrabatt!
             studentRabatt;              //  Bare enkeltrom har frokost!

    public:
        Enkeltrom()  {  }
        Enkeltrom(ifstream & inn);
        virtual ~Enkeltrom()  {  }
        virtual void lesData();
        virtual void skrivData() const;
        virtual void skrivHoveddata() const;
        virtual void skrivTilFil(ofstream & ut) const;
};


/**
 *  Avledet klasse 'Dobbeltrom' (med om har All Inclusive og/eller filmpakke).
 */
class Dobbeltrom : public Hotellrom {
    private:
        bool allInclusive,            //  Bare dobbeltrom har 'All inclusive'!
             filmpakke;               //  Bare dobbeltrom har filmpakke!

    public:
        Dobbeltrom()  {  }
        Dobbeltrom(ifstream & inn);
        virtual ~Dobbeltrom()  {  }
        virtual void lesData();
        virtual void skrivData() const;
        virtual void skrivHoveddata() const;
        virtual void skrivTilFil(ofstream & ut) const;
};


void bookRom();
void lesFraFil();
void rom(const romOperasjon sDsU);
void skrivAlleRommene();
void skrivBookedeRomnumre();
void skrivMeny();
void skrivTilFil();


map <int, Hotellrom*> gHotellRommene;      ///<  Alle hotellrommene.


/**
 *  Hovedprogram.
 */
int main() {
    char menyvalg;

    lesFraFil();

    skrivMeny();
    menyvalg = lesChar("\nMenyvalg");

    while (menyvalg != 'Q')  {
        switch (menyvalg) {
            case 'S':  skrivAlleRommene(); break;
            case 'B':  bookRom();          break;
            case 'F':  rom(seData);        break;
            case 'U':  rom(sjekkUt);       break;
            default:   skrivMeny();        break;
        }
        menyvalg = lesChar("\nMenyvalg");
    }

   skrivTilFil();

   return 0;
}

/**
 * Skriver ut alle valgene brukeren kan gjøre, og hva de gjør.
*/
void skrivMeny() {
    cout << "(S) Skriv alle rommene" << '\n';
    cout << "(B) Book rom" << '\n';
    cout << "(F) Se data" << '\n';
    cout << "(U) Sjekk ut" << '\n';
    cout << "(Q) Avslutt" << '\n';
}

void lesFraFIl() {
    char objektType;
    ifstream innfil("HOTELL.DTA");     // Fil å lese INN fra.

    if (innfil) {
        cout << "\nLeser dataene fra 'HOTELL.DTA'\n";
        innfil >> objektType;           //  Leser (om mulig) 1.felt ('E'/'D').
        while (!innfil.eof()) {         //  Ennå ikke filslutt:
            innfil.ignore();            //  Forkaster ' ' etter 'E'/'D'.
            switch (objektType) {
              case 'E': break;
              case 'D': break;
              default:  cout << "\n\tUlovlig type objekt på filen: '"
                             << objektType << "'\n\n";                  break;
            }
            innfil >> objektType;       //  Leser (om mulig) 1.felt ('E'/'D').
        }
    }
    // Feilmelding om man ikke finner filen
    else    cout << "Fant ikke filen 'HOTELL.DTA'\n";

}