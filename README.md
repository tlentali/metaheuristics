# Résolution du problème de patitionnement de graphe via l'utilisation de métaheuristiques

Ce projet a pour but de partitionner des graphes connexes non-orientés en K classes afin d’obtenir un minimum d’arêtes interclasses.  
Nous allons pour cela utiliser un algorithme d’énumération, un algorithme glouton de descente de gradient, et les méta-heuristiques recuit simulé et recherche tabou.
Tous les résultats et les temps d’exécution sont directement stockés dans un fichier.  
Pour ce rapport, nous avons décidé d’analyser les performances de nos algorithmes pour un partitionnement en K = 3 classes, mais bien entendu, nos programmes peuvent exécuter tout type de partitionnement allant de 1 jusqu’au nombre de sommets du graphe étudié.  
Pour une meilleure analyse, nous avons généré jusqu'à 5 fois nos algorithmes afin d’obtenir un temps d’exécution minimum, maximum, et ainsi calculer la moyenne des temps d’exécution.  
Il en est de même pour le calcul du nombre des arêtes interclasse.

Le projet est composé de 4 fichiers `.cpp`, un par algorithme.  
Afin d'executer nos progammes, depuis un terminal, se rendre dans le repertoir du `.cpp` à l'aide de la commande `cd`, 
ce repertoire doit egalement contenir les `.txt` des graphes, ils seront tous lu automatiquement.  

## Execution

Dans un terminal : 

```bash
g++ -o nomDuFichier nomDuFichier.cpp 
./nomDuFichier
```

Un fichier sera alors crée à coté du `.cpp` contenant les solutions touvées par l'algorithme.

## Enumeration

Nous avons décidé de générer toutes les solutions possibles de l’espace de recherche.  
On appelle cette méthode énumération explicite.  
Elle a pour but de parcourir toutes les solutions, vérifier leur validité et enfin stocker la meilleure solution parmi celles qui sont valides.  
Nous pouvons constater au travers des résultats, la complexité K nbsommets qui fait exploser le temps d’exécution de l’algorithme, ce qui nous empêche d’obtenir des résultats pour un graphe ayant plus de 17 sommets.

## Descente de gradient

Cet algorithme glouton a pour but d’améliorer la solution de manière successive jusqu’à ce qu’un minimum local ait été trouvé. Pour avoir plus de chances de tomber sur la solution optimale, nous générons plusieurs fois une solution aléatoire de départ afin de commencer notre descente en différents endroits.  
En premier lieu on génère une solution aléatoire qu’on appelle solution de base.  
Depuis cette solution de base, on explore tout son voisinage afin de trouver le meilleure solution voisine.  
Pour le voisinage nous avons choisi d’utiliser la méthode swap qui consiste à échanger deux sommets de classes différentes.  
Nous avons utilisé swap pour tout les algorithmes car il présente l’avantage de ne pas modifier la structure de la solution et nous garantit de trouver une solution valide.  
Si la solution trouvée améliore le résultat, on recommence le processus jusqu’à ce que la solution soit la meilleure de son voisinage.

## Recuit Simulé

Cet algorithme est une méta-heuristique qui s’inspire de la physique et plus particulièrement de la métallurgie afin d’améliorer la qualitée d’un métal.  
En partant d’une haute température à laquelle la matière est devenue liquide, la phase de refroidissement conduit la matière à retrouver sa forme solide par une diminution progressive de la température jusqu’à atteindre un état d’énergie minimale qui correspond à une structure stable du métal.  
De la même manière, la fonction qui évalue notre solution correspond à l’énergie et on crée un paramètre virtuel afin de gérer la température. En premier lieu on génère une solution aléatoire qu’on appelle solution de base.  
À partir de cette solution nous allons sur 10 paliers de températures différents, suivant un schéma de refroidissement géométrique (t n+1 = t n ∗ 0.9), générer 1000 voisins aléatoires puis pour chaque voisin si la solution est améliorante alors on la prend, sinon on applique le critère de Metropolis afin de savoir si on garde la solution ou pas.  
Le critère de Metropolis est une fonction stochastique qui définit la probabilité d’accepter une solution non améliorante.

## Recherche tabou

Nous avons utilisé la recherche tabou par mouvement avec mémoire à court terme.  
La liste tabou utilisée est de taille 8 et de type first in first out.  
A chaque itération on parcourt l’ensemble des solutions voisines et choisit la meilleure qui n’est pas interdite, même si elle est plus mauvaise que la solution courante.  
Son avantage par rapport à la descente de gradient est que la liste tabou permet d’interdire certaines solutions afin de ne pas rester bloqué dans un minimum local et de changer de voisinage.

# Conclusion

Le problème de partitionnement de graphe demande beaucoup de ressources afin d’obtenir un résultat optimal.  
Néanmoins il est possible d’approcher au plus près de l’optimal avec des temps raisonnables grâce aux algorithmes gloutons et à des méta-heuristiques.  
Ce projet nous convainc de l’efficacité de ces méthodes, notamment celle du recuit simulé qui nous a permis d’avoir un résultat pour un graphe de 1000 sommets (ce qui aurais pris avec l’énumération un temps qui dépasse les limites de ce projet).
