/*
 * Projet Final - Bouton.cpp
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
 *  Ce programme contient la définition des méthodes de la classe Bouton, 
 *  on voit les différentes méthodes utilisée dans le fichier Bouton.h.
 *  Cette classe permet de créer un objet bouton qui permet de controller 
 *  un bouton par scrutation, et qui a 4 états possibles.
 * 
 * IDENTIFICATIONS MATÉRIELLES :
 *  La broche utilisée en entrée est choisie par le programme qui utilise
 *  la librairie. 
 * 
 * Machine à état:
 +--------------+--------+---------------+
 | État courant | Entrée | Prochain état |
 +--------------+--------+---------------+
 | AUCUN        |      0 | AUCUN         |
 | AUCUN        |      1 | APPUYE        |
 | APPUYE       |      0 | RELACHE       |
 | APPUYE       |      1 | MAINTENU      |
 | MAINTENU     |      0 | RELACHE       |
 | MAINTENU     |      1 | MAINTENU      |
 | RELACHE      |      0 | AUCUN         |
 | RELACHE      |      1 | APPUYE        |
 +--------------+--------+---------------+
 * 
 * 
*/


#include "Bouton.h"


Bouton::Bouton(volatile uint8_t* adresseBrochesEntree, 
                        uint8_t  numeroBroche) {

    adresseBrochesEntree_ = adresseBrochesEntree;
    numeroBroche_ = numeroBroche;
    etat_ = Etat::AUCUN;

    if (*adresseBrochesEntree == PINA) {

        registreDirectionDonnees_ = &DDRA;
    
    } 
    else if (*adresseBrochesEntree == PINB) {
    
        registreDirectionDonnees_ = &DDRB;
    
    } 
    else if (*adresseBrochesEntree == PINC) {
    
        registreDirectionDonnees_ = &DDRC;
    
    } 
    else if (*adresseBrochesEntree == PIND) {
    
        registreDirectionDonnees_ = &DDRD;
    
    }

    *registreDirectionDonnees_ &= ~(1 << numeroBroche_);
}


Bouton::~Bouton() {

    *registreDirectionDonnees_ &= ~(1 << numeroBroche_);

}


Bouton::Etat Bouton::obtenirEtat() {

    mettreAJourEtat();
    return etat_;
    
}


void Bouton::mettreAJourEtat() {

    switch (etat_) {

        case Etat::AUCUN :
            if (estAppuye()) {

                etat_ = Etat::APPUYE;

            }
            break;

        case Etat::APPUYE :
            if (estAppuye()) {

                etat_ = Etat::MAINTENU;

            } else {

                etat_ = Etat::RELACHE;

            }
            break;

        case Etat::MAINTENU :
            if (!estAppuye()) {

                etat_ = Etat::RELACHE;

            }
            break;

        case Etat::RELACHE :
            if (estAppuye()) {

                etat_ = Etat::APPUYE;

            } else {

                etat_ = Etat::AUCUN;

            }
            break;
    }
}


bool Bouton::estAppuye() {

    bool boutonAppuye = *adresseBrochesEntree_ & (1 << numeroBroche_);

    if (boutonAppuye) {

        _delay_ms(DELAI_DEBOUNCE);
        boutonAppuye = *adresseBrochesEntree_ & (1 << numeroBroche_);

    }

    return boutonAppuye;
}

