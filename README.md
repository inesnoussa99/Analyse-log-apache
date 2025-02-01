# Analog

## Description
**Analog** est un programme permettant d'analyser les fichiers de logs Apache. Il offre plusieurs options pour filtrer et afficher les données les plus pertinentes en fonction des besoins de l'utilisateur.

## Fonctionnalités
- Lecture et analyse des fichiers de logs Apache
- Génération d'un fichier GraphViz (`.dot`) pour la visualisation des connexions
- Filtrage des requêtes selon l'heure, le domaine, et le type de fichiers
- Affichage des pages les plus consultées

## Prérequis
Avant d'utiliser **Analog**, assurez-vous que votre environnement possède les éléments suivants :

- Un compilateur compatible avec C++11 ou supérieur (g++, clang, etc.)
- CMake pour la compilation (optionnel)
- Un fichier de log Apache valide

## Compilation
Pour compiler le projet, utilisez la commande suivante :

```sh
make
```
## Utilisation
Lancer l'exécutable en ligne de commande avec les options suivantes :
```sh
bin/analog [options] logfilename.log
```

## Options disponibles

| Option | Description |
|--------|-------------|
| -g <file.dot> | Génère un fichier .dot pour visualisation avec GraphViz |
| -e | Exclut certains fichiers statiques (CSS, JS, images, etc.) |
| -t <heure> | Filtre les requêtes selon une heure donnée (0-23) |
| -d <domaine> | Prend en compte uniquement les requêtes du domaine spécifié |
| -n <nombre>	| Affiche les n pages les plus visitées |

## Auteurs

    Binôme B3304
    CHEBBI Ines - NAJI Adam
    Contacts : ines.chebbi@insa-lyon.fr - adam-yassine.naji@insa-lyon.fr
    
    Binôme B3303
    SHILI Ibrahim - CHAKROUN Mohamed
    Contacts : ibrahim.shili@insa-lyon.fr - med-amine.chakroun@insa-lyon.fr
    
    Année : 2024-2025 