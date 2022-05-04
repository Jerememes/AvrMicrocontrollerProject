/*
 * Projet Final - Moteur.cpp
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
 *  Ce programme contient la définition des méthodes de la classe Moteur, 
 *  on voit les différentes méthodes utilisée dans le fichier Moteur.h.
 *  Cette classe permet de controller un moteur.
 * 
 * IDENTIFICATIONS MATÉRIELLES :
 *  B3 et B4 en sortie pour generer le PWM
 *  B2 et B5 en sortie pour la direction du moteur
 *  La broche utilisée pour inverser la direction du moteur et qui est 
 *  relié a a la broche E du pont en H est choisie par le programme qui 
 *  utilise la librarie. 
*/


#include "Moteur.h"


Moteur::Moteur() {

    avancer(true, 
            true);

    TCCR0A  = (1 << COM0A1) | (0 << COM0A0);
    TCCR0A |= (1 << COM0B1) | (0 << COM0B0) | (1 << WGM00);
    TCCR0B  = (1 << CS02)   | (0 << CS01)   | (0 << CS00);

}


void Moteur::ajusterPWMGauche(uint8_t pourcentagePWM) {

    if (pourcentagePWM != pourcentagePwmGauche_) {

        pourcentagePwmGauche_ = pourcentagePWM;

        OCR0A = pourcentagePWM * 0xFF / 100;

        if (ecritureMemoireActivee_) {
            demarrerEcritureMemoire();
            memoire_.ecrirePourcentageGauche(pourcentagePWM);
        }
    }
}


void Moteur::ajusterPWMDroit(uint8_t pourcentagePWM) {

    if (pourcentagePWM != pourcentagePwmDroit_) {

        pourcentagePwmDroit_  = pourcentagePWM;

        OCR0B = pourcentagePWM  * 0xFF / 100;

        if (ecritureMemoireActivee_) {

            demarrerEcritureMemoire();
            memoire_.ecrirePourcentageDroit(pourcentagePWM);
        
        }
    }
}


void Moteur::changerActivationMoteurGauche(bool active) {

    if (active != roueGaucheActivee_) {
        roueGaucheActivee_ = active;

        DDRB &= ~(1 << PB3);
        DDRB |= (active << PB3);

        if (ecritureMemoireActivee_) {

            demarrerEcritureMemoire();
            memoire_.ecrireActivationGauche(active);
        
        }
    }
}


void Moteur::changerActivationMoteurDroit(bool active) {

    if (active != roueDroiteActivee_) {

        roueDroiteActivee_ = active;

        DDRB &= ~(1 << PB4);
        DDRB |= (active << PB4);

        if (ecritureMemoireActivee_) {

            demarrerEcritureMemoire();
            memoire_.ecrireActivationDroit(active);
        }
    }
}


void Moteur::changerDirectionMoteurGauche(bool avancer) {

    if (avancer != roueGaucheAvance_) {

        roueGaucheAvance_ = avancer;

        if (avancer) {

            PORTB |= (1 << PB2);
        
        } 
        else {
        
            PORTB &= ~(1 << PB2);
        
        }
        
        if (ecritureMemoireActivee_) {
        
            demarrerEcritureMemoire();
            memoire_.ecrireDirectionGauche(avancer);
        
        }
    }
}


void Moteur::changerDirectionMoteurDroit(bool avancer) {
    if (avancer != roueDroiteAvance_) {
        
        roueDroiteAvance_ = avancer;

        if (avancer) {
        
            PORTB |= (1 << PB5);
        
        } else {
        
            PORTB &= ~(1 << PB5);
        
        }
        
        if (ecritureMemoireActivee_) {
        
            demarrerEcritureMemoire();
            memoire_.ecrireDirectionDroit(avancer);
        
        }
    }
}


void Moteur::ajusterPWM(uint8_t pourcentageCoteGauche, 
                        uint8_t pourcentageCoteDroit){

    ajusterPWMGauche(pourcentageCoteGauche);
    ajusterPWMDroit(pourcentageCoteDroit);
}


void Moteur::changerMoteurActive(bool coteGauche, 
                                 bool coteDroit){

    changerActivationMoteurGauche(coteGauche);
    changerActivationMoteurDroit(coteDroit);
}


void Moteur::avancer(bool coteGauche, 
                     bool coteDroit){

    if (coteGauche) {

        changerDirectionMoteurGauche(true);
    
    }
    if (coteDroit) {

        changerDirectionMoteurDroit (true);
    
    }
}


void Moteur::reculer(bool coteGauche, 
                     bool coteDroit){

    if (coteGauche) {
    
        changerDirectionMoteurGauche(false);
    
    }
    if (coteDroit) {
    
        changerDirectionMoteurDroit (false);
    
    }
}


void Moteur::stopperMoteur(){

    changerMoteurActive(false, 
                        false);

    if (ecritureMemoireActivee_) {
    
        ecritureMemoireEnCours_ = false;
        memoire_.arreterEcriture();
    
    }
}


void Moteur::activerEcritureMemoire(){
    
    ecritureMemoireActivee_ = true;

}


void Moteur::demarrerEcritureMemoire(){

    if (!ecritureMemoireEnCours_) {

        memoire_.commencerEcriture();
        ecritureMemoireEnCours_ = true;

    }
}


void Moteur::terminerEcritureMemoire() {

    if (ecritureMemoireActivee_) {

        memoire_.commencerEcriture();
        ecritureMemoireActivee_ = false;
        ecritureMemoireEnCours_ = false;
        memoire_.ecrireFinParcours();

    }
}


uint8_t Moteur::obtenirPwmGauche() {

    return pourcentagePwmGauche_;

}


uint8_t Moteur::obtenirPwmDroit() {

    return pourcentagePwmDroit_;

}

