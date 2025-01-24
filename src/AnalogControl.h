/*************************************************************************
                           AnalogControl  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <AnalogControl> (fichier AnalogControl.h) ----------------
#if ! defined ( ANALOG_CONTROL_H )
#define ANALOG_CONTROL_H

//--------------------------------------------------- Interfaces utilisées
#include <map>
#include <string>
#include "ApacheLogReader.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

// typedef std::map<std::string,std::map<std::map<std::string,int>,int>> logsData;

typedef std::map<std::string,std::pair<std::map<std::string,int>,int>> logsData;

//------------------------------------------------------------------------
// Rôle de la classe <AnalogControl>
//
//
//------------------------------------------------------------------------

class AnalogControl
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    int Run (const int argc, char** argv);
    // Mode d'emploi :
    //
    // Contrat :
    //

    int ReadFile(const std::string & filename);
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
    bool endsWith(const std::string& str, const std::string& suffix);
    // Mode d'emploi :
    //
    // Contrat :
    //

    std::string getDomainFromReferer(const std::string& referer);
    // Mode d'emploi :
    //
    // Contrat :
    //

    std::string getDocumentFromReferer(const std::string& referer);
    // Mode d'emploi :
    //
    // Contrat :
    //

    std::string getTargetFromRequest(const std::string& request);
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


};

//-------------------------------- Autres définitions dépendantes de <AnalogControl>

#endif // ANALOG_CONTROL_H
