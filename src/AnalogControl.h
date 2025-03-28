/*************************************************************************
                           AnalogControl  -  Classe "directrice"
                           Elle récupère la ligne de commande, et execute les instructions
                           et stocke les données.
                             -------------------
    début                : 2025
    copyright            : (C) 2025 par NAJI Adam
    e-mail               : adam-yassine.naji@insa-lyon.fr 

*************************************************************************/

//---------- Interface de la classe <AnalogControl> (fichier AnalogControl.h) ----------------
#if ! defined ( ANALOG_CONTROL_H )
#define ANALOG_CONTROL_H

//--------------------------------------------------- Interfaces utilisées
#include <map>
#include <string>
#include "ApacheLogReader.h"
//------------------------------------------------------------- Constantes

enum AnalogReturnCode {
    
    AC_SUCCESS, // 0

    AC_INVALID_ARGUMENT_COUNT, // 1

    AC_MISSING_ARGUMENT, // 2

    AC_INVALID_TIME_VALUE, // 3

    AC_INVALID_NUMERIC_VALUE, // 4

    AC_UNKNOWN_OPTION, // 5

    AC_TOO_MANY_ARGUMENTS, // 6

    AC_MISSING_LOG_FILE, // 7

    AC_MISSING_CONFIG_FILE // 8

};

//------------------------------------------------------------------ Types

typedef std::map<std::string,std::pair<std::map<std::string,int>,int>> logsData;


//------------------------------------------------------------------------
// Rôle de la classe <AnalogControl>
//  
//  Récupérer la commande entrée par l'utilisateur, 
//  Utiliser la classe ApacheLogReader pour récuperer les données utiles,
//  Utiliser la classe AnalogAnalyse pour calculer les stats et générer les fichiers dot
//------------------------------------------------------------------------

class AnalogControl
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    AnalogReturnCode Run (const int argc, char** argv);
    // Mode d'emploi :
    //
    // Contrat :
    //


//------------------------------------------------- Surcharge d'opérateurs

    // AnalogControl & operator = ( const AnalogControl & unAnalogControl ); 
    
//-------------------------------------------- Constructeurs - destructeur
    
    // AnalogControl ( const AnalogControl & unAnalogControl ); 
    

    AnalogControl ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~AnalogControl ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

    AnalogReturnCode ReadFile(const std::string & filename);
    // Mode d'emploi :
    //
    // Contrat :
    //
//----------------------------------------------------- Attributs protégés
    logsData data;

    bool option_g; // create dot file
    std::string dotFileName;
    bool option_e; // exclude image, css and js files
    bool option_t; // one-hour interval
    int hour;
    bool option_d; // use custom domain name
    std::string domain;
    bool option_n;
    int n;

};

//-------------------------------- Autres définitions dépendantes de <AnalogControl>

#endif // ANALOG_CONTROL_H
