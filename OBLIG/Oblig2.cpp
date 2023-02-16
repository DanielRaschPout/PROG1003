/**
 * 
 *  Programmet:
 *  
 * 
 * @file Oblig2.cpp
 * @author Daniel Fernando Petter Rasch-Pout (dfraschp@gmail.com)
 * @brief 
 * @version 0.1
 * @date 16-02-2023
 * 
 */
#include <iostream>                //  cout, cin
#include <string>                  //  string-klassen
#include <vector>                  //  vector-klassen
#include "LesData2.h"              //  Verktøykasse for lesing av diverse data
using namespace std;


const int MAKSANTALL = 5;       ///<  Maks antall/beholdning av hver bok/film.


/**
 *  2x enum'er med utlånsgjenstand-sjangre  og  bok-formater.
 */
enum Sjanger {  Barn, Drama, Fantasy, Spenning  };

enum Format  {  Pocket, Innbundet, Lydbok  };


/**
 * Låneinfo med navn på person som låner bok/film, lånedato og returfrist.
 */
class LaaneInfo {
  private:
    string laanersNavn;
    int    laaneDato;   //  På formen:  AAAAMMDD
    int    returFrist;  //  På formen:  AAAAMMDD

  public:
    LaaneInfo(string nvn)      {  laanersNavn = nvn;  }
    string hentNavn()   const  {  return laanersNavn; }
    void   settData(const int lD, const int rF)
                               {  laaneDato = lD;  returFrist = rF;  }
    void   skrivData()  const;
};


/**
 * Baseklassen 'Gjenstand', blant annet inneholdende vector m/utlånene.
 */
class UtlaansGjenstand {
  protected:
    string  tittel;
    int     antallEksemplarer;
    vector <LaaneInfo*> utleideEksemplarer;
    Sjanger sjanger;

  public:
    UtlaansGjenstand()  {  }
    UtlaansGjenstand(const string & t) { tittel = t; }
    ~UtlaansGjenstand();
    void   endreAntallEks();
    bool   erTilgjengelig() const {
               return ((antallEksemplarer - utleideEksemplarer.size()) > 0); }
    string hentTittel() const { return tittel; }
    void   laanUt();
    void   lesData();
    void   leverInn();
    bool   sjekkDato(const int dag, const int mnd, const int aar);
    void   skrivData() const;
    void   skrivTittelOgAntall() const;
};


/**
 *  Subklassen 'Film' med spilletid og aldersgrense.
 */
class Film : public UtlaansGjenstand {
  private:
    int timer;
    int minutter;
    int aldersGrense;

  public:
    Film() {  }
    Film(const string & tittel) : UtlaansGjenstand(tittel) {  }
    void lesData();
    void sjekkAlderOgEvtLaanUt();
    void skrivData()   const;
    void skrivUtleid() const ;
};


/**
 *  Subklassen 'Bok' med antall sider og formatet på bok.
 */
class Bok : public UtlaansGjenstand {
  private:
    int    antallSider;
    Format bokFormat;

  public:
    Bok()  {  }
    Bok(const string & navn) : UtlaansGjenstand(navn) {  }
    void lesData();
    void skrivData()   const;
    void skrivUtleid() const;
};


void endreAntEksemplarer();
UtlaansGjenstand* finnEnGjenstand(const string tittel);
void fjernAllokertData();
void laanUtGjenstand();
void nyGjenstand();
void innleverGjenstand();
void skrivAlle();
void skrivMeny();
void skrivUtleide();


vector <Film*> gFilmene;    ///<  Vector med ALLE filmene i kartoteket.
vector <Bok*> gBokene;      ///<  Vector med ALLE bøkene  i kartoteket.


int main()  {

  char valg;

  skrivMeny();
  valg = lesChar("\n\nKommando");
  while (valg != 'Q') {
    switch (valg) {
      case 'N': nyGjenstand();          break;
      case 'U': laanUtGjenstand();      break;
      case 'I': innleverGjenstand();    break;
      case 'E': endreAntEksemplarer();  break;
      case 'A': skrivAlle();            break;
      case 'S': skrivUtleide();         break;
      default:  skrivMeny();            break;
    }
    valg = lesChar("\n\nKommando");
  }

  fjernAllokertData();
  return 0;
}


