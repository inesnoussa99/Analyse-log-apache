/*************************************************************************
                           AnalogControl  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <AnalogControl> (fichier AnalogControl.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <string>
#include <stdexcept>
#include <time.h>

//------------------------------------------------------ Include personnel
#include "AnalogControl.h"
#include "ApacheLogReader.h"
#include "AnalogAnalyse.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

AnalogReturnCode AnalogControl::Run (const int argc, char ** argv)
// Algorithme :
// 
{
    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << " [options] logfilename.log" << endl;
        cerr << "Use --help for more information" << endl;
        return AnalogReturnCode::AC_INVALID_ARGUMENT_COUNT;
    }

    // Variables for options
    option_g = false;
    option_e = false;
    option_t = false;
    option_d = false;
    option_n = false;

    n = 10;
    // Log file name (last required argument)
    string logFileName;
    bool logFileNameSet = false;
    // Parsing command-line arguments
    for (int i = 1; i < argc; ++i)
    {
        string arg = argv[i];

        if (arg == "-h" || arg == "--help")
        {
            cout << "Usage: " << argv[0] << " [options] logfilename.log" << endl;
            cout << "Available options:" << endl;
            cout << "  -g <file.dot>   Generates a .dot file for GraphViz" << endl;
            cout << "  -e              Excludes static files (CSS, JS, images, etc.)" << endl;
            cout << "  -t <hour>       Filters requests by hour (0-23)" << endl;
            cout << "  -d <domain>     Analyzes requests only from the specified domain" << endl;
            cout << "  -n <number>     Displays the n most visited pages" << endl;
            cout << "  -h, --help      Displays this help" << endl;

            cout << "The default domain name is \"intranet-if.insa-lyon.fr\". You can modify it in the file 'config/target_domain.txt'" << endl;

            return AnalogReturnCode::AC_SUCCESS;
        }
        else if (arg == "-g")
        {
            if (i + 1 < argc)
            {
                option_g = true;
                dotFileName = argv[++i];
            }
            else
            {
                cerr << "Error: -g option requires a .dot filename" << endl;
                cerr << "Use --help for more information" << endl;
                return AnalogReturnCode::AC_MISSING_ARGUMENT;
            }
        }
        else if (arg == "-e")
        {
            option_e = true;
        }
        else if (arg == "-t")
        {
            if (i + 1 < argc)
            {
                option_t = true;               
                try
                {
                    hour = stoi(argv[++i]);
                    
                    if (hour < 0 || hour > 23)
                    {
                        cerr << "Error: -t option requires a valid hour between 0 and 23" << endl;
                        return AnalogReturnCode::AC_INVALID_TIME_VALUE;
                    }
                    else
                    {
                        cout << "Warning: only hits between " << hour << "h and " << (hour + 1)%24 << "h have been taken into account" << endl;
                    }
                }
                catch (const std::invalid_argument &)
                {
                    cerr << "Error: -t option requires a numeric hour value" << endl;
                    return AnalogReturnCode::AC_INVALID_TIME_VALUE;
                }
            }
            else
            {
                cerr << "Error: -t option requires an hour value" << endl;
                cerr << "Use --help for more information" << endl;
                return AnalogReturnCode::AC_MISSING_ARGUMENT;
            }
        }
        else if (arg == "-d")
        {
            if (i + 1 < argc)
            {
                option_d = true;
                domain = argv[++i];
            }
            else
            {
                cerr << "Error: -d option requires a domain name" << endl;
                cerr << "Use --help for more information" << endl;
                return AnalogReturnCode::AC_MISSING_ARGUMENT;
            }
        }
        else if (arg == "-n")
        {
            if (i + 1 < argc)
            {
                option_n = true;           
                try
                {
                    n = stoi(argv[++i]);
                    if (n <= 0)
                    {
                        cerr << "Error: -n option requires a valid value greater than 0" << endl;
                        return AnalogReturnCode::AC_INVALID_NUMERIC_VALUE;
                    }
                }
                catch (const std::invalid_argument &)
                {
                    cerr << "Error: -n option requires a numeric value" << endl;
                    return AnalogReturnCode::AC_INVALID_NUMERIC_VALUE;
                }
                catch (const std::out_of_range &)
                {
                    cerr << "Error: -n option requires value within a valid range ( "<< sizeof(hour)<<" bytes )" << endl;
                    return AnalogReturnCode::AC_INVALID_NUMERIC_VALUE;
                }
            }
            else
            {
                cerr << "Error: -n option requires a value" << endl;
                cerr << "Use --help for more information" << endl;
                return AnalogReturnCode::AC_MISSING_ARGUMENT;
            }
        }
        else if (arg[0] == '-')
        {
            cerr << "Unknown option: " << arg << endl;
            cerr << "Use --help for more information" << endl;
            return AnalogReturnCode::AC_UNKNOWN_OPTION;
        }
        else if(!logFileNameSet)
        {
            logFileName = arg;
            logFileNameSet = true;
        }
        else
        {
            cerr << "Too many arguments" << endl;
            cerr << "Use --help for more information" << endl;
            return AnalogReturnCode::AC_TOO_MANY_ARGUMENTS;
        }
    }

    if (logFileName.empty())
    {
        cerr << "Error: log file is empty." << endl;
        cerr << "Use --help for more information" << endl;
        return AnalogReturnCode::AC_MISSING_LOG_FILE;
    }
    
    // Read the log file
    AnalogReturnCode code = ReadFile(logFileName);
    if(code != AnalogReturnCode::AC_SUCCESS)
    {
        return code;
    }

    AnalogAnalyse A; 

    // If -g is enabled, generate a GraphViz file
    if (option_g)
    {
        cout << "Generating .dot file: " << dotFileName << endl;
         A.creationficdot(data,dotFileName);
    }
    
    
    A.analysetopn(data,n);
    
    return AnalogReturnCode::AC_SUCCESS;

} //----- Fin de Run

AnalogReturnCode AnalogControl::ReadFile ( const string & filename )
// Algorithme :
//
{
    ApacheLogReader reader;
    
    if(reader.OpenFile(filename) == ApacheLogReaderReturnCode::ALR_FILE_NOT_FOUND)
    {
        return AnalogReturnCode::AC_MISSING_LOG_FILE;
    }

    if(!option_d)
    {   
        string domain_config_file = "./config/target_domain.txt";
        ifstream file (domain_config_file);
        if(!file.is_open())
        {
            file.open("../"+domain_config_file);
            if(!file.is_open())
            {
                file.open("../../"+domain_config_file);
                if(!file.is_open())
                {
                    cerr << "Error : Domain config file ( config/target_domain.txt ) is missing." << endl;
                    return AnalogReturnCode::AC_MISSING_CONFIG_FILE;
                }
            }
        }
        file>>domain;
        file.close();
    }


    while(!reader.EndOfFile())
    {

        ApacheLogData log = reader.ReadLine();

        string target = log.GetTargetFromRequest();

        if(log.GetMethodFromRequest() != "GET" || log.TargetIsDirectory())
        {
            continue;
        }
    
        if(option_e)
        {
            if( log.GetFileExtension()=="css"  || log.GetFileExtension()=="js"  ||
                log.GetFileExtension()=="png"  || log.GetFileExtension()=="gif" ||
                log.GetFileExtension()=="jpeg" || log.GetFileExtension()=="jpg" ||
                log.GetFileExtension()=="ico")
            {
                continue;
            }
        }

        if(option_t)
        {
    
            size_t start = log.GetDate().find(':');
            int heure_date = stoi(log.GetDate().substr(start + 1, 2));

            if (!(hour <= heure_date && heure_date < hour + 1))
            {
                continue;
            }
        }

        string refererDomain = log.GetDomainFromReferer();
        if(refererDomain != domain)
        {
            continue;
        }
        
        
        string referer = log.GetDocumentFromReferer();

        // On vérifie si la cible existe dans la map principale
        if (data.find(target) != data.end()) {
            // Si la cible existe, on vérifie si le referer existe dans la map interne
            if (data[target].first.find(referer) != data[target].first.end()) {
                // Si le referer existe déjà, on incrémente son compteur
                data[target].first[referer]++;
                data[target].second++;
            } else {
                // Sinon, on l'ajoute avec un compteur initial de 1
                data[target].first[referer] = 1;
                data[target].second++;
            }
        } else {
            // Si la cible n'existe pas, on crée une nouvelle map pour les referers
            data[target] = pair<map<string, int>,int>();
            // Et on ajoute le referer avec un compteur de 1
            data[target].first[referer] = 1;
            data[target].second = 1;
        }
    }

    reader.CloseFile();

    // Affichage du contenu de la structure de donnée
    // for (const auto& cible_entry : data) {
    //     cout << "Cible: " << cible_entry.first << "- Compte General "<< cible_entry.second.second << endl;
    //     for (const auto& referer_entry : cible_entry.second.first) {
    //         cout << "  Referer: " << referer_entry.first << " - Compte: " << referer_entry.second << endl;
    //     }
    // }

    return AnalogReturnCode::AC_SUCCESS;

} //----- Fin de ReadFile


//------------------------------------------------- Surcharge d'opérateurs

// AnalogControl & AnalogControl::operator = ( const AnalogControl & unAnalogControl )

//-------------------------------------------- Constructeurs - destructeur

// AnalogControl::AnalogControl ( const AnalogControl & unAnalogControl )

AnalogControl::AnalogControl ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <AnalogControl>" << endl;
#endif
} //----- Fin de AnalogControl


AnalogControl::~AnalogControl ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <AnalogControl>" << endl;
#endif
} //----- Fin de ~AnalogControl


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
