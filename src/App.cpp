/*************************************************************************
                           App  
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

//---------- Réalisation de la classe <App> (fichier App.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;
#include <cstring>
#include <utility> // make_pair()
#include <map>

//------------------------------------------------------ Include personnel
#include "App.h"
#include "Lecteur.h"
//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
