/*
 * Projet Final - Robot.cpp
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
 *  Ce programme contient la définition des méthodes de la classe Robot,
 *  on voit les différentes méthodes utilisée dans le fichier Robot.h.
 *  Cette classe permet de contrôler les différents aspetcs du robot.
 *
 * IDENTIFICATIONS MATÉRIELLES :
 *  Sortie : Tout les broches A2, A3 pour les DELs bicolores.
 *  Entrée : A6 pour le capteur infrarouge.
 *  Sortie : B2, B3, B4 et B5 pour le moteur
 * 
 */


#include "Robot.h"
#include "Debug.h"


// DEL
const uint8_t TEMPS_CLIGNOTTEMENT_DEL = 3; // En secondes
const uint8_t FREQUENCE_CLIGNOTTEMENT_DEL = 5;
const uint16_t SECONDES_EN_MILLISECONDES = 1000;


// POUR AVANCER TOUT DROIT
const uint8_t AJUSTEMENT_PWM = 2;


// DEMI-TOUR
const uint16_t TEMPS_MINIMUM_DEMI_TOUR = 3000;
const uint8_t TEMPS_ITERATION_AMBRE = 20;
const uint16_t TEMPS_AVANT_DEMI_TOUR = 1000;
const uint8_t PWM_DEMI_TOUR_GAUCHE = 60;
const uint8_t PWM_DEMI_TOUR_DROIT = 35;


// MODE MUR
const uint8_t DELAI_ENTRE_LECTURE = 15;
const uint8_t BORNE_PAS_UN_MUR = 50;
const uint8_t BORNE_INFERIEURE = 15;
const uint8_t DISTANCE_IDEALE = 20;
const uint8_t BORNE_SUPERIEURE = 25;
const uint8_t VITESSE_MODE_MUR = 25;
const uint8_t FACTEUR_CALCUL_VITESSE_MUR = 4;


// CAPTEUR DISTANCE
const float CONVERSION_CM_PO = 2.54;


// MODE LUMIERE
const uint8_t TEMPS_ENTRE_MESURES_LUMIERE_AMBIANTE = 1;
const uint8_t NUMERO_BROCHE_RESISTANCE_GAUCHE = PA0;
const uint8_t NUMERO_BROCHE_RESISTANCE_DROITE = PA1;
const uint8_t NOMBRE_MESURES_LUMIERE_AMBIANTE = 5;
const uint8_t TEMPS_ENTRE_AJUSTEMENTS_TRAJECTOIRE = 50;
const uint8_t INTENSITE_LUMIERE_MAXIMALE = 0xFF;
const uint8_t TOLERANCE_LUMIERE_AMBIANTE = 20; 
const uint8_t TOLERANCE_AVANCER_TOUT_DROIT = 10;
const uint8_t POURCENTAGE_PWM_PIVOTER = 50;
const uint8_t POURCENTAGE_PWM_MAXIMAL = 70;
const uint8_t POURCENTAGE_PWM_NORMAL = 30;
const uint8_t POURCENTAGE_PWM_MINIMAL = 10;
const uint8_t INTENSITE_LUMIERE_ACTIVATION = 220;


Robot::Robot() : moteur_(Moteur()),
                 capteurDistance_(CapteurDistance()),
                 del_(DelBicolore(&PORTA, PA2, PA3))
{
// code
}


uint8_t Robot::calculerMedianeDistanceCapteur(){

  uint8_t premiereLecture = calculerDistanceAuMurEnCm();
  _delay_ms(DELAI_ENTRE_LECTURE);

  uint8_t secondeLecture = calculerDistanceAuMurEnCm();
  _delay_ms(DELAI_ENTRE_LECTURE);

  uint8_t troisiemeLecture = calculerDistanceAuMurEnCm();
  _delay_ms(DELAI_ENTRE_LECTURE);

  if (premiereLecture <= secondeLecture){

    if (secondeLecture <= troisiemeLecture){

      return secondeLecture;
    
    } 
    else {

      if (premiereLecture < troisiemeLecture){

        return troisiemeLecture;
      
      } 
      else {

        return premiereLecture;
      
      }
    }
  } 
  else {

    if (premiereLecture <= troisiemeLecture){

      return premiereLecture;
    
    } 
    else {

      if (secondeLecture < troisiemeLecture) {
      
        return troisiemeLecture;
      
      } 
      else {
      
        return secondeLecture;
      
      }
    }
  }
}


