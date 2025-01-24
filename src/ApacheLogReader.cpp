/*************************************************************************
                           ApacheLogReader  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <ApacheLogReader> (fichier ApacheLogReader.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <regex>
//------------------------------------------------------ Include personnel
#include "./ApacheLogReader.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

bool ApacheLogReader::OpenFile (const std::string& filename)
// Algorithme :
//
{
    if (file.is_open()) {
        std::cerr << "File is already open." << std::endl;
        return false;
    }

    file.open(filename, std::ios::in);

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return false;
    }

    return true;
} //----- Fin de OpenFile


bool ApacheLogReader::CloseFile()
// Algorithme :
//
{
    if (!file.is_open()) {
        std::cerr << "No file is currently open." << std::endl;
        return false;
    }

    file.close();

    if (file.is_open()) {
        std::cerr << "Failed to close the file." << std::endl;
        return false;
    }

    return true;
} //----- Fin de CloseFile


bool ApacheLogReader::EndOfFile()
// Algorithme :
//
{
    if (!file.is_open()) {
        std::cerr << "No file is currently open to check EOF." << std::endl;
        return true; // Considérer qu'on est "à la fin" s'il n'y a pas de fichier.
    }

    return file.eof();
} //----- Fin de EndOfFile


bool ApacheLogReader::ResetReading()
// Algorithme :
//
{
    if (!file.is_open()) {
        std::cerr << "No file is currently open to reset." << std::endl;
        return false;
    }

    file.clear(); // Efface les flags d'erreur potentiels (EOF, etc.)
    file.seekg(0, std::ios::beg);
    return true;
} //----- Fin de ResetReading

ApacheLogData ApacheLogReader::ReadLine()
// Algorithme :
//
{
    ApacheLogData logData;

    if (!file.is_open() || file.eof()) {
        std::cerr << "Cannot read from file. Either no file is open or end of file reached." << std::endl;
        return logData; // Retourne un objet vide en cas d'erreur
    }

    std::string logLine;
    std::getline(file, logLine);

    if (logLine.empty()) {
        return logData; // Retourne un objet vide si la ligne est vide
    }

    size_t startPos = 0;
    size_t endPos = 0;

    endPos = logLine.find(' ', startPos);
    logData.SetIpAddress(logLine.substr(startPos, endPos - startPos));

    // Sauter l'espace, puis récupérer le User Logname et User Auth Name
    startPos = endPos + 1;
    endPos = logLine.find(' ', startPos);
    logData.SetUserLogname(logLine.substr(startPos, endPos - startPos));

    startPos = endPos + 1;
    endPos = logLine.find(' ', startPos);
    logData.SetUserAuthName(logLine.substr(startPos, endPos - startPos));

    // Récupération de la date entre crochets
    startPos = logLine.find('[', endPos) + 1; // juste après '['
    endPos = logLine.find(']', startPos);
    logData.SetDateTime(logLine.substr(startPos, endPos - startPos));

    // Récupérer la requête HTTP (tout entre guillemets après la date)
    startPos = logLine.find('"', endPos) + 1; // juste après le premier guillemet
    endPos = logLine.find('"', startPos);
    logData.SetRequest(logLine.substr(startPos, endPos - startPos));

    // Récupérer le code de statut (après la requête)
    startPos = endPos + 2; // après les guillemets et l'espace
    endPos = logLine.find(' ', startPos);
    logData.SetStatusCode(std::stoi(logLine.substr(startPos, endPos - startPos)));

    // Récupérer la taille des données
    startPos = endPos + 1;
    endPos = logLine.find(' ', startPos);
    logData.SetDataSize(std::stoi(logLine.substr(startPos, endPos - startPos)));

    // Récupérer le référent (tout entre guillemets)
    startPos = logLine.find('"', endPos) + 1; // juste après le guillemet
    endPos = logLine.find('"', startPos);
    logData.SetReferer(logLine.substr(startPos, endPos - startPos));

    // Récupérer le navigateur (tout entre guillemets)
    startPos = logLine.find('"', endPos) + 1;
    logData.SetNavigator(logLine.substr(startPos));

    return logData;
} //----- Fin de ReadLine


//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

ApacheLogReader::ApacheLogReader ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <ApacheLogReader>" << endl;
#endif
} //----- Fin de ApacheLogReader


ApacheLogReader::~ApacheLogReader ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <ApacheLogReader>" << endl;
#endif
    if (file.is_open()) {
        file.close();
    }
} //----- Fin de ~ApacheLogReader


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

