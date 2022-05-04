/*
 * Projet Final - Bouton.h
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
 *  Ce programme contient la déclaration de la classe Bouton, on voit les
 *  différentes méthodes utilisée dans le fichier Bouton.cpp.
 *  Cette classe permet de créer un objet bouton qui permet de controller 
 *  un bouton par scrutation, et qui a 4 états possibles.
 * 
 * IDENTIFICATIONS MATÉRIELLES :
 *  La broche utilisée en entrée est choisie par le programme qui utilise
 *  la librarie. 
 * 
 * Machine à état:
 +--------------+--------+---------------+
 | État courant | Entrée | Prochain état |
 +--------------+--------+---------------+
 | AUCUN        |      0 | AUCUN         |
 | AUCUN        |      1 | APPUYE        |
 | APPUYE       |      0 | RELACHE       |
 | APPUYE       |      1 | MAINTENU      |
 | MAINTENU     |      0 | RELACHE       |
 | MAINTENU     |      1 | MAINTENU      |
 | RELACHE      |      0 | AUCUN         |
 | RELACHE      |      1 | APPUYE        |
 +--------------+--------+---------------+
 *
 */


#ifndef BOUTON_H
#define BOUTON_H
#define F_CPU 8000000UL


#include <avr/io.h>
#include <util/delay.h>


class Bouton {

public:

    enum class Etat {
        AUCUN,
        APPUYE,
        MAINTENU,
        RELACHE,
    };

    Bouton(volatile uint8_t* adresseBrochesEntree, 
                    uint8_t  numeroBroche);

    ~Bouton();

    Etat obtenirEtat();

private:

    static const uint8_t DELAI_DEBOUNCE = 10;

    Etat              etat_;
    volatile uint8_t* registreDirectionDonnees_;
    volatile uint8_t* adresseBrochesEntree_;
             uint8_t  numeroBroche_;

private:

    void mettreAJourEtat();
    bool estAppuye();

};


#endif