int8_t Robot::calculerVitesseModeMur(uint8_t distanceAuMur){

  if (distanceAuMur <= DISTANCE_IDEALE){
  
    return VITESSE_MODE_MUR + FACTEUR_CALCUL_VITESSE_MUR * (DISTANCE_IDEALE - distanceAuMur);
  
  } 
  else {

    return VITESSE_MODE_MUR + FACTEUR_CALCUL_VITESSE_MUR * (distanceAuMur - DISTANCE_IDEALE);
  }
}


void Robot::suivreMur(){

  avancerToutDroit(VITESSE_MODE_MUR);

  uint8_t distanceAuMur = calculerMedianeDistanceCapteur();

  while (distanceAuMur <= BORNE_PAS_UN_MUR){

    if (distanceAuMur == DISTANCE_IDEALE){

      avancerToutDroit(VITESSE_MODE_MUR);
    
    } 
    else if (distanceAuMur < DISTANCE_IDEALE) {

      moteur_.ajusterPWM(VITESSE_MODE_MUR,
                         calculerVitesseModeMur(distanceAuMur));
    
    } 
    else {

      moteur_.ajusterPWM(calculerVitesseModeMur(distanceAuMur),
                         VITESSE_MODE_MUR);
    
    }

    distanceAuMur = calculerMedianeDistanceCapteur();
  }
  moteur_.stopperMoteur();
}


uint8_t Robot::calculerDistanceAuMurEnCm(){

  return capteurDistance_.calculerDistanceMur();

}


