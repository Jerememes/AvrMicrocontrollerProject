/*
 * Projet Final - Moteur.h
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
 *  Ce programme contient la déclaration de la classe Moteur, 
 *  on voit les différentes méthodes utilisée dans le fichier Moteur.cpp.
 *  Cette classe permet de controller un moteur.
 * 
 * IDENTIFICATIONS MATÉRIELLES :
 *  B3 et B4 en sortie pour generer le PWM
 *  B2 et B5 en sortie pour la direction du moteur
 *  La broche utilisée pour inverser la direction du moteur et qui est 
 *  relié a a la broche E du pont en H est choisie par le programme qui 
 *  utilise la librarie. 
*/


#define F_CPU 8000000UL


#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "EcritureMemoire.h"
#include "Debug.h"


#ifndef MOTEUR_H
#define MOTEUR_H


class Moteur {

public:

    Moteur();
    void ajusterPWM(uint8_t pourcentageCoteGauche, 
                    uint8_t pourcentageCoteDroit);
    void changerMoteurActive(bool coteGauche, 
                             bool coteDroit);
    void avancer(bool coteGauche, 
                 bool coteDroit);
    void reculer(bool coteGauche, 
                 bool coteDroit);
    void stopperMoteur();

    void ajusterPWMGauche(uint8_t pourcentagePWM);
    void ajusterPWMDroit(uint8_t pourcentagePWM);
    void changerActivationMoteurGauche(bool active);
    void changerActivationMoteurDroit(bool active);
    void changerDirectionMoteurGauche(bool avancer);
    void changerDirectionMoteurDroit(bool avancer);

    uint8_t obtenirPwmGauche();
    uint8_t obtenirPwmDroit();

    void activerEcritureMemoire();
    void terminerEcritureMemoire();

private:

    EcritureMemoire memoire_;

    uint8_t pourcentagePwmGauche_ = 0;
    uint8_t pourcentagePwmDroit_  = 0;

    bool roueGaucheActivee_ = false;
    bool roueDroiteActivee_ = false;
    bool roueGaucheAvance_ = false;
    bool roueDroiteAvance_ = false;
    
    bool ecritureMemoireEnCours_ = false;
    bool ecritureMemoireActivee_ = false;

private:

    void demarrerEcritureMemoire();

};


#endif