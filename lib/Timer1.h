/*
 * Projet Final - Timer1.h
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
 *  Ce programme contient la déclaration de la classe Timer1, 
 *  on voit les différentes méthodes utilisée dans le fichier Timer1.cpp.
 *  Cette classe permet d'initialiser et utiliser le Timer1 du microcontrolleur.
 * 
 * IDENTIFICATIONS MATÉRIELLES :
 *  Pas de broches utilisées.
*/



#ifndef TIMER1_H
#define TIMER1_H
#define F_CPU 8000000UL


#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>


class Timer1 {
public:

    Timer1(uint16_t prescaler);

    void     debuterMinuterie(uint16_t tempsEnSeconde);
    void     debuterChronometre();
    uint16_t ObtenirTempsCompte();
    void     debuterCompteur(uint16_t valeurMaximale);

private:

    uint16_t prescaler_;
};


#endif