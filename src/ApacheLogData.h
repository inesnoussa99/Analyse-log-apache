/*************************************************************************
                           ApacheLogData  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <ApacheLogData> (fichier ApacheLogData.h) ----------------
#if !defined(APACHE_LOG_DATA_H)
#define APACHE_LOG_DATA_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <ApacheLogData>
//
// Stocke et manipule les données d'une ligne de log Apache.
//------------------------------------------------------------------------

class ApacheLogData
{
    //----------------------------------------------------------------- PUBLIC

public:
    //----------------------------------------------------- Méthodes publiques

    //------------------------------------------------------ Getters
    // Retourne l'adresse IP du client
    const std::string &GetIpAddress() const;
    // Mode d'emploi :
    //
    // Contrat :
    //
    // Retourne le nom d'utilisateur logué
    const std::string &GetUserLogname() const;
    // Mode d'emploi :
    //
    // Contrat :
    //
    // Retourne le nom d'utilisateur authentifié
    const std::string &GetUserAuthName() const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    // Retourne la date et l'heure de la requête

    const std::string &GetDate() const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    // Retourne la requête HTTP (méthode et ressource demandée)

    const std::string &GetRequest() const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    // Retourne le code de statut HTTP

    int GetStatusCode() const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    // Retourne la taille des données transférées

    int GetDataSize() const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    // Retourne l'URL du référent (site d'origine)

    const std::string &GetReferer() const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    // Retourne l'identification du navigateur utilisé

    const std::string &GetNavigator() const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    //------------------------------------------------------ Setters

    // Définit l'adresse IP

    void SetIpAddress(const std::string &ip);
    // Mode d'emploi :
    //
    // Contrat :
    //
    // Définit le nom d'utilisateur logué
    void SetUserLogname(const std::string &name);
    // Mode d'emploi :
    //
    // Contrat :
    //
    // Définit le nom d'utilisateur authentifié
    void SetUserAuthName(const std::string &name);
    // Mode d'emploi :
    //
    // Contrat :
    //
    // Définit la date et l'heure de la requête
    void SetDateTime(const std::string &dt);
    // Mode d'emploi :
    //
    // Contrat :
    //
    // Définit la requête HTTP
    void SetRequest(const std::string &req);
    // Mode d'emploi :
    //
    // Contrat :
    //
    // Définit le code de statut HTTP
    void SetStatusCode(int code);
    // Mode d'emploi :
    //
    // Contrat :
    //
    // Définit la taille des données transférées
    void SetDataSize(int size);
    // Mode d'emploi :
    //
    // Contrat :
    //
    // Définit l'URL du référent
    void SetReferer(const std::string &ref);
    // Mode d'emploi :
    //
    // Contrat :
    //
    // Définit l'identification du navigateur
    void SetNavigator(const std::string &agent);
    // Mode d'emploi :
    //
    // Contrat :
    //

    //------------------------------------------------- Surcharge d'opérateurs
    // Opérateur d'affectation
    ApacheLogData &operator=(const ApacheLogData &unApacheLogData);
    // Mode d'emploi :
    //
    // Contrat :
    //
    // Surcharge de l'opérateur << pour afficher un log
    friend std::ostream &operator<<(std::ostream &os, const ApacheLogData &logData);
    // Mode d'emploi :
    //
    // Contrat :
    //

    //-------------------------------------------- Constructeurs - destructeur
    // Constructeur par copie

    ApacheLogData(const ApacheLogData &unApacheLogData);
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //
    // Constructeur par défaut
    ApacheLogData();
    // Mode d'emploi :
    //
    // Contrat :
    //
    // Destructeur
    virtual ~ApacheLogData();
    // Mode d'emploi :
    //
    // Contrat :
    //

    //------------------------------------------------------------------ PRIVE

protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
    std::string ipAddress;    // IP address
    std::string userLogname;  // User Logname
    std::string userAuthName; // Authenticated Username
    std::string date;         // Date and time of the request
    std::string request;      // HTTP request (method and resource)
    int statusCode;           // HTTP status code
    int dataSize;             // Data size in bytes
    std::string referer;      // Referer URL
    std::string navigator;    // Navigator identification
};

//-------------------------------- Autres définitions dépendantes de <ApacheLogData>

#endif // APACHE_LOG_DATA_H
