/***************************************************
Le nombre de classe peut etre changé a la ligne 98
****************************************************/

#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

vector<int> rsol(int base, int nbSommets) {
	int j = 0;
	vector<int> sol(nbSommets);
	vector<int> compt(base);
	for (int i = 0; i < base; i++) {
		compt[i] = (nbSommets / base);
	}

	while (j < nbSommets) {
		if (count(compt.begin(), compt.end(), 0) == base) {
			for (int i = 0; i < compt.size(); ++i) {
				compt[i] = 1;
			}
		}
		int r = rand() % base;
		if (compt[r] != 0) {
			compt[r]--;
			sol[j] = r;
			j++;
		}
	}
	return sol;
}
int eval(int** matAdj, int nbSommets, vector<int> sol) {
	int val = 0;
	for (int i = 0; i < nbSommets; i++) {
		for (int j = i + 1; j < nbSommets; ++j) {
			if (sol[i] != sol[j]) {
				val += matAdj[i][j];
			}
		}
	}
	return val;
}

bool critmetro(int delta, float t) {
	double r;
	if (delta <= 0)
		return true;
	else {
		r = (double) rand();

		return exp(-(delta / t)) > (r / RAND_MAX);
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
	ofstream ofic("recuit.dat", ios::out);

	for (int p = 0; p < 17; p++) {
vector<int> vsol;
	vector<float> vtime;
	for(int q=0; q<5; q++)
	
	{
		srand(clock());

/*****************NOMBRE DE CLASSE****************
*/

		int base = 3;

/*
*************************************************/

		

		float temps_initial = 0, temps_final = 0, temps_cpu = 0;
		temps_initial = clock();

		//lecture
		int nbSommets = 0, nbAretes = 0, dmin = 0, dmax = 0, **mat1, *deg,
				**matAdj;
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

		/*Recuit*/
		int palier = 0, temp = 0, accept = 0;
		float t = 10;

		vector<int> s;
		vector<int> sprim;
		vector<int> best;

		s = rsol(base, nbSommets);
		best = s;
		/*cout << "Sol de base : ";
		for (int i = 0; i < nbSommets; ++i) {
			cout << s[i] << " ";
		}
		cout << endl;
*/
		while (palier < 10) {
			//cout << palier << endl;
			temp = 0;
			while (temp < 10000) {
				sprim = s;
				bool egal = true;
				int a, b = 0;

				while (egal) {
					a = rand() % nbSommets;
					b = rand() % nbSommets;
					egal = (s[a] == s[b]);

				}

				swap(sprim[a], sprim[b]);

				if (critmetro(
						eval(matAdj, nbSommets, sprim)
								- eval(matAdj, nbSommets, s), t)) {
					s = sprim;
					accept++;
					if (eval(matAdj, nbSommets, best)
							> eval(matAdj, nbSommets, s)) {
						best = s;
					}

				}

				temp++;
			}
			t = t * 0.9;
			palier++;
			/*if (eval(matAdj, nbSommets, s) == eval(matAdj, nbSommets, sprim))
			 palier++;
			 else
			 palier = 0;*/

		}

		
		/*ofic << "Best sol : ";
		for (int i = 0; i < nbSommets; ++i) {
			ofic << s[i] << " ";
		}
		ofic << endl;
		ofic << "Le nombre minimum d'aretes interclasse est : "
				<< eval(matAdj, nbSommets, best) << endl;

		temps_final = clock();
		//Calcul du temps d'execution:
		temps_cpu = (temps_final - temps_initial) / CLOCKS_PER_SEC * 1000;
		ofic << "Temps d'execution: " << temps_cpu << " millisecondes." << endl
				<< endl;*/
temps_final = clock();
	temps_cpu = (temps_final - temps_initial) / CLOCKS_PER_SEC * 1000;
	vtime.push_back(temps_cpu);
	vsol.push_back(eval(matAdj, nbSommets, best));
}
	ofic<<nomFichier[p]<<endl;
	int mins = vsol[0];
	int maxs = vsol[0];
	float mint= vtime[0];
	float maxt = vtime[0];
	float moyennes = vsol[0];
	float moyennet = vtime[0];
	for(int i=1; i<vsol.size();i++){
		if (mins>vsol[i]){
			mins = vsol[i];
		}
		if (maxs<vsol[i]){
			maxs = vsol[i];
		}
		if (mint>vtime[i]){
			mint = vtime[i];
		}
		if (maxt<vtime[i]){
			maxt = vtime[i];
		}
		moyennes += vsol[i];
		moyennet += vtime[i];
		
	}
	moyennes /=5;
	moyennet /=5;
	ofic<<"Meilleure solution : "<<mins<<endl;
	ofic<<"Pire solution : "<<maxs<<endl;
	ofic<<"Moyenne : "<<moyennes<<endl<<endl;
	ofic<<"Meilleure temps : "<<mint<<endl;
	ofic<<"Pire temps : "<<maxt<<endl;
	ofic<<"Moyenne : "<<moyennet<<endl<<endl;
	



	}
	return 0;
}

