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
#include <ostream>
#include <vector>
#include <algorithm>
//------------------------------------------------------ Include personnel
#include "AnalogAnalyse.h"
//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
 bool AnalogAnalyse::compareavecsecond(const pair<int, string>& a, const pair<int, string>& b) 
{
    return a.first > b.first; // Tri décroissant
}

string AnalogAnalyse::retrouvercorrespondancenode(const string& m, const vector<pair<string, string>>& labelnode) const
{
    string result;
    int a=0;
    for (vector<pair<string, string>>::const_iterator kt = labelnode.cbegin(); kt != labelnode.cend(); ++kt) 
    {
        if (kt->second == m) 
        {  // Vérifier si le site est égal à 
            result = kt->first; // Récupérer le premier élément
            a=1;
            break;              // Sortir de la boucle une fois trouvé
        }
    }
    if(a==0) 
    {
        return "erreur";
    }
    return result;
}

int AnalogAnalyse::analysetopn(const logsData& data, int n) const
{
    //typedef map< string, pair< map<string,int> ,int>> logsData; 
    if (data.empty())
    {
        cout<< "Données vides" <<endl;
        return 1;
    }
    
    logsData::const_iterator debut = data.cbegin();
    logsData::const_iterator fin = data.cend();

    vector<pair<int, string>> valtriee; // conteneur temporaire pour stocker le site cible et son nombre de hit 

    for ( logsData::const_iterator it = debut; it != fin ; ++it )
    {
                const string& premierecle = it->first; // Clé du premier niveau (string)
                pair<map<string,int>,int> paireinterne= it->second; 
               
                valtriee.push_back(make_pair(paireinterne.second,premierecle)); // insérer le site cible et son nombre de hit dans le vecteur
    }

    sort(valtriee.begin(),valtriee.end(),compareavecsecond);// trier entre une plage donnée avec un critère spécifique ici la fonction compareavecsecond
    
    for ( vector<pair<int, string>>::iterator i = valtriee.begin();  i != valtriee.begin()+ n && i != valtriee.end() ; i++) 
    {
        //afficher le top n sites cibles avec le plus de hits
        cout << i->second << " (" << i->first << " hits)" << endl;
    }
    return 0;
}


int AnalogAnalyse::creationficdot(const logsData &data,string filename) const
{
        //typedef map< string, pair< map<string,int> ,int>> logsData; 
     if (data.empty())
    {
        cout<< "Données vides" <<endl;
        return 1;
    }
    ofstream fichier(filename);
    if (!fichier.is_open()) 
    {
        cerr << "Erreur : Impossible d'ouvrir le fichier .dot pour écrire." << endl;
        return 1 ;
    }
    vector<pair<string, string>> labelnode; // conteneur temporaire pour stocker les nodes et leurs noms de sites correspondant
   

    logsData::const_iterator debut = data.cbegin();
    logsData::const_iterator fin = data.cend();
    int i=0;

    fichier << "digraph {" << endl;// début fichier .dot


for (logsData::const_iterator it = debut; it != fin; ++it) 
{
        pair<map<string, int>, int> secondPair = it->second;
        map<string, int> internalMap = secondPair.first;
        //ajout de tous les sites cibles au nodes
           string sitecible = it->first; // Clé du premier niveau le site cible(string)
                fichier<< "node" << i << " [label="<< sitecible <<"];" <<endl;
                string nodei= "node" + to_string(i);
                labelnode.push_back(make_pair(nodei, sitecible)); 
                i++;

        // Vérification pour chaque site référent de la map interne s'il existe ou pas dans la plage de tout les sites cible (voir propriètès graph)
        for (map<string, int>::const_iterator jt = internalMap.begin(); jt != internalMap.end(); ++jt) 
        {
             string internalKey = jt->first;  // Clé interne (niveau 2)

            // Si cette clé interne (site référent) n'existe pas parmi les premières clés (firstKey) il faut l'ajouter dans les nodes de la graphe
            if (data.find(internalKey) == data.end()) 
            {
                fichier<< "node" << i << " [label="<< internalKey <<"];" <<endl;
                
                string nodeiref= "node" + to_string(i);
                labelnode.push_back(make_pair(nodeiref, sitecible)); 
                i++;
            }
        }
}

for (logsData::const_iterator it = debut; it != fin; ++it) 
{
         pair<map<string, int>, int> secondPair = it->second;
         map<string, int> internalMap = secondPair.first;

                 const  string sitecible = it->first; // Clé du premier niveau le site cible(string)

                    string nodecible= retrouvercorrespondancenode(sitecible,labelnode);


        // Vérification pour chaque site référent de la map interne s'il existe ou pas dans la plage de tout les sites cible (voir propriètès graph)
        for (map<string, int>::const_iterator jt = internalMap.begin(); jt != internalMap.end(); ++jt) 
        {
           const  string siteref = jt->first;  // Clé interne (niveau 2)
            int  rhit = jt->second;
            string noderef= retrouvercorrespondancenode(siteref,labelnode);

            fichier << noderef << "-> " << nodecible << " [label="<< rhit <<"];" <<endl;
        }
            
        }
   
    fichier << "}"; 
    return 0;
}
AnalogAnalyse::AnalogAnalyse()
{
    #ifdef MAP
    cout << "Appel au construction de <AnalogAnalyse>" << endl;
    #endif
}
AnalogAnalyse::~AnalogAnalyse()
{
    #ifdef MAP
    cout << "Appel au destructeur de <AnalogAnalyse>" << endl;
    #endif
}