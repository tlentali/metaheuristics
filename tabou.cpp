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

pair<int, int> neighborhood(vector<int> sol, int** matAdj,
		vector<pair<int, int> > tabou) {
	vector<int> solbest(sol.size());
	vector<int> solcurrent(sol.size());
	solbest = sol;
	pair<int, int> tuple = make_pair(sol.size(), sol.size());
	pair<int, int> tuple2;
	for (int i = 0; i < sol.size(); i++) {
		for (int j = i + 1; j < sol.size(); j++) {

			tuple2 = make_pair(i, j);
			if (find(tabou.begin(), tabou.end(), tuple2) == tabou.end()) {
				solcurrent = sol;
				swap(solcurrent[i], solcurrent[j]);
				if (eval(matAdj, sol.size(), solcurrent)
						< eval(matAdj, sol.size(), solbest)) {
					solbest = solcurrent;
					tuple = make_pair(i, j);
				}
			}
		}
	}
	return tuple;
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
	ofstream ofic("tabu.dat", ios::out);

	for (int p = 0; p < 17; p++) {

		srand(clock());

vector<int> vsol;
	vector<float> vtime;
	for(int q=0; q<5; q++)
	
	{
		int base = 3;
		vector<int> sol, best, bestall;
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

		/*for (int c = 0; c < nbAretes; c++) {
		 for (int cc = 0; cc < 3; cc++) {
		 cout << mat1[c][cc] << " ";
		 }
		 cout << endl;
		 }

		 for (int d = 0; d < nbSommets; d++) {
		 cout << deg[d] << endl;
		 }*/

		float temps_initial = 0, temps_final = 0, temps_cpu = 0;
		temps_initial = clock();

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

		//Debut du tabou
		pair<int, int> tuple;
		vector<pair<int, int> > tabou;
		bestall = rsol(base, nbSommets);

		for (int i = 0; i < 20; ++i) {

			//generation solution de base aleatoire
			sol = rsol(base, nbSommets);
			/*for (int i = 0; i < nbSommets; ++i) {
			 cout<<sol[i];
			 }
			 cout<<endl;*/
			//debut de la descente dans le voisinage
			tuple = neighborhood(sol, matAdj, tabou);
			if (tuple != make_pair(nbSommets, nbSommets)
					and tuple.first != tuple.second) {
				best = sol;
				swap(best[tuple.first], best[tuple.second]);
				if (tabou.size() >= 8) {
					tabou.erase(tabou.begin());
				}
				tabou.push_back(tuple);

			}
			if (best.size() != nbSommets) {
				best = sol;
			}
			for (int j = 0; j < 50; ++j) {
				sol = best;
				tuple = neighborhood(sol, matAdj, tabou);
				if (tuple != make_pair(nbSommets, nbSommets)
						and tuple.first != tuple.second) {
					best = sol;
					swap(best[tuple.first], best[tuple.second]);
					if (tabou.size() >= 8) {
						tabou.erase(tabou.begin());
					}
					tabou.push_back(tuple);
				}
			}
			if (eval(matAdj, nbSommets, best)
					< eval(matAdj, nbSommets, bestall)) {
				bestall = best;
			}

		}
		temps_final = clock();


		/*ofic << nomFichier[p] << endl;
		ofic << "Best sol : ";
		for (int i = 0; i < nbSommets; ++i) {
			ofic << bestall[i] << " ";
		}
		ofic << endl;
		ofic << "Le nombre minimum d'aretes interclasse est : "
				<< eval(matAdj, nbSommets, bestall) << endl;
		//Calcul du temps d'execution:
		temps_cpu = (temps_final - temps_initial) / CLOCKS_PER_SEC * 1000;
		ofic << "Temps d'execution: " << temps_cpu << " millisecondes." << endl<<endl;*/

	
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

