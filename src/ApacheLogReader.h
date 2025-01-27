/*************************************************************************
                           ApacheLogReader  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <ApacheLogReader> (fichier ApacheLogReader.h) ----------------
#if ! defined ( APACHE_LOG_READER_H )
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
//
//------------------------------------------------------------------------

class ApacheLogReader
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    bool OpenFile(const std::string& filename);
    // Mode d'emploi :
    //
    // Contrat :
    //

    bool CloseFile();
    // Mode d'emploi :
    //
    // Contrat :
    //

    bool EndOfFile();
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    bool ResetReading();
    // Mode d'emploi :
    //
    // Contrat :
    //

    ApacheLogData ReadLine();
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------- Surcharge d'opérateurs

    // ApacheLogReader & operator = ( const ApacheLogReader & unApacheLogReader ); // Inutile ?

//-------------------------------------------- Constructeurs - destructeur

    // ApacheLogReader ( const ApacheLogReader & unApacheLogReader ); // Inutile ?

    ApacheLogReader ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~ApacheLogReader ( );
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
    std::ifstream file;
};

//-------------------------------- Autres définitions dépendantes de <ApacheLogReader>

#endif // APACHE_LOG_READER_H

