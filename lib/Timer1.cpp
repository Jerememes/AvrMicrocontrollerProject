/*
 * Projet Final - Timer1.cpp
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
 *  Ce programme contient la définition des méthodes de la classe Timer1, 
 *  on voit les différentes méthodes utilisée dans le fichier Timer1.h.
 *  Cette classe permet d'initialiser et utiliser le Timer1 du microcontrolleur.
 * 
 * IDENTIFICATIONS MATÉRIELLES :
 *  Pas de broches utilisées.
*/


#include "Timer1.h"


Timer1::Timer1(uint16_t prescaler = 1024){
    cli();
    prescaler_ = prescaler;
    TCCR1A     = 0;

    TCCR1B |= (1 << WGM12);

    switch (prescaler_){
        case 1:
        TCCR1B |= (0 << CS12) | (0 << CS11) | (1 << CS10);
        case 8:
        TCCR1B |= (0 << CS12) | (1 << CS11) | (0 << CS10);
        case 64:
        TCCR1B |= (0 << CS12) | (1 << CS11) | (1 << CS10);
        case 256:
        TCCR1B |= (1 << CS12) | (0 << CS11) | (0 << CS10);
        case 1024:
        TCCR1B |= (1 << CS12) | (0 << CS11) | (1 << CS10);
    }
    TCCR1C = 0;
    TIMSK1 = (1 << OCIE1A) | (1 << ICIE1);
    sei();
}


void Timer1::debuterMinuterie(uint16_t tempsEnSeconde){
    cli();
    uint16_t valeurAComparer = F_CPU * tempsEnSeconde / prescaler_;
    TCCR1A = (1 << WGM12) | (0 << WGM11) | (0 << WGM10);
    TCNT1  = 0;
    OCR1A  = valeurAComparer;
    sei();
}


void Timer1::debuterCompteur(uint16_t valeurMaximale) {
    cli();
    TCCR1A = (1 << WGM12);
    TCNT1  = 0;
    OCR1A  = valeurMaximale;
    sei();
}


void Timer1::debuterChronometre(){
    TCNT1 = 0;
}


uint16_t Timer1::ObtenirTempsCompte(){
    return TCNT1 * prescaler_ / F_CPU ;
}

