/*************************************************************************
                           ApacheLogData  -  
                           Stockage des infos d'une ligne de log Apache
                             -------------------
    début                : 2025
    copyright            : (C) 2025 par CHEBBI Ines
                           ines.chebbi@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <ApacheLogData> (fichier ApacheLogData.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "./ApacheLogData.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

string ApacheLogData::GetIpAddress() const
// Algorithme :
//
{
    return ipAddress;
} //----- Fin de Méthode

string ApacheLogData::GetUserLogname() const
// Algorithme :
//
{
    return userLogname;
} //----- Fin de Méthode

string ApacheLogData::GetUserAuthName() const
// Algorithme :
//
{
    return userAuthName;
} //----- Fin de Méthode

string ApacheLogData::GetDate() const
// Algorithme :
//
{
    return date;
} //----- Fin de Méthode

string ApacheLogData::GetRequest() const
// Algorithme :
//
{
    return request;
} //----- Fin de Méthode

int ApacheLogData::GetStatusCode() const
// Algorithme :
//
{
    return statusCode;
} //----- Fin de Méthode

int ApacheLogData::GetDataSize() const
// Algorithme :
//
{
    return dataSize;
} //----- Fin de Méthode

string ApacheLogData::GetReferer() const
// Algorithme :
//
{
    return referer;
} //----- Fin de Méthode

string ApacheLogData::GetNavigator() const
// Algorithme :
//
{
    return navigator;
} //----- Fin de Méthode


string ApacheLogData::GetTargetFromRequest() const
// Algorithme :
//
{
    size_t startPos = request.find(" ") + 1; // Après le premier espace, pour l'URL
    
    // Trouver la position du dernier espace avant la version HTTP
    size_t endPos = request.rfind(" ");
    
    // Si les positions sont valides, on extrait l'URL
    if (startPos != string::npos && endPos != string::npos && startPos < endPos) {
        return request.substr(startPos, endPos - startPos); // Extrait l'URL
    }
    
    // Si les positions ne sont pas valides, retourner une chaîne vide
    return "-";
} //----- Fin de Méthode

string ApacheLogData::GetMethodFromRequest() const
// Algorithme :
//
{
    size_t endPos = request.find(" "); // Avant le premier espace

    if (endPos != string::npos && 0 < endPos) {
        return request.substr(0, endPos); // Extrait la Methode
    }

    // Si les positions ne sont pas valides, retourner une chaîne vide
    return "-";
} //----- Fin de Méthode

string ApacheLogData::GetFileExtension() const
// Algorithme :
//
{
    // Trouver la position du dernier '/'
    size_t lastSlash = GetTargetFromRequest().find_last_of("/\\");
    
    // Extraire le nom du fichier (sans le chemin)
    string filename = (lastSlash != string::npos) ? GetTargetFromRequest().substr(lastSlash + 1) : GetTargetFromRequest();
    
    // Supprimer la partie après un éventuel point-virgule ou point d'interrogation (paramètres d'URL)
    size_t delimiterPos = filename.find_first_of(";?");
    if (delimiterPos != string::npos) {
        filename = filename.substr(0, delimiterPos);
    }

    // Trouver la position du dernier point dans le nom du fichier
    size_t lastDot = filename.find_last_of('.');
    if (lastDot == string::npos || lastDot == 0) {
        return ""; // Aucune extension trouvée ou nom de fichier commençant par un point
    }

    // Extraire et retourner l'extension
    return filename.substr(lastDot + 1);
} //----- Fin de Méthode

bool ApacheLogData::TargetIsDirectory() const
{
    return !GetTargetFromRequest().empty() && (GetTargetFromRequest().back() == '/' || GetTargetFromRequest().back() == '\\');
}

string ApacheLogData::GetDocumentFromReferer() const
// Algorithme :
//
{
    // Trouver la position de "http://", ou "https://"
    size_t startPos = referer.find("://");

    // Si "://" est trouvé, décaler le curseur pour sauter "://"
    if (startPos != string::npos) {
        startPos += 3; // "://"
    } else {
        // Si "://" n'est pas trouvé, l'URL est mal formée
        return "-";
    }

    // Trouver la position du premier "/" après le nom de domaine
    size_t slashPos = referer.find("/", startPos);

    // Si "/" est trouvé, extraire la partie après le "/"
    if (slashPos != string::npos) 
    {
        return referer.substr(slashPos);  
    }

    // Si "/" n'est pas trouvé, il n'y a pas de chemin
    return "-";
} //----- Fin de Méthode

string ApacheLogData::GetDomainFromReferer() const 
// Algorithme :
//
{
    // Trouver la position après "http://" ou "https://"
    string::size_type startPos = referer.find("://");
    if (startPos == string::npos) {
        return "-"; // Pas un URL valide
    }
    startPos += 3; // Sauter "://"

    // Trouver la fin du domaine (soit le premier '/' ou la fin de la chaîne)
    string::size_type endPos = referer.find('/', startPos);
    if (endPos == string::npos) {
        endPos = referer.length(); // Si aucun '/' n'est trouvé
    }

    // Extraire le domaine
    return referer.substr(startPos, endPos - startPos);
} //----- Fin de Méthode


void ApacheLogData::SetIpAddress(const string& ip)
{
    ipAddress = ip;
} //----- Fin de Méthode

void ApacheLogData::SetUserLogname(const string& name)
{
    userLogname = name;
} //----- Fin de Méthode

void ApacheLogData::SetUserAuthName(const string& name)
{
    userAuthName = name;
} //----- Fin de Méthode

void ApacheLogData::SetDateTime(const string& dt)
{
    date = dt;
} //----- Fin de Méthode

void ApacheLogData::SetRequest(const string& req)
{
    request = req;
} //----- Fin de Méthode

void ApacheLogData::SetStatusCode(int code)
{
    statusCode = code;
} //----- Fin de Méthode

void ApacheLogData::SetDataSize(int size)
{
    dataSize = size;
} //----- Fin de Méthode

void ApacheLogData::SetReferer(const string& ref)
{
    referer = ref;
} //----- Fin de Méthode

void ApacheLogData::SetNavigator(const string& agent)
{
    navigator = agent;
} //----- Fin de Méthode


//------------------------------------------------- Surcharge d'opérateurs
ApacheLogData & ApacheLogData::operator = ( const ApacheLogData & unApacheLogData )
// Algorithme :
//
{
    if (this != &unApacheLogData) {
        ipAddress = unApacheLogData.ipAddress;
        userLogname = unApacheLogData.userLogname;
        userAuthName = unApacheLogData.userAuthName;
        date = unApacheLogData.date;
        request = unApacheLogData.request;
        statusCode = unApacheLogData.statusCode;
        dataSize = unApacheLogData.dataSize;
        referer = unApacheLogData.referer;
        navigator = unApacheLogData.navigator;
    }
    return *this;
} //----- Fin de operator =

ostream & operator << (ostream & os, const ApacheLogData & logData)
// Algorithme :
//
{
    os << "IP Address: " << logData.ipAddress << "\n"
       << "User Logname: " << logData.userLogname << "\n"
       << "Authenticated Username: " << logData.userAuthName << "\n"
       << "Date: " << logData.date << "\n"
       << "Request: " << logData.request << "\n"
       << "Status Code: " << logData.statusCode << "\n"
       << "Data Size: " << logData.dataSize << " bytes\n"
       << "Referer: " << logData.referer << "\n"
       << "Navigator: " << logData.navigator << "\n";
    return os;
} //----- Fin de operator <<

//-------------------------------------------- Constructeurs - destructeur
ApacheLogData::ApacheLogData ( const ApacheLogData & unApacheLogData )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <ApacheLogData>" << endl;
#endif
    if (this != &unApacheLogData) {
        ipAddress = unApacheLogData.ipAddress;
        userLogname = unApacheLogData.userLogname;
        userAuthName = unApacheLogData.userAuthName;
        date = unApacheLogData.date;
        request = unApacheLogData.request;
        statusCode = unApacheLogData.statusCode;
        dataSize = unApacheLogData.dataSize;
        referer = unApacheLogData.referer;
        navigator = unApacheLogData.navigator;
    }
} //----- Fin de ApacheLogData (constructeur de copie)


ApacheLogData::ApacheLogData ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <ApacheLogData>" << endl;
#endif
} //----- Fin de ApacheLogData


ApacheLogData::~ApacheLogData ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <ApacheLogData>" << endl;
#endif
} //----- Fin de ~ApacheLogData


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

