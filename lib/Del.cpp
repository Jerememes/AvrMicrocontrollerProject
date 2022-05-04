/*
 * Projet Final - Del.cpp
 * Date de remise : 20 avril 2022
 * Section 03
 * Équipe 68 et 75
 * 
 * AUTEURS :
 *  Walid Fortas - 2047983
 *  Zarine Ardekani-Djoneidi - 2139186
 *  Mingame Maelle Oceane Ouattara - 1998415
 *  Jeremy Rouillard - 2007279
 *  
 * DESCRIPTION DU PROGRAMME :
 *  Ce programme contient la définition des méthodes de la classe Del, 
 *  on voit les différentes méthodes utilisée dans le fichier Del.h.
 *  Cette classe permet de controler une DEL.
 * 
 * IDENTIFICATIONS MATÉRIELLES :
 *  Les broches utilisées en sortie sont choisies par le programme qui utilise
 *  la librarie, si le programme ne précise pas les broches, la classe va
 *  utiliser le constructeur par défaut qui utilise A0 et A1 comme sorties. 
*/


#include "Del.h"


Del::Del(volatile uint8_t* adresseBrochesSortie, 
                  uint8_t  numeroBroche) {

    adresseBrochesSortie_ = adresseBrochesSortie;

    numeroBroche_ = numeroBroche;

    if      (*adresseBrochesSortie_ == PORTA) {

        registreDirectionDonnees_ = &DDRA;

    } 
    else if (*adresseBrochesSortie_ == PORTB) {

        registreDirectionDonnees_ = &DDRB;

    } 
    else if (*adresseBrochesSortie_ == PORTC) {

        registreDirectionDonnees_ = &DDRC;

    } 
    else if (*adresseBrochesSortie_ == PORTD) {
        
        registreDirectionDonnees_ = &DDRD;
    }

    *registreDirectionDonnees_ |= (1 << numeroBroche_);
}


Del::~Del() {

    eteindre();
    *registreDirectionDonnees_ &= ~(1 << numeroBroche_);

}


void Del::allumer() {

    *adresseBrochesSortie_ |= (1 << numeroBroche_);

}


void Del::eteindre() {

    *adresseBrochesSortie_ &= ~(1 << numeroBroche_);

}

