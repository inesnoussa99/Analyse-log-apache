/*************************************************************************
                           ApacheLogReader  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <ApacheLogReader> (fichier ApacheLogReader.h) ----------------
#if !defined(APACHE_LOG_READER_H)
#define APACHE_LOG_READER_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <fstream>
#include "ApacheLogData.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <ApacheLogReader>
//
// Ouvre un fichier de logs Apache, lit les lignes et extrait les données.
//------------------------------------------------------------------------

class ApacheLogReader
{
    //----------------------------------------------------------------- PUBLIC

public:
    //----------------------------------------------------- Méthodes publiques
    // Ouvre un fichier de logs
    bool OpenFile(const std::string &filename);
    // Mode d'emploi :
    //
    // Contrat :
    //
    // Ferme le fichier de logs
    bool CloseFile();
    // Mode d'emploi :
    //
    // Contrat :
    //
    // Vérifie si la fin du fichier est atteinte
    bool EndOfFile();
    // Mode d'emploi :
    //
    // Contrat :
    //
    // Réinitialise la lecture du fichier
    bool ResetReading();
    // Mode d'emploi :
    //
    // Contrat :
    //
    // Lit une ligne du fichier et retourne les données sous forme d'objet
    ApacheLogData ReadLine();
    // Mode d'emploi :
    //
    // Contrat :
    //

    //------------------------------------------------- Surcharge d'opérateurs

    // ApacheLogReader & operator = ( const ApacheLogReader & unApacheLogReader ); // Inutile ?

    //-------------------------------------------- Constructeurs - destructeur

    // ApacheLogReader ( const ApacheLogReader & unApacheLogReader ); // Inutile ?
    // Constructeur par défaut
    ApacheLogReader();
    // Mode d'emploi :
    //
    // Contrat :
    //
    // Destructeur
    virtual ~ApacheLogReader();
    // Mode d'emploi :
    //
    // Contrat :
    //

    //------------------------------------------------------------------ PRIVE
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    //----------------------------------------------------- Attributs protégés
    std::ifstream file; // Fichier en cours de lecture
};

//-------------------------------- Autres définitions dépendantes de <ApacheLogReader>

#endif // APACHE_LOG_READER_H
