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
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
typedef std::map<std::string,std::map<std::map<std::string,int>,int>> logsData;

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

    int Run (const int argc, const char** argv);
    // Mode d'emploi :
    //
    // Contrat :
    //

    void ReadFile(const std::string & filename);
    // Mode d'emploi :
    //
    // Contrat :
    //
//------------------------------------------------- Surcharge d'opérateurs

    // AnalogControl & operator = ( const AnalogControl & unAnalogControl ); // Inutile ?
    
//-------------------------------------------- Constructeurs - destructeur
    
    // AnalogControl ( const AnalogControl & unAnalogControl ); // Inutile ?
    

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

//----------------------------------------------------- Attributs protégés
    logsData data;

    bool option_g; // create dot file
    std::string dotFileName;
    bool option_e; // exclude image, css and js files
    bool option_t; // one-hour interval
    int hour;
    bool option_d; // use custom domain name
    std::string customDomain;


};

//-------------------------------- Autres définitions dépendantes de <AnalogControl>

#endif // ANALOG_CONTROL_H
