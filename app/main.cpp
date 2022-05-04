/*
 * Projet Final - main.cpp
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
 * Ce programme va combiner l'entièreté des fonctionnalités qui ont été développées
 * tout au long du projet. Ces fonctionnalités vont regroupé les fonctions:
 * -suivreLumiere()
 * -suivreMur()
 * -faireDemiTour()
 * -lireMemoire()
 * Pour changer d'une fonction à une autre, une machine à état a été implantée pour 
 * gérer la gestion d'état.
 * 
 *
 * IDENTIFICATIONS MATÉRIELLES :
 *  Entrée : A0 et A1 pour les photorésistances
 *  Sortie : A2 et A3 pour la DEL
 *  Entrée : A6 pour le capteur infrarouge
 *  Sortie : B2, B3, B4 et B5 pour le moteur
 *  Entrée : D2 pour le bouton interrupt
 *  Entrée : D0 pour le bouton poussoir
 *  C0 et C1 pour accéder à la mémoire
 * 
 * Machine à état:
 * 
 
+--------------------------------------+---------------------+-------------------------+----------------------+------------------+--------------------------------------+
|             État Courant             | Entrée Bouton Blanc | Entrée Bouton Interrupt | Détection de lumière | Détection de mur | Prochain État                        |
+--------------------------------------+---------------------+-------------------------+----------------------+------------------+--------------------------------------+
| ATTENTE_RECEVOIR_INSTRUCTION_DEBUT   | 0                   | 0                       | x                    | x                | ATTENTE_RECEVOIR_INSTRUCTION_DEBUT   |
| ATTENTE_RECEVOIR_INSTRUCTION_DEBUT   | 0                   | 1                       | x                    | x                | SUIVRE_MUR                           |
| ATTENTE_RECEVOIR_INSTRUCTION_DEBUT   | 1                   | 0                       | x                    | x                | LIRE_MEMOIRE                         |
| ATTENTE_RECEVOIR_INSTRUCTION_DEBUT   | 1                   | 1                       | x                    | x                | LIRE_MEMOIRE                         |
+--------------------------------------+---------------------+-------------------------+----------------------+------------------+--------------------------------------+
| ATTENTE_RECEVOIR_INSTRUCTION_FIN_MUR | 0                   | 0                       | 0                    | x                | ATTENTE_RECEVOIR_INSTRUCTION_FIN_MUR |
| ATTENTE_RECEVOIR_INSTRUCTION_FIN_MUR | 1                   | 0                       | 0                    | x                | FAIRE_DEMI_TOUR                      |
| ATTENTE_RECEVOIR_INSTRUCTION_FIN_MUR | 0                   | 1                       | 0                    | x                | FIN                                  |
| ATTENTE_RECEVOIR_INSTRUCTION_FIN_MUR | 1                   | 1                       | 0                    | x                | FIN                                  |
| ATTENTE_RECEVOIR_INSTRUCTION_FIN_MUR | x                   | x                       | 1                    | x                | SUIVRE_LUMIERE                       |
+--------------------------------------+---------------------+-------------------------+----------------------+------------------+--------------------------------------+
| SUIVRE_MUR                           | x                   | x                       | x                    | 1                | SUIVRE_MUR                           |
| SUIVRE_MUR                           | x                   | x                       | x                    | 0                | ATTENTE_RECEVOIR_INSTRUCTION_FIN_MUR |
+--------------------------------------+---------------------+-------------------------+----------------------+------------------+--------------------------------------+
| SUIVRE_LUMIERE                       | x                   | x                       | x                    | 0                | SUIVRE_LUMIERE                       |
| SUIVRE_LUMIERE                       | x                   | x                       | x                    | 1                | SUIVRE_MUR                           |
+--------------------------------------+---------------------+-------------------------+----------------------+------------------+--------------------------------------+
| FAIRE_DEMI_TOUR                      | x                   | x                       | x                    | 0                | FAIRE_DEMI_TOUR                      |
| FAIRE_DEMI_TOUR                      | x                   | x                       | x                    | 1                | SUIVRE_MUR                           |
+--------------------------------------+---------------------+-------------------------+----------------------+------------------+--------------------------------------+
| LIRE_MEMOIRE                         | x                   | x                       | x                    | x                | FIN                                  |
+--------------------------------------+---------------------+-------------------------+----------------------+------------------+--------------------------------------+
| FIN                                  | x                   | x                       | x                    | x                | FIN                                  |
+--------------------------------------+---------------------+-------------------------+----------------------+------------------+--------------------------------------+


 */

#define F_CPU 8000000UL
#include <avr/io.h>
#include "Bouton.h"
#include "LectureMemoire.h"
#include "Robot.h"


enum class Mode {
    ATTENTE_RECEVOIR_INSTRUCTION_DEBUT,
    ATTENTE_RECEVOIR_INSTRUCTION_FIN_MUR,
    SUIVRE_MUR,
    SUIVRE_LUMIERE,
    FAIRE_DEMI_TOUR,
    LIRE_MEMOIRE,
    FIN
};

int main() {

    Bouton         boutonBlanc(&PIND, PD0);
    Bouton         boutonInterrupt(&PIND, PD2);
    LectureMemoire memoire;
    Robot          robot;
    
    Mode mode = Mode::ATTENTE_RECEVOIR_INSTRUCTION_DEBUT;
    while (true) {
        switch (mode) {
            case Mode::ATTENTE_RECEVOIR_INSTRUCTION_DEBUT :
                if (boutonBlanc.obtenirEtat() == Bouton::Etat::RELACHE) {
                    robot.clignotterDel(DelBicolore::Couleur::ROUGE);
                    mode = Mode::LIRE_MEMOIRE;
                }
                if (boutonInterrupt.obtenirEtat() == Bouton::Etat::APPUYE) {
                    robot.clignotterDel(DelBicolore::Couleur::VERT);
                    robot.calculerLumiereAmbiante();
                    robot.activerEcritureMemoire();
                    mode = Mode::SUIVRE_MUR;
                }
                break;

            case Mode::ATTENTE_RECEVOIR_INSTRUCTION_FIN_MUR :
                if(robot.detecterLumiere()) {
                    mode = Mode::SUIVRE_LUMIERE;
                }
                if (boutonBlanc.obtenirEtat() == Bouton::Etat::RELACHE) {
                    mode = Mode::FAIRE_DEMI_TOUR;
                }
                if (boutonInterrupt.obtenirEtat() == Bouton::Etat::APPUYE) {
                    mode = Mode::FIN;
                }
                break;

            case Mode::SUIVRE_MUR :                
                robot.suivreMur();
                mode = Mode::ATTENTE_RECEVOIR_INSTRUCTION_FIN_MUR;
                break;
            
            case Mode::SUIVRE_LUMIERE :
                robot.suivreLumiere();
                mode = Mode::SUIVRE_MUR;
                break;
            
            case Mode::FAIRE_DEMI_TOUR :
                robot.faireDemiTour();
                mode = Mode::SUIVRE_MUR;
                break;
            
            case Mode::LIRE_MEMOIRE :
                memoire.executerModeReprise();
                mode = Mode::FIN;
                break;
            
            case Mode::FIN :
                robot.finirParcours();
                break;
        }
    }
    return 0;
}