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
    cout << "(S) Skriv alle rommene" << endl;
    cout << "(B) Book rom" << endl;
    cout << "(F) Se data" << endl;
    cout << "(U) Sjekk ut" << endl;
    cout << "(Q) Avslutt" << endl;
}

void lesFraFil() {
    ifstream innfil("HOTELL.DTA");
    if (!innfil)  {
        cout << "Kan ikke åpne filen 'HOTELL.DTA' for lesing!" << endl;
    }
    else {
        int antallRommene;
        innfil >> antallRommene;
        for (int i = 0; i < antallRommene; i++)  {
            int romNr;
            innfil >> romNr;
            char romType;
            innfil >> romType;
            if (romType == 'E')  {
                gHotellRommene[romNr] = new Enkeltrom(innfil);
            }
            else if (romType == 'D')  {
                gHotellRommene[romNr] = new Dobbeltrom(innfil);
            }
        }
        innfil.close();
    }
}