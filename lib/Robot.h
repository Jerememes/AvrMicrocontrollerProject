/*
 * Projet Final - Robot.h
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
 *  Ce programme contient la déclaration de la classe Robot, 
 *  on voit les différentes méthodes utilisée dans le fichier Robot.cpp.
 *  Cette classe permet de contrôler les différents aspetcs du robot.
 * 
 * IDENTIFICATIONS MATÉRIELLES :
 *  Sortie : Tout le port A pour les DELs
 *  Sortie : D5 pour le son
 *  Sortie : B2, B3, B4 et B5 pour le moteur
*/


#ifndef ROBOT_H
#define ROBOT_H
#define F_CPU 8000000UL


#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "DelBicolore.h"
#include "Moteur.h"
#include "CapteurDistance.h"
#include "Debug.h"
#include "Can.h"


class Robot {

public:

    Robot();
    ~Robot() = default;

    void    activerEcritureMemoire();
    void    suivreMur();
    void    suivreLumiere();
    void    faireDemiTour();
    void    finirParcours();

    uint8_t calculerDistanceAuMurEnCm();
    bool    detecterPresenceMur();
    bool    detecterLumiere();
    void    calculerLumiereAmbiante();
    void    clignotterDel(DelBicolore::Couleur couleur);

    bool aFaitDemiTour_ = false;
    
private:

    Moteur          moteur_;
    CapteurDistance capteurDistance_;
    DelBicolore     del_;
    Can             can_;
    uint8_t         lumiereAmbiante_;
    int8_t          ajustementPhotoresistanceGauche_;

private:

    void    avancerToutDroit(uint8_t pourcentagePWM);
    void    avancerEnTournant(uint8_t pourcentageCoteGauche, 
                              uint8_t pourcentageCoteDroit);
    void    pivoter(uint8_t pourcentagePWM, 
                    bool    versLaDroite);
    void    arreter();
    uint8_t calculerMedianeDistanceCapteur();
    uint8_t calculerVitesse(uint8_t intensiteLumiere);
    uint8_t calculerVitesseTourner(uint8_t differenceLumiereGaucheDroite);
    int8_t  calculerVitesseModeMur(uint8_t distanceAuMur);

};


#endif