/*
 * Projet Final - CommunicationRS232.h
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
 *  Ce programme contient la déclaration de la classe CommunicationRS232, on voit les
 *  différentes méthodes utilisée dans le fichier CommunicationRS232.cpp.
 *  Cette classe permet de transmettre des messages du robot a l'ordinateur.
 * 
 * IDENTIFICATIONS MATÉRIELLES :
 *  D0 en entrée 
 *  D1 en sortie
*/


#ifndef COMM_RS232_H
#define COMM_RS232_H
#define F_CPU 8000000UL


#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>


class CommunicationRS232{

public:

    CommunicationRS232();

    uint8_t recevoirUART();
    void transmettreUART(uint8_t donnee);
    void transmettreUART(const char* donnees);

};


#endif