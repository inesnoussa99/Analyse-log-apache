/*************************************************************************
                           ApacheLogData  -  
                           Stockage des infos d'une ligne de log Apache
                             -------------------
    début                : 2025
    copyright            : (C) 2025 par CHEBBI Ines
                           ines.chebbi@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <ApacheLogReader> (fichier ApacheLogReader.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
//------------------------------------------------------ Include personnel
#include "./ApacheLogReader.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

ApacheLogReaderReturnCode ApacheLogReader::OpenFile (const std::string& filename)
// Algorithme :
//
{
    if (file.is_open()) {
        std::cerr << "File is already open." << std::endl;
        return ApacheLogReaderReturnCode::ALR_FILE_ALREADY_OPEN;
    }

    file.open(filename, std::ios::in);

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return ApacheLogReaderReturnCode::ALR_FILE_NOT_FOUND;
    }

    return ApacheLogReaderReturnCode::ALR_SUCCESS;
} //----- Fin de OpenFile


ApacheLogReaderReturnCode ApacheLogReader::CloseFile()
// Algorithme :
//
{
    if (!file.is_open()) {
        std::cerr << "No file is currently open." << std::endl;
        return ApacheLogReaderReturnCode::ALR_FILE_NOT_OPEN;
    }

    file.close();

    if (file.is_open()) {
        std::cerr << "Failed to close the file." << std::endl;
        return ApacheLogReaderReturnCode::ALR_FILE_CLOSE_ERROR;
    }

    return ApacheLogReaderReturnCode::ALR_SUCCESS;
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


ApacheLogReaderReturnCode ApacheLogReader::ResetReading()
// Algorithme :
//
{
    if (!file.is_open()) {
        std::cerr << "No file is currently open to reset." << std::endl;
        return ApacheLogReaderReturnCode::ALR_FILE_NOT_OPEN;
    }

    file.clear(); // Efface les flags d'erreur potentiels (EOF, etc.)
    file.seekg(0, std::ios::beg);
    return ApacheLogReaderReturnCode::ALR_SUCCESS;
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
    try {
        logData.SetStatusCode(std::stoi(logLine.substr(startPos, endPos - startPos)));
    } catch (const std::invalid_argument& e) {
        logData.SetDataSize(520);               // 520 = unkown error
    } catch (const std::out_of_range& e) {
        logData.SetDataSize(520);
    }

    // Récupérer la taille des données
    startPos = endPos + 1;
    endPos = logLine.find(' ', startPos);
  
    try {
        logData.SetDataSize(std::stoi(logLine.substr(startPos, endPos - startPos)));
    } catch (const std::invalid_argument& e) {
        logData.SetDataSize(0);
    } catch (const std::out_of_range& e) {
        logData.SetDataSize(0);
    }

    // Récupérer le référent (tout entre guillemets)
    startPos = logLine.find('"', endPos) + 1; // juste après le guillemet
    endPos = logLine.find('"', startPos);
    logData.SetReferer(logLine.substr(startPos, endPos - startPos));

    // Récupérer le navigateur (tout entre guillemets)
    startPos = logLine.find('"', endPos) + 1;
    logData.SetNavigator(logLine.substr(startPos));

    // cout<<"READER : log readed = \r\n"<<logData<<endl;
    
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

