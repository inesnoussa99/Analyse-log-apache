/*************************************************************************
                           AnalogAnalyse  
     La classe AnalogAnalyse fait  le traitement et l'analyse de ces données stockées 
        pour l'affichage du top 10 des sites visités ainsi que la création du fichier
        .dot
                                     -------------------
    début                : $DATE$
    copyright            : (C) $2024$ par $Shili Ibrahim$
    e-mail               : ibrahim.shili@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <AnalogAnalyse> (fichier AnalogAnalyse.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;
#include <cstring>
#include <utility> // make_pair()
#include <map>
#include <vector>
#include <algorithm>
//------------------------------------------------------ Include personnel
#include "AnalogAnalyse.h"
//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
bool compareavecsecond(const pair<int, string>& a, const pair<int, string>& b) 
{
    return a.second > b.second; // Tri décroissant
}

void AnalogAnalyse::analysetopn(logsdata data, int n) const
{
    //typedef map< string, map< map<string,int> ,int>> logsdata; 
    if (data.empty())
    {
        cout<< "Données vides" <<endl;
        return;
    }
 
    logsdata::iterator debut = data.begin();
    logsdata::iterator fin = data.end();

    vector<pair<int, string>> valtriee; // conteneur temporaire pour stocker le site cible et son nombre de hit 

    for ( logsdata::iterator it = debut; it != fin ; ++it )
    {
                const string& premierecle = it->first; // Clé du premier niveau (string)
                map<map<string,int>,int> & mapinterne= it->second; 
                for (map<map<string,int>,int> ::iterator jt = mapinterne.begin(); jt != mapinterne.end(); jt++)//parcourir la deuxième map
                {
                    valtriee.push_back(make_pair(jt->second,premierecle)); // insérer le site cible et son nombre de hit dans le vecteur
                }  
    }
    sort(valtriee.begin(),valtriee.end(),compareavecsecond);// trier entre un plage donner avec un critère spécifique ici la fonction compareavecsecond
    
    for ( vector<pair<int, string>>::iterator i = valtriee.begin();  i != valtriee.begin()+ n && i != valtriee.end() ; i++) 
    {
        //afficher le top n sites cibles avec le plus de hits
        cout << i->first << ' (' << i->second << ')' << endl;
    }
    return;
}


void AnalogAnalyse::creationficdot(logsdata data) const
{

}