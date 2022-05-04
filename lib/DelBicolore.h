/*
 * Projet Final - DelBicolore.h
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
 *  Ce programme contient la déclaration de la classe DelBicolore, 
 *  on voit les différentes méthodes utilisée dans le fichier DelBicolore.cpp.
 *  Cette classe permet de controler une DEL bicolore.
 * 
 * IDENTIFICATIONS MATÉRIELLES :
 *  Les broches utilisées en sortie sont choisies par le programme qui utilise
 *  la librarie, si le programme ne précise pas les broches, la classe va
 *  utiliser le constructeur par défaut qui utilise A0 et A1 comme sorties.
 * 
*/


#ifndef DEL_BICOLORE_H
#define DEL_BICOLORE_H


#include <avr/io.h>


class DelBicolore{

public:
    
    enum class Couleur {
        VERT,
        ROUGE,
    };
    
    DelBicolore();
    DelBicolore(volatile uint8_t* adresseBrochesSortie, 
                         uint8_t  numeroBrocheRouge, 
                         uint8_t  numeroBrocheVert);
    ~DelBicolore();

    void allumer(Couleur couleur);
    void eteindre();


private:

    volatile uint8_t* const ADRESSE_BROCHES_DEFAUT = &PORTA;
    const    uint8_t        NUMERO_BROCHE_ROUGE_DEFAUT = PA0;
    const    uint8_t        NUMERO_BROCHE_VERT_DEFAUT = PA1;

    volatile uint8_t* adresseBrochesSortie_;
    volatile uint8_t* registreDirectionDonnees_;
             uint8_t  numeroBrocheRouge_;
             uint8_t  numeroBrocheVert_;
             
};


#endif