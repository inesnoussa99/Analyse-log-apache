/*************************************************************************
                           ApacheLogData  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
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
// type ApacheLogData::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

const std::string& ApacheLogData::GetIpAddress() const
// Algorithme :
//
{
    return ipAddress;
} //----- Fin de Méthode

const std::string& ApacheLogData::GetUserLogname() const
// Algorithme :
//
{
    return userLogname;
} //----- Fin de Méthode

const std::string& ApacheLogData::GetUserAuthName() const
// Algorithme :
//
{
    return userAuthName;
} //----- Fin de Méthode

const std::string& ApacheLogData::GetDate() const
// Algorithme :
//
{
    return date;
} //----- Fin de Méthode

const std::string& ApacheLogData::GetRequest() const
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

const std::string& ApacheLogData::GetReferer() const
// Algorithme :
//
{
    return referer;
} //----- Fin de Méthode

const std::string& ApacheLogData::GetNavigator() const
// Algorithme :
//
{
    return navigator;
} //----- Fin de Méthode

//------------------------------------------------------ Setters
void ApacheLogData::SetIpAddress(const std::string& ip)
{
    ipAddress = ip;
} //----- Fin de Méthode

void ApacheLogData::SetUserLogname(const std::string& name)
{
    userLogname = name;
} //----- Fin de Méthode

void ApacheLogData::SetUserAuthName(const std::string& name)
{
    userAuthName = name;
} //----- Fin de Méthode

void ApacheLogData::SetDateTime(const std::string& dt)
{
    date = dt;
} //----- Fin de Méthode

void ApacheLogData::SetRequest(const std::string& req)
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

void ApacheLogData::SetReferer(const std::string& ref)
{
    referer = ref;
} //----- Fin de Méthode

void ApacheLogData::SetNavigator(const std::string& agent)
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

std::ostream & operator << (std::ostream & os, const ApacheLogData & logData)
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

