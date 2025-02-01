/*************************************************************************
                           AnalogControl  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <AnalogControl> (fichier AnalogControl.h) ----------------
#if !defined(ANALOG_CONTROL_H)
#define ANALOG_CONTROL_H

//--------------------------------------------------- Interfaces utilisées
#include <map>
#include <string>
#include "ApacheLogReader.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

// Structure pour stocker les données des logs

typedef std::map<std::string, std::pair<std::map<std::string, int>, int>> logsData;

//------------------------------------------------------------------------
// Rôle de la classe <AnalogControl>
// Gère la lecture des fichiers logs, applique des options de filtrage et
// stocke les données pour analyse.
//------------------------------------------------------------------------

class AnalogControl
{
    //----------------------------------------------------------------- PUBLIC

public:
    //----------------------------------------------------- Méthodes publiques

    // Lance l'exécution du programme avec les arguments donnés
    int Run(const int argc, char **argv);
    // Mode d'emploi :
    //
    // Contrat :
    //
    // Lit un fichier de logs et stocke les données

    int ReadFile(const std::string &filename);
    // Mode d'emploi :
    //
    // Contrat :
    //

    //------------------------------------------------- Surcharge d'opérateurs

    // AnalogControl & operator = ( const AnalogControl & unAnalogControl );

    //-------------------------------------------- Constructeurs - destructeur

    // AnalogControl ( const AnalogControl & unAnalogControl );
    // Constructeur par défaut
    AnalogControl();
    // Mode d'emploi :
    //
    // Contrat :
    //
    // Destructeur
    virtual ~AnalogControl();
    // Mode d'emploi :
    //
    // Contrat :
    //

    //------------------------------------------------------------------ PRIVE

protected:
    //----------------------------------------------------- Méthodes protégées

    // Vérifie si une chaîne se termine par un suffixe donné
    bool endsWith(const std::string &str, const std::string &suffix);
    // Mode d'emploi :
    //
    // Contrat :
    //

    // Extrait le domaine à partir d'un référent (referer)
    std::string getDomainFromReferer(const std::string &referer);
    // Mode d'emploi :
    //
    // Contrat :
    //

    // Extrait le document à partir d'un référent
    std::string getDocumentFromReferer(const std::string &referer);
    // Mode d'emploi :
    //
    // Contrat :
    //

    // Extrait la cible d'une requête HTTP
    std::string getTargetFromRequest(const std::string &request);
    // Mode d'emploi :
    //
    // Contrat :
    //

    //----------------------------------------------------- Attributs protégés
    logsData data; // Stocke les données des logs

    bool option_g;           // Générer un fichier .dot
    std::string dotFileName; // Nom du fichier .dot

    bool option_e; // Exclure les fichiers image, CSS et JS
    bool option_t; // Appliquer un filtre sur une plage horaire d'une heure
    int hour;      // Heure spécifique pour le filtre

    bool option_d;      // Utiliser un nom de domaine personnalisé
    std::string domain; // Nom de domaine personnalisé
};

//-------------------------------- Autres définitions dépendantes de <AnalogControl>

#endif // ANALOG_CONTROL_H
