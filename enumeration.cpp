#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

void plusUn(int *tab, int endroit, int base) {
	tab[endroit] = tab[endroit] + 1;
	if (tab[endroit] == base) {
		tab[endroit] = 0;
		plusUn(tab, endroit - 1, base);
	}
}

int main() {
	vector<string> nomFichier;
	nomFichier.push_back("quatreSommets.txt");
	nomFichier.push_back("cinqSommets.txt");
	nomFichier.push_back("dixSommets.txt");
	nomFichier.push_back("quinzeSommets.txt");
	nomFichier.push_back("dixSeptSommets.txt");
	nomFichier.push_back("vingtEtunSommets.txt");
	nomFichier.push_back("vingtDeuxSommets.txt");
	nomFichier.push_back("vingtTroisSommets.txt");
	nomFichier.push_back("vingtQuatreSommets.txt");
	nomFichier.push_back("vingtCinqSommets.txt");
	nomFichier.push_back("trenteSommets.txt");
	nomFichier.push_back("cinquanteSommets.txt");
	nomFichier.push_back("centSommets.txt");
	nomFichier.push_back("cinqCentSommets.txt");
	nomFichier.push_back("milleSommets.txt");
	nomFichier.push_back("dixMilleSommets.txt");

	stringstream sstm;
	ofstream ofic("enumeration.dat", ios::out);

	for (int p = 0; p < 5; p++) {

		int base = 3;
		float temps_initial = 0, temps_final = 0, temps_cpu = 0;
		temps_initial = clock();
		/*
		 * Partie LECTURE
		 */

		int nbSommets = 0, nbAretes = 0, dmin = 0, dmax = 0, **mat1, *deg,
				**matAdj, temp1, temp2, temp3;
		string jeux;

		ifstream ific(nomFichier[p].c_str(), ios::in);

		if (ific == 0) {
			cerr << "Impossible d'ouvrir le fichier !" << endl;
		}

		while (jeux != "nbAretes") {
			ific >> jeux >> ws;
		}

		ific >> nbSommets >> ws;
		ific >> nbAretes >> ws;

		while (jeux != "dmax") {
			ific >> jeux >> ws;
		}

		ific >> dmin >> ws;
		ific >> dmax >> ws;

		while (jeux != "val") {
			ific >> jeux >> ws;
		}

		mat1 = new int*[nbAretes]; //creation de la matrice qui va stocker l'information
		for (int b = 0; b < nbAretes; b++) {
			mat1[b] = new int[3];
		}

		for (int c = 0; c < nbAretes; c++) {
			ific >> mat1[c][0] >> ws >> mat1[c][1] >> ws >> mat1[c][2] >> ws;
		}

		while (jeux != "degre") {
			ific >> jeux >> ws;
		}

		deg = new int[nbSommets];

		for (int d = 0; d < nbSommets; d++) {
			ific >> jeux >> ws >> deg[d] >> ws;
		}

		ific.close();

		/*for(int c = 0; c < nbAretes; c++)
		 {
		 for(int cc = 0; cc < 3; cc++)
		 {
		 cout<<mat1[c][cc]<<" ";
		 }
		 cout<<endl;
		 }


		 for(int d = 0; d < nbSommets; d++)
		 {
		 cout<<deg[d]<<endl;
		 }
		 */

		matAdj = new int*[nbSommets]; //creation de la matrice d'adjacance
		for (int e = 0; e < nbSommets; e++) {
			matAdj[e] = new int[nbSommets];
		}

		for (int f = 0; f < nbSommets; f++) {
			for (int g = 0; g < nbSommets; g++) {
				matAdj[f][g] = 0;
			}
		}

		for (int i = 0; i < nbAretes; i++) {
			matAdj[mat1[i][0] - 1][mat1[i][1] - 1] = mat1[i][2];
			matAdj[mat1[i][1] - 1][mat1[i][0] - 1] = mat1[i][2];
		}
		/*
		 for(int i = 0; i < nbSommets; i++)
		 {
		 for(int j =0; j < nbSommets; j++)
		 {
		 cout<<matAdj[i][j]<<" ";
		 }
		 cout<<endl;
		 }
		 cout<<endl;*/
		/*
		 * Partie TRAITEMENT
		 */

		int nbsom = nbSommets, cmp3 = 0, cmp4 = 0, cmp5 = 0, resultat = 0, min =
				100000;
		int tab[nbsom], solution[nbSommets];
		int compt[base];
		int nbSol = pow(base, nbsom);
		int estValide;
		int cardmin = (nbsom / base);
		int cardmax = (nbsom / base) + 1;
		vector<vector<int> > list(base);
		vector<int> listForbiden;

		for (int i = 0; i < nbsom; i++) {
			tab[i] = 0;
		}

		for (int i = 0; i < nbSol; i++) {

			/*for(int j=0; j<nbsom; j++)
			 {
			 cout<<tab[j]<<" ";
			 }
			 cout<<endl;
			 */

			for (int val = 0; val < base; val++) //compte le cardinal dans les classes
					{
				compt[val] = 0; //initialisation a 0 du compteur
				for (int j = 0; j < nbsom; j++) {
					if (tab[j] == val) {
						compt[val] = compt[val] + 1;
					}
				}
				//cout<<compt[val]<<" ";
				if ((compt[val] >= cardmin) && (compt[val] <= cardmax)) //verification de la validité de la solution
						{
					cmp3++;
				}
			}
			//cout<<endl;

			if (cmp3 == base) {
				estValide = 1;
				cmp4++;

				for (int c = 0; c < base; c++) {
					for (int b = 0; b < nbsom; b++) {
						if (tab[b] == c) {
							list[c].push_back(b);
						}
					}

				}
				for (int d = 0; d < base; d++) {
					for (int e = 0; e < list[d].size(); e++) {
						listForbiden.push_back(list[d][e]);
					}
					for (int f = 0; f < list[d].size(); f++) {
						for (int g = 0; g < nbsom; g++) {
							for (int h = 0; h < listForbiden.size(); h++) {
								if (g == listForbiden[h]) {
									cmp5++;
								}
							}
							if (cmp5 == 0) {

								resultat = resultat + matAdj[list[d][f]][g];
							}
							cmp5 = 0;
						}
					}
				}
				if (resultat < min) //recuperation du min
						{
					min = resultat;
					for (int h = 0; h < nbSommets; h++) {
						solution[h] = tab[h];
					}
				}
				/*for(int j=0; j<nbsom; j++)
				 {
				 cout<<tab[j]<<" ";
				 }
				 cout<<endl;
				 for(int val=0; val<base; val++)
				 {
				 cout<<compt[val]<<" ";
				 }
				 cout<<"valide"<<endl;
				 cout<<"Resultat : "<<resultat<<endl<<endl;*/
				resultat = 0;
				listForbiden.clear();
				for (int i = 0; i < base; i++) {
					list[i].clear();
				}

			} else {
				estValide = 0;
				//cout<<"non valide"<<endl;
			}
			cmp3 = 0;

			plusUn(tab, nbsom - 1, base); //genere une nouvelle solution
		}

		ofic << nomFichier[p] << endl;

		ofic << "Un exemple de solution minimal:" << endl;
		for (int h = 0; h < nbSommets; h++) {
			ofic << solution[h] << " ";
		}
		ofic << endl;
		ofic << "Le nombre minimum d'aretes interclasse est : " << min << endl;
		temps_final = clock();

		//Calcul du temps d'execution:
		temps_cpu = (temps_final - temps_initial) / CLOCKS_PER_SEC * 1000;
		ofic << "Temps d'execution: " << temps_cpu << " millisecondes." << endl
				<< endl;
	}
	return 0;
}
