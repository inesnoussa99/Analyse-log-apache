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
#include <ctime>
//------------------------------------------------------ Include personnel
#include "AnalogControl.h"
#include "ApacheLogReader.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
int AnalogControl::Run (const int argc, char ** argv)
// Algorithme :
// 
{
    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << " [options] logfilename.log" << endl;
        return -1;
    }

    // Variables for options
    option_g = false;
    option_e = false;
    option_t = false;
    option_d = false;

    // Log file name (last required argument)
    string logFileName;
    bool logFileNameSet = false;
    // Parsing command-line arguments
    for (int i = 1; i < argc; ++i)
    {
        string arg = argv[i];

        if (arg == "-g")
        {
            if (i + 1 < argc)
            {
                option_g = true;
                dotFileName = argv[++i];
            }
            else
            {
                cerr << "Error: -g option requires a .dot filename" << endl;
                return -1;
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
                        throw out_of_range("Hour out of range");
                    }
                }
                catch (const exception& e)
                {
                    cerr << "Error: -t option requires a valid hour between 0 and 23" << endl;
                    return -1;
                }
            }
            else
            {
                cerr << "Error: -t option requires an hour value" << endl;
                return -1;
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
                return -1;
            }
        }
        else if (arg[0] == '-')
        {
            cerr << "Unknown option: " << arg << endl;
            return -1;
        }
        else if(!logFileNameSet)
        {
            logFileName = arg;
            logFileNameSet = true;
        }
        else
        {
            cerr << "Too many arguments" << endl;
            return -1;
        }
    }

    if (logFileName.empty())
    {
        cerr << "Error: log file is required." << endl;
        return -1;
    }
    
    // Read the log file
    ReadFile(logFileName);

    // If -g is enabled, generate a GraphViz file
    if (option_g)
    {
        cout << "Generating .dot file: " << dotFileName << endl;
        // Call a method to generate the .dot file (to be implemented)
    }

    // Default: display the top 10 most visited documents
    // Method to display results (to be implemented)

    return 0;

} //----- Fin de Run

int AnalogControl::ReadFile ( const string & filename )
// Algorithme :
//
{
    ApacheLogReader reader;
    reader.OpenFile(filename);

    if(!option_d)
    {
        ifstream file ("config/target_domain.txt");
        if(!file.is_open())
        {
            cerr << "Domain config file ( target_domain.txt ) is missing..." << endl;
            return -1;
        }
        file>>domain;
        file.close();
    }


    while(!reader.EndOfFile())
    {

        ApacheLogData log = reader.ReadLine();

        string target = getTargetFromRequest(log.GetRequest());

        if(option_e)
        {
            if(endsWith(target,".css")   || endsWith(target,".js") ||
               endsWith(target,".png")  || endsWith(target,".gif")||
               endsWith(target,".jpeg") || endsWith(target,".jpg"))
            {
                continue;
            }
        }

        if(option_t)
        {
            tm tm = {};
    
            // Le format attendu est "[08/Sep/2012:11:15:00 +0200]"
            const char* format = "[%d/%b/%Y:%H:%M:%S %z]";

            // Utiliser strptime pour analyser la date
            if (strptime(log.GetDate().c_str(), format, &tm) == nullptr) {
                continue;
            }

            int heure_date = tm.tm_hour;

            if (!(hour <= heure_date && heure_date < hour + 1))
            {
                continue;
            }
        }

        string refererDomain;
        if(option_d)
        {
            refererDomain = getDomainFromReferer(log.GetReferer());
            if(refererDomain != domain){
                continue;
            }
        }
        else
        {
            refererDomain = getDomainFromReferer(log.GetReferer());
            if(refererDomain != domain)
            {
                continue;
            }
        }
        
        string referer = getDocumentFromReferer(log.GetReferer());

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

    for (const auto& cible_entry : data) {
        cout << "Cible: " << cible_entry.first << "- Compte General "<< cible_entry.second.second << endl;
        for (const auto& referer_entry : cible_entry.second.first) {
            cout << "  Referer: " << referer_entry.first << " - Compte: " << referer_entry.second << endl;
        }
    }

    return 0;

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

bool AnalogControl::endsWith(const string& str, const string& suffix)
{
    if (str.size() < suffix.size()) return false;
    return equal(suffix.rbegin(), suffix.rend(), str.rbegin());
}

string AnalogControl::getDomainFromReferer(const string& referer) 
{
    // Trouver la position après "http://" ou "https://"
    string::size_type startPos = referer.find("://");
    if (startPos == string::npos) {
        return ""; // Pas un URL valide
    }
    startPos += 3; // Sauter "://"

    // Trouver la fin du domaine (soit le premier '/' ou la fin de la chaîne)
    string::size_type endPos = referer.find('/', startPos);
    if (endPos == string::npos) {
        endPos = referer.length(); // Si aucun '/' n'est trouvé
    }

    // Extraire le domaine
    return referer.substr(startPos, endPos - startPos);
}

string AnalogControl::getDocumentFromReferer(const string& referer)
{
    // Trouver la position de "http://", ou "https://"
    size_t startPos = referer.find("://");

    // Si "://" est trouvé, décaler le curseur pour sauter "://"
    if (startPos != std::string::npos) {
        startPos += 3; // "://"
    } else {
        // Si "://" n'est pas trouvé, l'URL est mal formée
        return "";
    }

    // Trouver la position du premier "/" après le nom de domaine
    size_t slashPos = referer.find("/", startPos);

    // Si "/" est trouvé, extraire la partie après le "/"
    if (slashPos != std::string::npos) {
        return referer.substr(slashPos + 1);  // Extraire tout après "/"
    }

    // Si "/" n'est pas trouvé, il n'y a pas de chemin
    return "";
}

string AnalogControl::getTargetFromRequest(const string& request)
{
    size_t startPos = request.find(" ") + 1; // Après le premier espace, pour l'URL
    
    // Trouver la position du dernier espace avant la version HTTP
    size_t endPos = request.rfind(" ");
    
    // Si les positions sont valides, on extrait l'URL
    if (startPos != std::string::npos && endPos != std::string::npos && startPos < endPos) {
        return request.substr(startPos, endPos - startPos); // Extrait l'URL
    }
    
    // Si les positions ne sont pas valides, retourner une chaîne vide
    return "";
}