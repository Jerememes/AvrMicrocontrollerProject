/*
 * Projet - CapteurDistance.cpp
 * Date de remise : 2o avril 2022
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


#include "CapteurDistance.h"


const uint8_t PIN_CAPTEUR = 6;


CapteurDistance::CapteurDistance(){

    lumiereAmbiante_ = obtenirValeurConvertisseur();

}


uint16_t CapteurDistance::obtenirValeurConvertisseur(){

    return convertisseurAnalogique_.lecture8bits(PIN_CAPTEUR);

}


uint8_t CapteurDistance::calculerDistanceMur(){

    uint16_t valeurConvertiseurAnalogique = obtenirValeurConvertisseur();

    if        (valeurConvertiseurAnalogique <= 20) {

        return 62;

    } 
    else if (valeurConvertiseurAnalogique <= 21) {
        
        return 61;
    
    }
    else if (valeurConvertiseurAnalogique <= 22) {
        
        return 60;
    
    } 
    else if (valeurConvertiseurAnalogique <= 23) {
        
        return 59;
    
    } 
    else if (valeurConvertiseurAnalogique <= 24) {
        
        return 58;
    
    } 
    else if (valeurConvertiseurAnalogique <= 25) {
        
        return 56;
    
    } 
    else if (valeurConvertiseurAnalogique <= 26) {
        
        return 55;
    
    } 
    else if (valeurConvertiseurAnalogique <= 27) {
        
        return 54;
    
    } 
    else if (valeurConvertiseurAnalogique <= 28) {
        
        return 52;
    
    } 
    else if (valeurConvertiseurAnalogique <= 30) {
        
        return 51;
    
    } 
    else if (valeurConvertiseurAnalogique <= 31) {
        
        return 50;
    
    } 
    else if (valeurConvertiseurAnalogique <= 32) {
        
        return 49;
    
    } 
    else if (valeurConvertiseurAnalogique <= 33) {
        
        return 47;
    
    } 
    else if (valeurConvertiseurAnalogique <= 34) {
        
        return 46;
    
    } 
    else if (valeurConvertiseurAnalogique <= 36) {
        
        return 45;
    
    } 
    else if (valeurConvertiseurAnalogique <= 37) {
        
        return 44;
    
    } 
    else if (valeurConvertiseurAnalogique <= 38) {
        
        return 43;
    
    } 
    else if (valeurConvertiseurAnalogique <= 39) {
        
        return 42;
    
    } 
    else if (valeurConvertiseurAnalogique <= 40) {
        
        return 41;
    
    } 
    else if (valeurConvertiseurAnalogique <= 41) {
        
        return 39;
    
    } 
    else if (valeurConvertiseurAnalogique <= 42) {
        
        return 38;
    
    }
    else if (valeurConvertiseurAnalogique <= 43) {
        
        return 37;
    
    } 
    else if (valeurConvertiseurAnalogique <= 45) {
        
        return 36;
    
    } 
    else if (valeurConvertiseurAnalogique <= 46) {
        
        return 35;
    
    } 
    else if (valeurConvertiseurAnalogique <= 47) {
        
        return 34;
    
    } 
    else if (valeurConvertiseurAnalogique <= 48) {
        
        return 33;
    
    } 
    else if (valeurConvertiseurAnalogique <= 50) {
        
        return 32;
    
    } 
    else if (valeurConvertiseurAnalogique <= 51) {
        
        return 31;
    
    } 
    else if (valeurConvertiseurAnalogique <= 54) {
        
        return 30;
    
    } 
    else if (valeurConvertiseurAnalogique <= 56) {
        
        return 29;
    
    } 
    else if (valeurConvertiseurAnalogique <= 58) {
        
        return 28;
    
    }
    else if (valeurConvertiseurAnalogique <= 59) {
        
        return 27;
    
    } 
    else if (valeurConvertiseurAnalogique <= 61) {
        
        return 26;
    
    } 
    else if (valeurConvertiseurAnalogique <= 63) {
        
        return 25;
    
    } 
    else if (valeurConvertiseurAnalogique <= 64) {
        
        return 24;
    
    } 
    else if (valeurConvertiseurAnalogique <= 68) {
        
        return 23;
    
    } 
    else if (valeurConvertiseurAnalogique <= 69) {
        
        return 22;
    
    } 
    else if (valeurConvertiseurAnalogique <= 71) {
        
        return 21;
    
    } 
    else if (valeurConvertiseurAnalogique <= 76) {
        
        return 20;
    
    } 
    else if (valeurConvertiseurAnalogique <= 80) {
        
        return 19;
    
    } 
    else if (valeurConvertiseurAnalogique <= 84) {
        
        return 18;
    
    } 
    else if (valeurConvertiseurAnalogique <= 90) {
        
        return 17;
    
    } 
    else if (valeurConvertiseurAnalogique <= 93) {
        
        return 16;
    
    } 
    else if (valeurConvertiseurAnalogique <= 97) {
        
        return 15;
    
    } 
    else if (valeurConvertiseurAnalogique <= 102) {
        
        return 14;
    
    } 
    else if (valeurConvertiseurAnalogique <= 110) {
        
        return 13;
    
    } 
    else if (valeurConvertiseurAnalogique <= 121) {
        
        return 12;
    
    } 
    else if (valeurConvertiseurAnalogique <= 131) {
        
        return 11;
    
    } 
    else if (valeurConvertiseurAnalogique <= 142) {
        
        return 10;
    
    } 
    else if (valeurConvertiseurAnalogique <= 160) {
        
        return 9;
    
    } 
    else if (valeurConvertiseurAnalogique <= 172) {
        
        return 8;
    
    } 
    else {
        
        return 7;
    
    }
}

