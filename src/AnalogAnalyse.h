/*************************************************************************
                           AnalogAnalysepp.h
 La classe AnalogAnalyse fait  le traitement et l'analyse de ces données stockées
        pour l'affichage du top 10 des sites visités ainsi que la création du fichier
        .dot
                             -------------------
    début                : $DATE$
    copyright            : (C) $2024$ par $Shili Ibrahim$
    e-mail               : ibrahim.shili@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <AnalogAnalyse> (fichier AnalogAnalyse.h) ----------------
#if !defined(ANALOGANALYSE)
#define ANALOGANALYSE
#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include "AnalogControl.h"
using namespace std;
//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

class AnalogAnalyse
{

public:
    //----------------------------------------------------- Méthodes publiques
    // Analyse et affiche le top n des sites les plus visités
    int analysetopn(const logsData &data, int n) const;

    // Crée un fichier .dot basé sur les données des logs
    int creationficdot(const logsData &data, string filename) const;

    //----------------------------------------------------- Méthodes publiques pour le filtrage de données

    //-------------------------------------------- Constructeurs - destructeur

    // Mode d'emploi : constructeur par défaut

    AnalogAnalyse();

    // Mode d'emploi: Libère la mémoire allouée dynamiquement pour les logs stockés
    ~AnalogAnalyse();

    //----------------------------------------------------- Attributs protégés
private:
    // Trouve la correspondance d'un nœud dans une liste
    string retrouvercorrespondancenode(const string &m, const vector<pair<string, string>> &labelnode) const;

    // Fonction de comparaison pour trier les sites par nombre de visites
    static bool compareavecsecond(const pair<int, string> &a, const pair<int, string> &b);
};

//-------------------------------- Autres définitions dépendantes de <AnalogAnalyse>

#endif // AnalogAnalyse