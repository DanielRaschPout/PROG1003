/**
 * 
 *  Programmet:
 * -  Leser inn filmer/bøker fra bruker og legger dem i et vektor.
 * -  Lar bruker låne ut filmer/bøker.
 * -  Lar bruker levere inn filmer/bøker.
 * -  Lar bruker endre antall eksemplarer av filmer/bøker.
 * -  Skriver ut alle filmer/bøker i vektoren.
 * -  Skriver ut alle utleide filmer/bøker i vektoren.
 * 
 * @file Oblig2.cpp
 * @author Daniel Fernando Petter Rasch-Pout (dfraschp@gmail.com)
 * @version 0.4
 * @date 02-03-2023
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

/**
 * Hovedprogrammet.
 */
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
    cout << "\nNavn: " << laanersNavn << '\n';
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
    cout << "Antall eksemplarer: " << antallEksemplarer << '\n';
    cout << "Vil du endre antall eksemplarer? (J/N)" << '\n';
    char svar = lesChar("Svar");

    if (svar == 'J') {
    antallEksemplarer = lesInt("Antall eksemplarer",1,MAKSANTALL);
    while (antallEksemplarer < utleideEksemplarer.size()) {
        cout << "Det er utlånt flere eksemplarer enn det er i beholdning." << '\n';
        cout << "Du må først innlevere eksemplarer." << '\n';
        antallEksemplarer = lesInt("Antall eksemplarer",1,MAKSANTALL);
    }
    }
    else {
        cout << "Antall eksemplarer er ikke endret." << '\n';
    }
}

/**
 * Låner ut en gjenstand (hvis den er tilgjengelig)
 * 
 * @see UtlaansGjenstand::erTilgjengelig()
 * @see UtlaansGjenstand::sjekkDato()
 * @see LaaneInfo::LaaneInfo()
 * @see LaaneInfo::settData()
 */
