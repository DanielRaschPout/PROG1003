#include <iostream>                //  cout
#include <fstream>                 //  ifstream, ofstream
#include <iomanip>                 //  setprecision
#include <string>                  //  string
#include <vector>                  //  vector
using namespace std;

class Publikasjon {
    private:
        string tittel;
        float pris;

    public:
        Publikasjon(ifstream & inn) {
            inn >> pris; inn.ignore();
            getline(inn, tittel);
        }

        virtual void skrivTilFil(ofstream & ut) {
            ut << fixed << setprecision(2);
            ut << pris << ' ' << tittel << '\n';
        }

};

class Bok : public Publikasjon {
    private:
        string forfatter;
        int antallSider;
    
    public:
        Bok(ifstream & inn) : Publikasjon(inn) {
            inn >> antallSider; inn.ignore();
            getline(inn, forfatter);
        }

        virtual void skrivTilFil(ofstream & ut) {
            ut << 'B' << ' ';
            Publikasjon::skrivTilFil(ut);
            ut << antallSider << ' ' << forfatter << '\n';

        }
};

class Magasin : public Publikasjon {
    private:
        int aar,
            volum;
    
    public:
    Magasin(ifstream & inn) : Publikasjon(inn) {
        inn >> aar; inn.ignore(); inn >> volum; inn.ignore();
    }

    virtual void skrivTilFil(ofstream & ut) {
            ut << 'M' << ' ';
            Publikasjon::skrivTilFil(ut);
            ut << aar << ' ' << volum << '\n';

        }
};

vector <Publikasjon*>  gPublikasjoner; ///<  Datastrukturen med publikasjoner.


int main ()  {
    ifstream  innfil("oppg_16.dta");    //  Fil å lese INN fra.
    ofstream  utfil("oppg_16.dt2");     //  fil å skrive UT til.
    char objektType;                    //  'B' eller 'M' fra fil.

    if (innfil) {                       //  Filen finnes/mulig � �pne:
        cout << "\nLeser dataene fra 'OPPG_16.DTA'\n";
        innfil >> objektType;           //  Leser (om mulig) 1.felt ('B'/'M').
        while (!innfil.eof()) {         //  Enn� ikke filslutt:
            innfil.ignore();            //  Forkaster ' ' etter 'B'/'M'.
            switch (objektType) {
              case 'B': gPublikasjoner.push_back(new Bok(innfil));      break;
              case 'M': gPublikasjoner.push_back(new Magasin(innfil));  break;
              default:  cout << "\n\tUlovlig type objekt p� filen: '"
                             << objektType << "'\n\n";                  break;
            }
            innfil >> objektType;       //  Leser (om mulig) 1.felt ('B'/'M').
        }
        
        innfil.close();                 //  Lukker innlesningsfilen.

                                        //  Skriver ALT til fil:
        cout << "\nSkriver dataene til 'OPPG_16.DT2'\n\n\n";
        for (int i = 0; i < gPublikasjoner.size(); i++)
            gPublikasjoner[i]->skrivTilFil(utfil);


    } else
      cout << "\n\tFant ikke filen 'OPPG_16.DTA'!\n\n";

    utfil.close();                      //  Utskriftsfilen lukkes uansett.

    return 0;
}
