/*
 * Projet Final - CodeMemoire.h
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
 *  Ce fichier contient le namespace code qui définit les codes utilisés
 *  par EcritureMemoire et LectureMemoire.
 *
 * IDENTIFICATIONS MATÉRIELLES :
 *  D0 en entrée
 *  D1 en sortie
 *  C0 et C1 pour accéder à la mémoire
 */


#ifndef CODE_MEMOIRE_H
#define CODE_MEMOIRE_H


#define F_CPU 8000000UL


namespace code {
    const uint8_t POURCENTAGE_G = 0;
    const uint8_t POURCENTAGE_D = 1;
    const uint8_t ACTIVATION_G  = 2;
    const uint8_t ACTIVATION_D  = 3;
    const uint8_t DIRECTION_G   = 4;
    const uint8_t DIRECTION_D   = 5;
    const uint8_t ATTENTE       = 6;
    const uint8_t FIN_PARCOURS  = 7;
}


#endif