/*
 * Projet Final - CommunicationnRS232.cpp
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
 *  Ce programme contient la définition des méthodes de la classe 
 *  CommunicationRS232, on voit les différentes méthodes utilisée
 *  dans le fichier CommunicationRS232.h.
 *  Cette classe permet de transmettre des messages du robot a l'ordinateur.
 * 
 * IDENTIFICATIONS MATÉRIELLES :
 *  D0 en entrée 
 *  D1 en sortie
*/


#include "CommunicationRS232.h"


CommunicationRS232::CommunicationRS232() {

    UBRR0H = 0;
    UBRR0L = 0xCF;
    UCSR0A |= (1 << RXC0)   | (1 << TXC0);
    UCSR0B |= (1 << RXEN0)  | (1 << TXEN0);
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);

}


uint8_t CommunicationRS232::recevoirUART() {

    while (!(UCSR0A & (1<<RXC0)));
    return UDR0;

}


void CommunicationRS232::transmettreUART(const char* donnees) {

    uint8_t numeroCaractere = 0;
    char    caractere = donnees[numeroCaractere];

    while (caractere != '\0') {

        transmettreUART(donnees[numeroCaractere]);
        numeroCaractere++;
        caractere = donnees[numeroCaractere];

    }

    transmettreUART('\n');
}


void CommunicationRS232::transmettreUART(uint8_t donnee) {

    while (!(UCSR0A & (1<<UDRE0)));
    UDR0 = donnee;
    
}

