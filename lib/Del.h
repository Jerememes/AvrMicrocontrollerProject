/*
 * Projet Final - Del.h
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
 *  Ce programme contient la déclaration de la classe Del, 
 *  on voit les différentes méthodes utilisée dans le fichier Del.cpp.
 *  Cette classe permet de controler une DEL.
 * 
 * IDENTIFICATIONS MATÉRIELLES :
 *  Les broches utilisées en sortie sont choisies par le programme qui utilise
 *  la librarie. 
*/


#ifndef DEL_H
#define DEL_H


#include <avr/io.h>


class Del {

public:

    Del(volatile uint8_t* adresseBrochesSortie, 
                 uint8_t  numeroBroche);
    ~Del();

    void allumer();
    void eteindre();

private:

    volatile uint8_t* adresseBrochesSortie_;
    volatile uint8_t* registreDirectionDonnees_;
             uint8_t  numeroBroche_;
};


#endif