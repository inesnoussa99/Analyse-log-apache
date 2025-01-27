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
    int analysetopn(const logsData &data,int n) const; // analyse du top n des sites les plus visités
    int creationficdot(const logsData &data,string filename) const;  // création du fichier .dot 

    //----------------------------------------------------- Méthodes publiques pour le filtrage de données

    //-------------------------------------------- Constructeurs - destructeur
    
    // Mode d'emploi : constructeur par défaut
    AnalogAnalyse();


    //Mode d'emploi: Libère la mémoire allouée dynamiquement pour les logs stockés
     ~AnalogAnalyse();
    
    //----------------------------------------------------- Attributs protégés

private:
    string retrouvercorrespondancenode(const string& m, const vector<pair<string, string>>& labelnode) const;
    static bool compareavecsecond(const pair<int, string>& a, const pair<int, string>& b);

};

//-------------------------------- Autres définitions dépendantes de <AnalogAnalyse>

#endif // AnalogAnalyse