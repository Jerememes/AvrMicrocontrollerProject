/*
 * TP9 - Debug.h
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
 *  Ce programme contient la déclaration de la classe Debug, 
 *  on voit les différentes méthodes utilisée dans le fichier Debug.cpp.
 *  Cette classe permet de débogger les programmes en utilisant la 
 *  communication RS232.
 * 
 * IDENTIFICATIONS MATÉRIELLES :
 *  D0 en entrée
 *  D1 en sortie
*/


#ifndef DEBUG_H
#define DEBUG_H


#ifdef DEBUG
# define DEBUG_PRINT(x) Debug::afficherString(x)
# define DEBUG_PRINTF(x, y) Debug::afficherStringFormattee(x, y)
#else
# define DEBUG_PRINT(x) do {} while (0)
# define DEBUG_PRINTF(x, y) do {} while (0)
#endif


#include "CommunicationRS232.h"


class Debug {

public:

    static void afficherString(const char* texte);
    static void afficherStringFormattee(const char* texte, 
                                        uint16_t donnee);

private:

    static const uint8_t      NOMBRE_CARACTERES_MAXIMAL_ = 255;
    static CommunicationRS232 communicationRS232_;

};


#endif