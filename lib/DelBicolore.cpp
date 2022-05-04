/*
 * Projet Final - DelBicolore.cpp
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
 *  Ce programme contient la définition des méthodes de la classe DelBicolore, 
 *  on voit les différentes méthodes utilisée dans le fichier DelBicolore.h.
 *  Cette classe permet de controler une DEL bicolore.
 * 
 * IDENTIFICATIONS MATÉRIELLES :
 *  Les broches utilisées en sortie sont choisies par le programme qui utilise
 *  la librarie, si le programme ne précise pas les broches, la classe va
 *  utiliser le constructeur par défaut qui utilise A0 et A1 comme sorties. 
 * 
*/


#include "DelBicolore.h"


DelBicolore::DelBicolore() {

    DelBicolore(ADRESSE_BROCHES_DEFAUT, 
                NUMERO_BROCHE_ROUGE_DEFAUT, 
                NUMERO_BROCHE_VERT_DEFAUT);

}


DelBicolore::DelBicolore(volatile uint8_t* adresseBrochesSortie, 
                                  uint8_t  numeroBrocheRouge, 
                                  uint8_t  numeroBrocheVert) {

    adresseBrochesSortie_ = adresseBrochesSortie;
    numeroBrocheRouge_ = numeroBrocheRouge;
    numeroBrocheVert_ = numeroBrocheVert;

    if (*adresseBrochesSortie_ == PORTA) {

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
    
    *registreDirectionDonnees_ |= (1 << numeroBrocheRouge_) | (1 << numeroBrocheVert_);
}


DelBicolore::~DelBicolore() {

    eteindre();
    *registreDirectionDonnees_ &= ~((1 << numeroBrocheRouge_) | (1 << numeroBrocheVert_));

}


void DelBicolore::allumer(Couleur couleur) {

    switch (couleur) {
    
        case Couleur::ROUGE:
            *adresseBrochesSortie_ |=  (1 << numeroBrocheRouge_);
            *adresseBrochesSortie_ &= ~(1 << numeroBrocheVert_);
            break;
    
        case Couleur::VERT:
            *adresseBrochesSortie_ |=  (1 << numeroBrocheVert_);
            *adresseBrochesSortie_ &= ~(1 << numeroBrocheRouge_);
            break;
    
    }
}


void DelBicolore::eteindre() {

    *adresseBrochesSortie_ &= ~(1 << numeroBrocheVert_);
    *adresseBrochesSortie_ &= ~(1 << numeroBrocheRouge_);

}

