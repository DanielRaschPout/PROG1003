#include <iostream>
#include <iomanip>
using namespace std;

const int MAXLOPERE = 10;

int main() {
    int distanse,
        ant500,
        min, sek, hundr,
        antallLopere;
    float poeng;
    char brukerSvar;

    do {
        do {
            cout << "Skriv en skøytedistanse (500, 1500, 3000, 5000): ";
            cin >> distanse;
        } while (distanse != 500   &&  distanse != 1500 && 
                distanse != 3000  &&  distanse != 5000);
        
        ant500 = distanse / 500;

        do {
            cout << "Antall løpere å lese tider for (1-" << MAXLOPERE << ") ";
            cin >> antallLopere;
        } while (antallLopere < 1 || antallLopere > MAXLOPERE);
    

        for (int i = 1; i <= antallLopere; ++i) {
            do {
                cout << "Tid (mm ss hh): ";
                cin >> min >> sek >> hundr;
            } while (min < 0  ||  sek < 0  || hundr < 0);

            poeng =  ((min*60) + sek + (hundr/100.0)) / ant500;
            cout << "Poengsum: " << setw(3) << poeng << "\n";
        }

        cout <<"\nLese tider om en ny distanse (J/N): ";
        cin >> brukerSvar;
        brukerSvar = toupper(brukerSvar);
    } while (brukerSvar == 'J');

    return 0;
}