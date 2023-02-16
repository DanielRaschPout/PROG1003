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


void LaaneInfo::skrivData()  const  {

//  LAG INNMATEN

}


//*************************  UTLAANSGJENSTAND:  **********************

UtlaansGjenstand::~UtlaansGjenstand() {

//  LAG INNMATEN

}


void UtlaansGjenstand::endreAntallEks() {

//  LAG INNMATEN

}


void UtlaansGjenstand::laanUt(){

//  LAG INNMATEN

}


void UtlaansGjenstand::lesData(){

//  LAG INNMATEN

}


void UtlaansGjenstand::leverInn() {

//  LAG INNMATEN

}


bool UtlaansGjenstand::sjekkDato(int dag, int mnd, int aar){

//  LAG INNMATEN

}


void UtlaansGjenstand::skrivData() const {

//  LAG INNMATEN

}


void UtlaansGjenstand::skrivTittelOgAntall() const {

//  LAG INNMATEN

}


//*************************  FILM:  *********************************

void Film::lesData() {

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

//  LAG INNMATEN

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

//  LAG INNMATEN
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
