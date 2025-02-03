/*************************************************************************
                           ApacheLogData  -  
                           Stockage des infos d'une ligne de log Apache
                             -------------------
    début                : 2025
    copyright            : (C) 2025 par CHEBBI Ines
                           ines.chebbi@insa-lyon.fr
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
enum ApacheLogReaderReturnCode {

    ALR_SUCCESS, // 0

    ALR_FILE_ALREADY_OPEN, // 1

    ALR_FILE_NOT_FOUND, // 2

    ALR_FILE_NOT_OPEN, // 3

    ALR_FILE_CLOSE_ERROR // 4

};
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

    ApacheLogReaderReturnCode OpenFile(const std::string& filename);
    // Mode d'emploi :
    //
    // Contrat :
    //

    ApacheLogReaderReturnCode CloseFile();
    // Mode d'emploi :
    //
    // Contrat :
    //

    bool EndOfFile();
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    ApacheLogReaderReturnCode ResetReading();
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

    // ApacheLogReader & operator = ( const ApacheLogReader & unApacheLogReader ); 

//-------------------------------------------- Constructeurs - destructeur

    // ApacheLogReader ( const ApacheLogReader & unApacheLogReader ); 

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