//*************************  LAANEINFO:  **********************

/**
 *  Skriver ut låneinfo.
 * 
 */
void LaaneInfo::skrivData()  const  {
    cout << "Navn: " << laanersNavn << '\n';
    cout << "Lånedato: " << laaneDato << '\n';
    cout << "Returfrist: " << returFrist << '\n';

}


//*************************  UTLAANSGJENSTAND:  **********************
/**
 * Sletter/Fjerner alt som utleideEksemplarer peker på.
 * Sletter/Fjerner alle pekere i utleideEksemplarer.
 * 
 */
UtlaansGjenstand::~UtlaansGjenstand() {
    for (int i = 0; i < utleideEksemplarer.size(); i++) {
        delete utleideEksemplarer[i];
    }
    utleideEksemplarer.clear();

}

/**
 * Tilbyr bruker å endre antall eksemplarer av en gjenstand.
 * 
 */
void UtlaansGjenstand::endreAntallEks() {
    cout << "Tittel: " << tittel << '\n';
    cout << "Antall eksemplarer: " << antallEksemplarer << '\n';
    cout << "Vil du endre antall eksemplarer? (J/N)" << '\n';
    char svar = lesChar("Svar: ");
    toupper(svar);
    if (svar == 'J') {
    antallEksemplarer = lesInt("Antall eksemplarer: ",1,MAKSANTALL);
    }
    else {
        cout << "Antall eksemplarer er ikke endret." << '\n';
    }

}


void UtlaansGjenstand::laanUt(){
    if (erTilgjengelig()) {
        // HUSK FINISH ********************************************************
    
    }

    // Melding hvis det ikke er noen eksemplarer tilgjengelig.
    else {
        cout << "Ingen eksemplarer tilgjengelig." << '\n';
    }

}

/**
 * Leser og setter antall eksemplarer avgjenstanden til utlån,
 * samt hvilken lovlig sjanger den er av.
 * 
 */
void UtlaansGjenstand::lesData(){
    cout << "(1) Barn, (2) Drama, (3) Fantasy, (4) Spenning: ";
    int sjangerInt =lesInt("Sjanger: ", 1, 4);
    sjanger = Sjanger(sjangerInt-1);
    antallEksemplarer = lesInt("Antall eksemplarer: ", 1, MAKSANTALL);
}

/**
 * Leser inn låners navn. Om ingen låner er funnet, skrives det ut en 
 * feilmelding. Om låner er funnet, slettes låneren fra utleideEksemplarer.
 * 
 * @see LaaneInfo::hentNavn()
 */
void UtlaansGjenstand::leverInn() {
    if (utleideEksemplarer.size() > 0) {
        bool funnet = false;
        string navn;
        cout << "Låner: ";
        getline(cin, navn);

        // Sjekker om navnet er i utleideEksemplarer.
        for (int i = 0; i < utleideEksemplarer.size(); i++) {
            if (utleideEksemplarer[i]->hentNavn() == navn) {
                funnet = true;
                delete utleideEksemplarer[i];
                utleideEksemplarer.erase(utleideEksemplarer.begin() + i);
                cout << "Innlevering vellykket." << '\n';
            }
        }

        if (!funnet) {
            cout << "Fant ingen låner med dette navnet." << '\n';
        }
    
    }
    else {
        cout << "Ingen eksemplarer er utleid." << '\n';
    }

}

/**
 * Sjekker om innlest dato er gyldig. 
 * 
 * @param dag 
 * @param mnd 
 * @param aar 
 * @return ans  Returnerer true hvis datoen er gyldig, false hvis ikke.
 */
bool UtlaansGjenstand::sjekkDato(int dag, int mnd, int aar){

bool ans = true;

if (dag < 1 || dag > 31) {
    ans = false;
}
if (mnd < 1 || mnd > 12) {
    ans = false;
  }
if (aar < 2022 || aar > 2030) {
    ans = false;
  }

  return ans;
}


