/*
 * Projet Final - EcritureMemoire.h
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
 *  Ce programme contient la déclaration des méthodes de la classe EcritureMemoire,
 *  on voit les différentes méthodes utilisée dans le fichier EcritureMemoire.cpp.
 *  Ce programme permet d'écrire en memoire externe toutes les actions effectuees
 *  par le moteur afin de pouvoir les reproduire en mode reprise.
 *
 * IDENTIFICATIONS MATÉRIELLES :
 *  D0 en entrée
 *  D1 en sortie
 *  C0 et C1 pour accéder à la mémoire
 */

/*
DESCRIPTION DE L'ORGANISATION DES INFORMATIONS EN MEMOIRE :

Chaque action que le moteur doit effectuer s'ecrit sur 4 octets.
Il y a toujours deux octets de temps d'attente, puis un code sur un octet et
finalement une information sur un octet. Le code permet de determiner comment
il faut interpreter l'information qui le suit.
Par rapport au tp9, le code peut etre compare a l'instruction et l'information
a l'operande.
IL y a une exception a cette structure : si le code est ATTENTE, il n'y a pas
d'information qui le suit. Seul le temps d'attente precedent le code est 
important car le moteur n'a pas a effectuer une nouvelle action.

Structure :   --- 2 octets ---|- 1 octet -|- 1 octet -
              temps d'attente |   code    | information

Code          | Information enregistree
--------------|---------------------------------
POURCENTAGE_G | pourcentageGauche  -> 0 a 100 %
POURCENTAGE_D | pourcentageDroit   -> 0 a 100 %
ACTIVATION_G  | moteurGaucheActive -> 0 ou 1
ACTIVATION_D  | moteurDroitActive  -> 0 ou 1
DIRECTION_G   | moteurGaucheAvance -> 0 ou 1
DIRECTION_D   | moteurDroitAvance  -> 0 ou 1
ATTENTE       | 
FIN_PARCOURS  | fin du parcours
*/


#ifndef ECRITURE_MEMOIRE_H
#define ECRITURE_MEMOIRE_H


#define F_CPU 8000000UL


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Memoire_24.h"
#include "Timer1.h"
#include "CodeMemoire.h"


class EcritureMemoire {

public:

    EcritureMemoire()  = default;
    ~EcritureMemoire() = default;

    void commencerEcriture();
    void arreterEcriture();

    void ecrirePourcentageGauche(uint8_t pourcentageGauche);
    void ecrirePourcentageDroit(uint8_t pourcentageDroit);
    void ecrireActivationGauche(bool moteurGaucheActive);
    void ecrireActivationDroit(bool moteurDroitActive);
    void ecrireDirectionGauche(bool moteurGaucheAvance);
    void ecrireDirectionDroit(bool moteurDroitAvance);
    void ecrireFinParcours();

    static void incrementerNombreIterationsMinuterie();

private:

    const uint16_t ADRESSE_MEMOIRE_DEBUT_ = 0x00;
    const uint8_t  TAILLE_OCTET_ = 8;
    const uint16_t MAX_COMPTEUR = 0xFFFF;
    const uint16_t PRESCALER_ = 1024;

    Memoire24CXXX   gestionnaireMemoire_;
    Timer1          minuterie_ = Timer1(PRESCALER_);
    uint16_t        numeroOctet_ = 0;
    static uint8_t  nombreIterationsMinuterie_;
    static bool     minuterieActive_;

private:

    void ecrireOctetEnMemoire(uint8_t  octet);
    void ecrireDeuxOctetsEnMemoire(uint16_t octets);
    void ecrireTempsAttente();
    void ecrireIterationsMinuterie();

};


#endif