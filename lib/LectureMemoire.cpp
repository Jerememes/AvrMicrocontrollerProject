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


#include "LectureMemoire.h"


void LectureMemoire::executerModeReprise() {

    while (!programmeTermine_) {

        attendre(lireTempsEnMemoire());
        uint8_t code = lireOctetEnMemoire();
        uint8_t information = lireOctetEnMemoire();

        switch (code){

            case code::POURCENTAGE_G :
                moteur_.ajusterPWMGauche(information);
                break;

            case code::POURCENTAGE_D :
                moteur_.ajusterPWMDroit(information);
                break;

            case code::ACTIVATION_G :
                moteur_.changerActivationMoteurGauche(information);
                break;

            case code::ACTIVATION_D :
                moteur_.changerActivationMoteurDroit(information);
                break;

            case code::DIRECTION_G :
                moteur_.changerDirectionMoteurGauche(information);
                break;

            case code::DIRECTION_D :
                moteur_.changerDirectionMoteurDroit(information);
                break;

            case code::ATTENTE :
                numeroOctet_--;
                break;

            case code::FIN_PARCOURS :
                programmeTermine_ = true;
                break;
        }
    }
}


void LectureMemoire::attendre(uint16_t compteur) {

    const uint8_t TEMPS_INCREMENT_COMPTEUR = 128;   // En microsecondes
                                                    // Pré-calculé en faisant PRESCALER * 1000000 / F_CPU
                                                    // = 1024 * 1000000 / 8000000 = 128
    for (uint16_t i = 0; i < compteur; i++) {
        _delay_us(TEMPS_INCREMENT_COMPTEUR);
    }
}


uint16_t LectureMemoire::lireTempsEnMemoire() {

    uint8_t premiereMoitieTemps = lireOctetEnMemoire();
    uint8_t deuxiemeMoitieTemps = lireOctetEnMemoire();
    return (premiereMoitieTemps << TAILLE_OCTET_) | deuxiemeMoitieTemps;

}


uint8_t LectureMemoire::lireOctetEnMemoire() {

    uint8_t octet;
    gestionnaireMemoire_.lecture(ADRESSE_MEMOIRE_DEBUT_ + 
                                 numeroOctet_, 
                                 &octet);
    numeroOctet_++;
    return octet;
}