void Robot::suivreLumiere(){

  enum class EtatMoteurs{
    TOURNER_DROITE,
    TOURNER_GAUCHE,
    AVANCER_TOUT_DROIT,
    ARRETER,
    PIVOTER_DROITE,
    PIVOTER_GAUCHE
  };

  EtatMoteurs etatLumiere;

  while (!detecterPresenceMur()){

    _delay_ms(TEMPS_ENTRE_AJUSTEMENTS_TRAJECTOIRE);

    uint8_t intensiteLumiereDroite = can_.lecture8bits(NUMERO_BROCHE_RESISTANCE_DROITE);
    uint8_t intensiteLumiereGauche = can_.lecture8bits(NUMERO_BROCHE_RESISTANCE_GAUCHE) + ajustementPhotoresistanceGauche_;

    if (intensiteLumiereDroite < lumiereAmbiante_) {

      intensiteLumiereDroite = lumiereAmbiante_;
    
    }
    if (intensiteLumiereGauche < lumiereAmbiante_) {

      intensiteLumiereGauche = lumiereAmbiante_;

    }

    bool estLumiereAmbiante = intensiteLumiereDroite < lumiereAmbiante_ + TOLERANCE_LUMIERE_AMBIANTE &&
                              intensiteLumiereGauche < lumiereAmbiante_ + TOLERANCE_LUMIERE_AMBIANTE;
    bool estDansIntervalleDroite = intensiteLumiereDroite > intensiteLumiereGauche;
    bool estDansIntervalleAvancer, estDansIntervallePivoter;
    if (estDansIntervalleDroite) {

      estDansIntervalleAvancer = intensiteLumiereDroite - intensiteLumiereGauche < TOLERANCE_AVANCER_TOUT_DROIT;
      estDansIntervallePivoter = intensiteLumiereDroite >= lumiereAmbiante_ && intensiteLumiereGauche <= lumiereAmbiante_;
    
    } 
    else {

      estDansIntervalleAvancer = intensiteLumiereGauche - intensiteLumiereDroite < TOLERANCE_AVANCER_TOUT_DROIT;
      estDansIntervallePivoter = intensiteLumiereDroite <= lumiereAmbiante_ && intensiteLumiereGauche >= lumiereAmbiante_;
    
    }

    if (estLumiereAmbiante) {

      etatLumiere = EtatMoteurs::ARRETER;
    
    } 
    else if (estDansIntervalleAvancer) {

      etatLumiere = EtatMoteurs::AVANCER_TOUT_DROIT;
    
    } 
    else if (estDansIntervalleDroite && !estDansIntervallePivoter) {

      etatLumiere = EtatMoteurs::TOURNER_DROITE;
    
    } 
    else if (!estDansIntervalleDroite && !estDansIntervallePivoter) {
    
      etatLumiere = EtatMoteurs::TOURNER_GAUCHE;
    
    } 
    else if (estDansIntervalleDroite && estDansIntervallePivoter) {
    
      etatLumiere = EtatMoteurs::PIVOTER_DROITE;
    
    } 
    else {

      etatLumiere = EtatMoteurs::PIVOTER_GAUCHE;
    
    }

    uint8_t vitesseGauche, vitesseDroite;
    switch (etatLumiere){

      case EtatMoteurs::ARRETER:
        arreter();
        break;

      case EtatMoteurs::AVANCER_TOUT_DROIT:
        avancerToutDroit(calculerVitesse(intensiteLumiereDroite));
        break;

      case EtatMoteurs::TOURNER_DROITE:
        vitesseGauche = calculerVitesse(intensiteLumiereDroite);
        vitesseDroite = calculerVitesseTourner(intensiteLumiereDroite -
                                              intensiteLumiereGauche);
        avancerEnTournant(vitesseGauche,  
                          vitesseDroite);
        break;

      case EtatMoteurs::TOURNER_GAUCHE:
        vitesseDroite = calculerVitesse(intensiteLumiereGauche);
        vitesseGauche = calculerVitesseTourner(intensiteLumiereGauche -
                                               intensiteLumiereDroite);
        avancerEnTournant(vitesseGauche, 
                          vitesseDroite);
        break;

      case EtatMoteurs::PIVOTER_DROITE:
        pivoter(POURCENTAGE_PWM_PIVOTER, 
                true);
        break;

      case EtatMoteurs::PIVOTER_GAUCHE:
        pivoter(POURCENTAGE_PWM_PIVOTER, 
                false);
        break;
    }
  }
}


uint8_t Robot::calculerVitesse(uint8_t intensiteLumiere) {

    uint8_t intervalleVitesse = POURCENTAGE_PWM_MAXIMAL -
                                POURCENTAGE_PWM_NORMAL;

    uint8_t intervalleLumiere = INTENSITE_LUMIERE_MAXIMALE -
                                lumiereAmbiante_;

    return (intensiteLumiere - lumiereAmbiante_)
             * intervalleVitesse / intervalleLumiere + POURCENTAGE_PWM_NORMAL;
}


uint8_t Robot::calculerVitesseTourner(uint8_t differenceLumiereGaucheDroite){

  uint8_t intervalleVitesse = POURCENTAGE_PWM_NORMAL -
                              POURCENTAGE_PWM_MINIMAL;
  
  uint8_t differenceMaximale = INTENSITE_LUMIERE_MAXIMALE -
                               lumiereAmbiante_;
  
  return POURCENTAGE_PWM_NORMAL - differenceLumiereGaucheDroite * intervalleVitesse / differenceMaximale;
}


void Robot::calculerLumiereAmbiante(){

  uint8_t intensiteLumiereDroite = can_.lecture8bits(NUMERO_BROCHE_RESISTANCE_DROITE);
  uint8_t intensiteLumiereGauche = can_.lecture8bits(NUMERO_BROCHE_RESISTANCE_GAUCHE);

  lumiereAmbiante_ = intensiteLumiereDroite;
  ajustementPhotoresistanceGauche_ = intensiteLumiereDroite - intensiteLumiereGauche;
}


