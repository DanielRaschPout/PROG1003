/**
 * 
 * Filen inneholder funksjoner som er nødvendige for å kjøre programmet.
 * 
 * Inneholder funksjonenes definisjoner.
 * 
 * @file funksjoner.cpp
 * @author Daniel Fernando Petter Rasch-Pout (dfraschp@gmail.com)
 */
#include <iostream>            //  cin, cout
#include "funksjoner.h"

/**
 * Skriver ut de ulike menyvalgene brukeren har
 * 
 */
void skrivMeny() {
    std::cout << "(U)" << '\n'
              << "(A)" << '\n'
              << "(K)" << '\n'
              << "(T)" << '\n'
              << "(Q) Avslutt" << '\n';
}
