/*************************************************************************
                           ApacheLogData  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <ApacheLogData> (fichier ApacheLogData.h) ----------------
#if ! defined ( APACHE_LOG_DATA_H )
#define APACHE_LOG_DATA_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <ApacheLogData>
//
//
//------------------------------------------------------------------------

class ApacheLogData
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

//------------------------------------------------------ Getters
    const std::string& GetIpAddress() const ;
    // Mode d'emploi :
    //
    // Contrat :
    //

    const std::string& GetUserLogname() const ;
    // Mode d'emploi :
    //
    // Contrat :
    //

    const std::string& GetUserAuthName() const ;
    // Mode d'emploi :
    //
    // Contrat :
    //

    const std::string& GetDate() const ;
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    const std::string& GetRequest() const ;
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    int GetStatusCode() const ;
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    int GetDataSize() const ;
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    const std::string& GetReferer() const ;
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    const std::string& GetNavigator() const ;
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------ Setters
    void SetIpAddress(const std::string& ip);
    // Mode d'emploi :
    //
    // Contrat :
    //

    void SetUserLogname(const std::string& name) ;
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    void SetUserAuthName(const std::string& name) ;
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    void SetDateTime(const std::string& dt) ;
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    void SetRequest(const std::string& req) ;
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    void SetStatusCode(int code) ;
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    void SetDataSize(int size) ;
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    void SetReferer(const std::string& ref) ;
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    void SetNavigator(const std::string& agent) ;
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------- Surcharge d'opérateurs
    ApacheLogData & operator = ( const ApacheLogData & unApacheLogData ); 
    // Mode d'emploi :
    //
    // Contrat :
    //

  
    friend std::ostream & operator << (std::ostream & os, const ApacheLogData & logData);
    // Mode d'emploi :
    //
    // Contrat :
    //
    
//-------------------------------------------- Constructeurs - destructeur
    ApacheLogData ( const ApacheLogData & unApacheLogData );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    ApacheLogData ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~ApacheLogData ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    std::string ipAddress;   // IP address of the client
    std::string userLogname; // User Logname   
    std::string userAuthName;// Authenticated Username
    std::string date;        // Date and time of the request
    std::string request;     // HTTP request (method and resource)
    int statusCode;          // HTTP status code
    int dataSize;            // Data size in bytes
    std::string referer;     // Referer URL
    std::string navigator;   // navigator identification
};

//-------------------------------- Autres définitions dépendantes de <ApacheLogData>

#endif // APACHE_LOG_DATA_H

