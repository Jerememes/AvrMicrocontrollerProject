/*
 * TP9 - Debug.cpp
 * Date de remise : 22 mars 2022
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
 *  Ce programme contient la définition des méthodes de la classe Debug, 
 *  on voit les différentes méthodes utilisée dans le fichier Debug.h.
 *  Cette classe permet de débogger les programmes en utilisant la 
 *  communication RS232.
 * 
 * IDENTIFICATIONS MATÉRIELLES :
 *  D0 en entrée
 *  D1 en sortie
*/


#include "Debug.h"


CommunicationRS232 Debug::communicationRS232_;


void Debug::afficherStringFormattee(const char* texte, 
                                    uint16_t donnee) {

    char tampon[NOMBRE_CARACTERES_MAXIMAL_];
    
    sprintf(tampon, 
            texte, 
            donnee);

    communicationRS232_.transmettreUART(tampon);

}


void Debug::afficherString(const char* texte) {

    communicationRS232_.transmettreUART(texte);

}