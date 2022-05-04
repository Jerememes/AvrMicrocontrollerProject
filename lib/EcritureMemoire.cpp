/*
 * Projet Final - EcritureMemoire.cpp
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
 *  Ce programme contient la définition des méthodes de la classe EcritureMemoire,
 *  on voit les différentes méthodes utilisée dans le fichier EcritureMemoire.h.
 *  Ce programme permet d'écrire en memoire externe toutes les actions effectuees
 *  par le moteur afin de pouvoir les reproduire en mode reprise.
 *
 * IDENTIFICATIONS MATÉRIELLES :
 *  D0 en entrée
 *  D1 en sortie
 *  C0 et C1 pour accéder à la mémoire
 */


#include "EcritureMemoire.h"


uint8_t EcritureMemoire::nombreIterationsMinuterie_ = 0;
bool    EcritureMemoire::minuterieActive_ = false;


ISR (TIMER1_COMPA_vect) {

    EcritureMemoire::incrementerNombreIterationsMinuterie();

}


void EcritureMemoire::incrementerNombreIterationsMinuterie() {
 
    if (minuterieActive_) {
        nombreIterationsMinuterie_++;
    }
}


void EcritureMemoire::ecrireIterationsMinuterie() {
    
    for (uint8_t i = 0; i < nombreIterationsMinuterie_; i++) {
        ecrireDeuxOctetsEnMemoire(MAX_COMPTEUR);
        ecrireOctetEnMemoire(code::ATTENTE);
    }
    
    nombreIterationsMinuterie_ = 0;
}


void EcritureMemoire::commencerEcriture() {
    
    nombreIterationsMinuterie_ = 0;
    minuterie_.debuterCompteur(MAX_COMPTEUR);
    minuterieActive_ = true;

}


void EcritureMemoire::arreterEcriture() {
    
    minuterieActive_ = false;

}


void EcritureMemoire::ecrireFinParcours() {

    ecrireTempsAttente();
    ecrireOctetEnMemoire(code::FIN_PARCOURS);
    arreterEcriture();

}


void EcritureMemoire::ecrirePourcentageGauche(uint8_t pourcentageGauche) {

    ecrireTempsAttente();
    ecrireOctetEnMemoire(code::POURCENTAGE_G);
    ecrireOctetEnMemoire(pourcentageGauche);

}


void EcritureMemoire::ecrirePourcentageDroit(uint8_t pourcentageDroit) {

    ecrireTempsAttente();
    ecrireOctetEnMemoire(code::POURCENTAGE_D);
    ecrireOctetEnMemoire(pourcentageDroit);

}


void EcritureMemoire::ecrireActivationGauche(bool moteurGaucheActive) {

    ecrireTempsAttente();
    ecrireOctetEnMemoire(code::ACTIVATION_G);
    ecrireOctetEnMemoire(moteurGaucheActive);

}


void EcritureMemoire::ecrireActivationDroit(bool moteurDroitActive) {

    ecrireTempsAttente();
    ecrireOctetEnMemoire(code::ACTIVATION_D);
    ecrireOctetEnMemoire(moteurDroitActive);

}


void EcritureMemoire::ecrireDirectionGauche(bool moteurGaucheAvance) {

    ecrireTempsAttente();
    ecrireOctetEnMemoire(code::DIRECTION_G);
    ecrireOctetEnMemoire(moteurGaucheAvance);

}


void EcritureMemoire::ecrireDirectionDroit(bool moteurDroitAvance) {

    ecrireTempsAttente();
    ecrireOctetEnMemoire(code::DIRECTION_D);
    ecrireOctetEnMemoire(moteurDroitAvance);

}


void EcritureMemoire::ecrireTempsAttente() {

    ecrireIterationsMinuterie();
    ecrireDeuxOctetsEnMemoire(TCNT1);
    minuterie_.debuterCompteur(MAX_COMPTEUR);

}


void EcritureMemoire::ecrireDeuxOctetsEnMemoire(uint16_t octets) {

    uint8_t premierOctet  = octets >> TAILLE_OCTET_;
    uint8_t deuxiemeOctet = octets - premierOctet;
    ecrireOctetEnMemoire(premierOctet);
    ecrireOctetEnMemoire(deuxiemeOctet);

}


void EcritureMemoire::ecrireOctetEnMemoire(uint8_t octet) {

    const uint8_t DELAI = 5;
    gestionnaireMemoire_.ecriture(ADRESSE_MEMOIRE_DEBUT_ + numeroOctet_, 
                                  octet);
    _delay_ms(DELAI);
    numeroOctet_++;
    
}