void UtlaansGjenstand::skrivData() const {

//  LAG INNMATEN

}


void UtlaansGjenstand::skrivTittelOgAntall() const {

//  LAG INNMATEN

}


//*************************  FILM:  *********************************

void Film::lesData() {
  timer = lesInt("Timer: ", 0, 3);
  minutter = lesInt("Minutter: ", 0, 59);
  aldersGrense = lesInt("Aldersgrense: ", 0, 18);

//  LAG INNMATEN

}


void Film::sjekkAlderOgEvtLaanUt()  {

//  LAG INNMATEN

}


void Film::skrivData() const {

//  LAG INNMATEN

}


void Film::skrivUtleid() const {

//  LAG INNMATEN

}


//*************************  BOK:  *********************************

void Bok::lesData() {

  int bokFor;
  cout << "(1) Heftet, (2) Innbundet, (3) Pocket: ";
  bokFor = lesInt("Bokformat: ", 1, 3);
  bokFormat = Format(bokFor-1);
  

  antallSider = lesInt("Antall sider: ", 1, 1000);


}


void Bok::skrivData() const {

//  LAG INNMATEN

}


void Bok::skrivUtleid() const {

//  LAG INNMATEN

}


//*********************  FUNKSJONER:  *******************************

void endreAntEksemplarer() {

//  LAG INNMATEN
}


/**
 *  Returnerer (om mulig) gjenstand med hel/delvis match ift tittel.
 *
 *  @param    tittel -  Tittel på bok/film det søkes etter
 *  @return   Peker til aktuell gjenstand, evt nullptr
 *  @see      UtlaansGjenstand::hentTittel()
 */
UtlaansGjenstand* finnEnGjenstand(string tittel){
  int funn = 0;
  UtlaansGjenstand* gjenstand = nullptr;

  for (const auto & val: gFilmene)
      if (!val->hentTittel().compare(0, tittel.size(), tittel))  {
         gjenstand = dynamic_cast <UtlaansGjenstand*> (val);
         funn++;
      }

  for (const auto & val: gBokene)
      if (!val->hentTittel().compare(0, tittel.size(), tittel))  {
         gjenstand = dynamic_cast <UtlaansGjenstand*> (val);
         funn++;
      }

   return ((funn == 1) ? gjenstand : nullptr);
}


void fjernAllokertData() {

//  LAG INNMATEN

}


void laanUtGjenstand(){

//  LAG INNMATEN
}


void nyGjenstand() {
  string title;
  cout << "Tittel: ";
  getline(cin, title);
  if(finnEnGjenstand(title) != nullptr) {
    cout << "Gjenstanden finnes allerede i biblioteket." << '\n';
  }
  else {
    int valg;
    cout << "(1) Bok, (2) Film: ";
    valg = lesInt("Valg: ", 1, 2);
    if (valg == 1) {
      Bok* nyBok = new Bok;
      nyBok->lesData();
      gBokene.push_back(nyBok);
    }
    else {
      Film* nyFilm = new Film;
      nyFilm->lesData();
      gFilmene.push_back(nyFilm);
    }
  }

}


void innleverGjenstand(){

//  LAG INNMATEN

}


void skrivAlle() {

//  LAG INNMATEN

}


/**
 *  Skriver programmets menyvalg/muligheter på skjermen.
 */
void skrivMeny()  {
  cout << "\nFlgende kommandoer er tilgjengelige:\n"
       << "\n   N  - Legg til ny Bok/Film"
       << "\n   U  - Laan ut"
       << "\n   I  - Lever inn"
       << "\n   E  - Endre antall Bok/Film"
       << "\n   A  - Skriv ut alle gjenstander i bibliotek"
       << "\n   S  - Skriv ut alle utleide gjenstander"
       << "\n   Q  - Quit / avslutt";
}


void skrivUtleide(){

//  LAG INNMATEN

}
