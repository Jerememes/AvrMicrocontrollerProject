/*
 * Projet Final - LectureMemoire.h
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
 *  Ce programme contient la déclaration des méthodes de la classe LectureMemoire,
 *  on voit les différentes méthodes utilisée dans le fichier LectureMemoire.cpp.
 *  Ce programme permet de lire en memoire les actions que le moteur doit effectuer
 *  pendant le mode reprise.
 *
 * IDENTIFICATIONS MATÉRIELLES :
 *  Sortie : Tout le port A pour les DELs
 *  Sortie : D5 pour le son
 *  Sortie : B2, B3, B4 et B5 pour le moteur
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


#ifndef LECTURE_MEMOIRE_H
#define LECTURE_MEMOIRE_H


#define F_CPU 8000000UL


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Memoire_24.h"
#include "Moteur.h"
#include "CodeMemoire.h"


class LectureMemoire {

public:
    
    void executerModeReprise();

private:
    
    const uint16_t ADRESSE_MEMOIRE_DEBUT_ = 0x00;
    const uint8_t  TAILLE_OCTET_ = 8;

    uint16_t      numeroOctet_ = 0;
    bool          programmeTermine_ = false;
    Memoire24CXXX gestionnaireMemoire_;
    Moteur        moteur_;

private:

    uint8_t  lireOctetEnMemoire();
    uint16_t lireTempsEnMemoire();
    void     attendre(uint16_t compteur);

};


#endif