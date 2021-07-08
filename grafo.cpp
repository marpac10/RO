#include "grafo.h"

using namespace std;

Grafo::Grafo(int n_vertici, int sorgente) {
	if (n_vertici==0) {
		cout << "Inserisci un numero di vertici maggiore di 0 \n" ;
		exit(1);
	}
	this->n_vertici = n_vertici;
	this->sorgente = sorgente;
	this->n_archi = 0;
	cout << "Grafo inizializzato correttamente \n";
}

void Grafo::inserisci_arco(int a, int b, int costo) {
	mappa[make_pair(a,b)] = costo;
	n_archi++;
}

int Grafo::calcola_costo(int a, int b) {
	map<pair<int, int>,int>::iterator i = mappa.find(make_pair(a, b)); 
	if(i == mappa.end()) return -1;
		return i->second; 
}

void Grafo::stampa_grafo() {
	map<pair<int, int>, int>::iterator i;
	cout << "Il grafo ha " << n_vertici << " vertici e " << n_archi << " archi \n" ;
	cout << "Il vertice iniziale e' " << sorgente << endl;
	for(i = mappa.begin(); i != mappa.end(); i++)
		cout << "Nel grafo e' presente l'arco (" << i->first.first << "," << i->first.second <<") con costo "  << i->second << endl;
	
}