void UtlaansGjenstand::laanUt(){
    if (erTilgjengelig()) {
      string navn;
      int laanedato,
          returfrist,
          dag, mnd, aar;
      bool dato1 = false,
           dato2 = false;

      cout << "Lånerens navn: ";
      getline(cin, navn);

      // Sjekker om Lånedato er gyldig.
      while (!dato1) {
        cout << "Lånedato (AAAAMMDD): ";
        cin >> laanedato;
        cin.ignore();
        dag = laanedato % 100;
        mnd = (laanedato / 100) % 100;
        aar = laanedato / 10000;
        dato1 = sjekkDato(dag, mnd, aar);
        if (!dato1) 
          cout << "Ugyldig dato." << '\n';
      }

      // Sjekker om returfristen er gyldig.
      while (!dato2) {
        cout << "Returfrist (AAAAMMDD): ";
        cin >> returfrist;
        cin.ignore();
        dag = returfrist % 100;
        mnd = (returfrist / 100) % 100;
        aar = returfrist / 10000;
        dato2 = sjekkDato(dag, mnd, aar);
        if (!dato2) 
          cout << "Ugyldig dato." << '\n';
      }
        // Sjekker om returfristen er før lånedatoen.
        if (laanedato > returfrist) 
            cout << "Ugyldig dato." << '\n';
        // Hvis returfristen er etter lånedatoen.
        else {
            LaaneInfo* nyLaan = new LaaneInfo(navn);
            nyLaan->settData(laanedato, returfrist);
            utleideEksemplarer.push_back(nyLaan);
        }
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
    cout << "(1) Barn, (2) Drama, (3) Fantasy, (4) Spenning";
    int sjangerInt =lesInt("", 1, 4);
    sjanger = Sjanger(sjangerInt-1);
    antallEksemplarer = lesInt("Antall eksemplarer", 1, MAKSANTALL);
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

/**
 * Skriver ut tittel, sjanger og antall eksemplarer.
 * 
 * @see UtlaansGjenstand::skrivTittelOgAntall()
 */
void UtlaansGjenstand::skrivData() const {

  skrivTittelOgAntall();
  cout << "Sjanger: ";
  switch (sjanger) {
    case Barn:     cout << "Barn";     break;
    case Drama:    cout << "Drama";    break;
    case Fantasy:  cout << "Fantasy";  break;
    case Spenning: cout << "Spenning"; break;
  }
  cout << "\nAntall eksemplarer: " << antallEksemplarer << '\n';
}


void UtlaansGjenstand::skrivTittelOgAntall() const {

  cout << "Tittel: " << tittel << '\n';
  cout << "Antall eksemplarer: " << antallEksemplarer << '\n';
}


//*************************  FILM:  *********************************
/**
 * Leser og setter timer, minutter og aldersgrense.
 * Tilkaller på lesData() fra superklassen for å lese inn 
 * tittel, sjanger og antall eksemplarer.
 * 
 * @see UtlaansGjenstand::lesData()
 */
void Film::lesData() {
  UtlaansGjenstand::lesData();
  timer = lesInt("Timer: ", 0, 3);
  minutter = lesInt("Minutter: ", 0, 59);
  aldersGrense = lesInt("Aldersgrense: ", 0, 18);
}

/**
 * Sjekker om låner er gammel nok til å se filmen.
 * I så fall, kaller på laanUt().
 * 
 * @see UtlaansGjenstand::laanUt()
 */
void Film::sjekkAlderOgEvtLaanUt()  {

  int alder;
  alder = lesInt("Alder: ", 0, 100);
  if (alder < aldersGrense) {
    cout << "Du er for ung til å se denne filmen." << '\n';
  }
  else {
    UtlaansGjenstand::laanUt();
  }
}

/**
 * Skriver ut tittel, sjanger, antall eksemplarer, lengde og aldersgrense.
 * 
 * @see UtlaansGjenstand::skrivData()
 */
void Film::skrivData() const {

  UtlaansGjenstand::skrivData();
  cout << "Lengde: " << timer << " timer og " << minutter 
       << " minutter" << '\n';
  cout << "Aldersgrense: " << aldersGrense << '\n';
}

/**
 * Om det er utleide eksemplarer, skrives det ut 
 * alle filmens data og info om alle lånerne.
 * Hvis ingen er utleid, skrives det ut at ingen er utleid.
 * 
 * @see Film::skrivData()
 * @see LaaneInfo::skrivData()
 */
void Film::skrivUtleid() const {

  if (utleideEksemplarer.size() > 0) {
    skrivData();
    for (int i = 0; i < utleideEksemplarer.size(); i++) {
      utleideEksemplarer[i]->skrivData();
    }
  }
  else {
    cout << "Ingen eksemplarer er utleid." << '\n';
  }
}


//*************************  BOK:  *********************************
/**
 * Leser inn all data (ikke tittel) som trengs for å opprette en ny bok.
 * 
 * @see UtlaansGjenstand::lesData()
 */
void Bok::lesData() {

  int bokFor;
  UtlaansGjenstand::lesData();
  cout << "(1) Pocket, (2) Innbundet, (3) Lydbok:";
  bokFor = lesInt("", 1, 3);
  bokFormat = Format(bokFor-1);

  antallSider = lesInt("Antall sider", 1, 1000);
}

/**
 * Skriver ut tittel, sjanger, antall eksemplarer, bokformat og antall sider.
 * 
 * @see UtlaansGjenstand::skrivData()
 */
void Bok::skrivData() const {

  UtlaansGjenstand::skrivData();
  cout << "Bokformat: ";
  switch (bokFormat) {
    case Pocket:    cout << "Pocket";     break;
    case Innbundet: cout << "Innbundet";  break;
    case Lydbok:    cout << "Lydbok";     break;
  }
  cout << " \nAntall sider: " << antallSider << '\n';
}

/**
 * Om det er utleide eksemplarer, skrives det ut
 * alle bokens data og info om alle lånerne.
 * Hvis ingen er utleid, skrives det ut at ingen er utleid.
 * 
 * @see Bok::skrivData()
 * @see LaaneInfo::skrivData()
 */
void Bok::skrivUtleid() const {

  if (utleideEksemplarer.size() > 0) {
    skrivData();
    for (int i = 0; i < utleideEksemplarer.size(); i++) {
      utleideEksemplarer[i]->skrivData();
      
    }
  }
  else {
    cout << "Ingen eksemplarer er utleid." << '\n';
  }
}


//*********************  FUNKSJONER:  *******************************
/**
 * Leser inn tittel for en gjenstand.
 * Hvis gjenstanden finnes, kaller på UtlaansGjenstand::endreAntEks(),
 * som endrer antall eksemplarer.
 * Hvis ikke, skrives det ut at gjenstanden ikke finnes.
 * 
 * @see UtlaansGjenstand::endreAntallEks()
 */
void endreAntEksemplarer() {

  string title;
  cout << "Tittel: ";
  getline(cin, title);
   if (finnEnGjenstand(title) != nullptr) {
    finnEnGjenstand(title)->endreAntallEks();
  }
  else {
    cout << "Fant ingen gjenstand med denne tittelen." << '\n';
  }
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

/**
 * Frigir ALL allokert memory under run-time.
 * 
 */
void fjernAllokertData() {

  // Går gjennom alle filmene og sletter dem
  for (int i = 0; i < gFilmene.size(); i++) {
    delete gFilmene[i];
  }
  // Går gjennom alle bøkene og sletter dem
  for (int i = 0; i < gBokene.size(); i++) {
    delete gBokene[i];
  }
  gBokene.clear();
  gFilmene.clear();
}

/**
 * Leser inn tittel.
 * Hvis gjenstanden finnes, kaller på UtlaansGjenstand::laanUt(),
 * som låner ut gjenstanden.
 * Hvis ikke, skrives det ut at gjenstanden ikke finnes.
 * 
 * @see UtlaansGjenstand::laanUt()
 * @see Film::sjekkAlderOgEvtLaanUt()
 */
void laanUtGjenstand(){

  string title;
  cout << "Tittel: ";
  getline(cin, title);
  if (finnEnGjenstand(title) != nullptr) {
    UtlaansGjenstand* gjenstand = finnEnGjenstand(title);
    // Hvis gjenstand er bok
    for (int i = 0; i < gBokene.size(); i++) {
      if (gBokene[i] == gjenstand) {
        gBokene[i]->laanUt();
      }
    }
    // Hvis gjenstand er film
    for (int i = 0; i < gFilmene.size(); i++) {
      if (gFilmene[i] == gjenstand) {
        gFilmene[i]->sjekkAlderOgEvtLaanUt();
      }
    }
  }
  else {
    cout << "Fant ingen gjenstand med denne tittelen." << '\n';
  }
}

/**
 * Leser inn tittel.
 * Hvis ikke finnes fra før, spør om det er en bok eller film.
 * Aktuell gjenstand opprettes og leses inn.
 * Hvis gjenstanden finnes fra før, skrives det ut at den finnes.
 * 
 * @see Bok::lesData()
 * @see Film::lesData()
 */
void nyGjenstand() {
  string title;
  cout << "Tittel: ";
  getline(cin, title);
  if(finnEnGjenstand(title) != nullptr) {
    cout << "Gjenstanden finnes allerede i biblioteket." << '\n';
  }
  else {
    int valg;
    cout << "(1) Bok, (2) Film, (3) Avbryt";
    valg = lesInt("", 1, 3);

    switch (valg) {
      case 1: {
        Bok* nyBok = new Bok(title);
        nyBok->lesData();
        gBokene.push_back(nyBok);
        break;
      }
      case 2: {
        Film* nyFilm = new Film(title);
        nyFilm->lesData();
        gFilmene.push_back(nyFilm);
        break;
      }
      case 3: {
        cout << "Avbryter." << '\n';
        break;
      }
    }
  }
}

/**
 * Leser inn tittel.
 * Hvis gjenstanden finnes, kaller på UtlaansGjenstand::leverInn(),
 * som leverer inn gjenstanden.
 * 
 * @see UtlaansGjenstand::leverInn()
 */
void innleverGjenstand(){

  string title;
  cout << "Tittel: ";
  getline(cin, title);
  if (finnEnGjenstand(title) != nullptr) {
    UtlaansGjenstand* gjenstand = finnEnGjenstand(title);
    gjenstand->leverInn();
  }
  else {
    cout << "Fant ingen gjenstand med denne tittelen." << '\n';
  }
}

/**
 * Skriver ut alle bøker og filmer (hvis det er noen).
 * 
 * @see Bok::skrivData()
 * @see Film::skrivData()
 */
void skrivAlle() {

  // Hvis det er noen bøker registrert, skriv ut alle bøkene
  if (gBokene.size() > 0) {
    cout << "\nBøker:\n";
    for (int i = 0; i < gBokene.size(); i++) {
      gBokene[i]->skrivData();
    }
  }
  else {
    cout << "Ingen bøker registrert." << '\n';
  }
  // Hvis det er noen filmer registrert, skriv ut alle filmer
  if (gFilmene.size() > 0) {
    cout << "\nFilmer:\n";
    for (int i = 0; i < gFilmene.size(); i++) {
      gFilmene[i]->skrivData();
    }
  }
  else {
    cout << "Ingen filmer registrert." << '\n';
  }
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

/**
 * Skriver ut alle utleide bøker/filmer (hvis det er noen).
 * 
 * @see Bok::skrivUtleid()
 * @see Film::skrivUtleid()
 */
void skrivUtleide(){

  // Hvis det er noen bøker registrert, skriv ut alle utleide bøker
  if (gBokene.size() > 0) {
    cout << "\nUtleide bøker:\n";
    for (int i = 0; i < gBokene.size(); i++) {
      gBokene[i]->skrivUtleid();
      
    }
  }
  else {
    cout << "Ingen bøker registrert." << '\n';
  }
  // Hvis det er noen filmer registrert, skriv ut alle utleide filmer
  if (gFilmene.size() > 0) {
    cout << "\nUtleide filmer:\n";
    for (int i = 0; i < gFilmene.size(); i++) {
      gFilmene[i]->skrivUtleid();
    }
  }
  else {
    cout << "Ingen filmer registrert." << '\n';
  }
}
