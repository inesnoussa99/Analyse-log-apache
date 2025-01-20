/*************************************************************************
                           App.h  
 La classe App représente l'application qui sert à faire le filtrage 
        du fichier log en fonction des options choisi par l'utilisateur.
        Elle fait aussi le traitement et l'analyse de ces données stockées 
        pour l'affichage du top 10 des sites visités ainsi que la création du fichier
        .dot
                             -------------------
    début                : $DATE$
    copyright            : (C) $2024$ par $Shili Ibrahim$ 
    e-mail               : ibrahim.shili@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <App> (fichier App.h) ----------------
#if !defined(APP)
#define APP
#include <iostream>
#include <cstring>
#include <map>
#include "Lecteur.h"
using namespace std;
//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types


class App 
{

public:
    //----------------------------------------------------- Méthodes publiques
    void analysetopten() const;
    void creationficdot() const; 
    void Stocker();//stocker un log  

    //----------------------------------------------------- Méthodes publiques pour le filtrage de données

    //------------------------------------------------- Surcharge d'opérateurs
     // Mode d'emploi :
    //L'opérateur d'affectation = est surchargé dans la classe App pour permettre la copie profonde entre deux instances de cette classe.
    App &operator=(const App &uneApp);
    


    //-------------------------------------------- Constructeurs - destructeur
    // Mode d'emploi: constructeur par copie
    //Crée une copie profonde d'un autre trajet composé :
    //Une nouvelle liste est allouée et copiée à partir de celle de uneApp.
    //Le nombre de trajets est également copié.
    App(const App & uneApp);

    
    // Mode d'emploi : constructeur par défaut
    
    App();

    
    //Mode d'emploi: Libère la mémoire allouée dynamiquement pour les logs stockés
     ~App();
    
    

protected:
    //----------------------------------------------------- Attributs protégés
    typedef int Rhit; // nombre de hit sur le site Référent 
    typedef int Chit; // nombre de hit sur le site cible
    typedef map< string, map< map<string,Rhit> ,Chit>> tdic; //dictionnaire


};

//-------------------------------- Autres définitions dépendantes de <App>

#endif // App