bool Robot::detecterLumiere(){

  return (can_.lecture8bits(NUMERO_BROCHE_RESISTANCE_DROITE) >= INTENSITE_LUMIERE_ACTIVATION) || (can_.lecture8bits(NUMERO_BROCHE_RESISTANCE_GAUCHE) >= INTENSITE_LUMIERE_ACTIVATION);

}


bool Robot::detecterPresenceMur(){

  return ((BORNE_INFERIEURE <= calculerDistanceAuMurEnCm()) && (calculerDistanceAuMurEnCm() <= BORNE_SUPERIEURE));

}


void Robot::faireDemiTour(){

  if (!aFaitDemiTour_){

    moteur_.stopperMoteur();
    moteur_.terminerEcritureMemoire();
    aFaitDemiTour_ = true;

    _delay_ms(TEMPS_AVANT_DEMI_TOUR);

    moteur_.changerMoteurActive(true, 
                                true);
    moteur_.avancer(true, 
                    true);
    moteur_.ajusterPWM(PWM_DEMI_TOUR_GAUCHE,
                       PWM_DEMI_TOUR_DROIT);

    uint16_t tempsEcoule = 0;
    
    while (!detecterPresenceMur() || tempsEcoule < TEMPS_MINIMUM_DEMI_TOUR){

      _delay_ms(TEMPS_ITERATION_AMBRE / 2);
      del_.allumer(DelBicolore::Couleur::ROUGE);
      
      _delay_ms(TEMPS_ITERATION_AMBRE / 2);
      del_.allumer(DelBicolore::Couleur::VERT);
      
      tempsEcoule += TEMPS_ITERATION_AMBRE;
    }

    del_.eteindre();
    moteur_.stopperMoteur();
  }
}


void Robot::activerEcritureMemoire(){

  moteur_.activerEcritureMemoire();

}


void Robot::avancerToutDroit(uint8_t pourcentagePWM){

  moteur_.changerMoteurActive(true, 
                              true);
  moteur_.avancer(true, 
                  true);
  moteur_.ajusterPWM(pourcentagePWM,
                     pourcentagePWM + AJUSTEMENT_PWM);
}


void Robot::avancerEnTournant(uint8_t pourcentageCoteGauche,
                              uint8_t pourcentageCoteDroit){

  moteur_.changerMoteurActive(true, 
                              true);
  moteur_.avancer(true, 
                  true);
  moteur_.ajusterPWM(pourcentageCoteGauche,
                     pourcentageCoteDroit);
}


void Robot::pivoter(uint8_t pourcentagePWM,
                    bool versLaDroite){

  moteur_.changerMoteurActive(true, 
                              true);
  moteur_.avancer(true, 
                  true);
  
  if (versLaDroite){

    moteur_.reculer(false, 
                    true);
    moteur_.ajusterPWM(pourcentagePWM, 
                       pourcentagePWM);
  
  } else {

    moteur_.reculer(true, 
                    false);
    moteur_.ajusterPWM(pourcentagePWM, 
                       pourcentagePWM);
  }
}


void Robot::arreter(){

  moteur_.stopperMoteur();

}


void Robot::clignotterDel(DelBicolore::Couleur couleur){

  uint8_t delaiUnClignottement = SECONDES_EN_MILLISECONDES / FREQUENCE_CLIGNOTTEMENT_DEL;
  for (uint8_t i = 0; i < FREQUENCE_CLIGNOTTEMENT_DEL * TEMPS_CLIGNOTTEMENT_DEL; i++){

    del_.allumer(couleur);
    _delay_ms(delaiUnClignottement / 2);
    
    del_.eteindre();
    _delay_ms(delaiUnClignottement / 2);
  
  }
}


void Robot::finirParcours(){

  del_.allumer(DelBicolore::Couleur::ROUGE);
  if (!aFaitDemiTour_)
    moteur_.terminerEcritureMemoire();
  
  while (true)
    del_.allumer(DelBicolore::Couleur::VERT);
}

