/*
 * Projet Final - CapteurDistance.h
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
 *  Ce programme contient la déclaration de la classe CapteurDistance, 
 *  on voit les différentes méthodes utilisée dans le fichier CapteurDistance.cpp.
 *  Cette classe permet de controller un capteur de distance.
 * 
 * IDENTIFICATIONS MATÉRIELLES :
 * Entrée : A6 pour le capteur infrarouge
*/


#define F_CPU 8000000UL
#include "Can.h"
#include <util/delay.h>


#ifndef CAPTEURDISTANCE_H
#define CAPTEURDISTANCE_H


class CapteurDistance {

public:

    CapteurDistance();
    ~CapteurDistance() = default;

    uint8_t  calculerDistanceMur();
    uint16_t obtenirValeurConvertisseur();
    
private:

    uint8_t lumiereAmbiante_;
    Can     convertisseurAnalogique_ = Can();

};


#endif