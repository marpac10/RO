#ifndef GRAFO_H
#define GRAFO_H

#include <map> // per la definizione del tipo map
#include <vector> // per la definizione di vettori
#include <set> // per la definizione dei set
#include <utility>  // per la definizione del tipo pair
#include <time.h>  // per generare numeri casuali
#include <stdlib.h> // utilizzata per le funzioni rand e srand
#include <iostream> // libreria generica per cin e cout
#include <algorithm> // per ordinare gli elementi e altre funzioni di base


class Grafo
{
private:
	std::map<std::pair<int, int>, int> mappa; // insieme degli archi con associato il loro costo
	int n_vertici; // numero di vertici
	int sorgente; // vertice sorgente
	int n_archi; // numero di archi
public:
	Grafo(int, int); // costruttore con argomenti
	void inserisci_arco(int, int, int); // inserisce un arco con il costo associato nel grafo
    void stampa_grafo ();
	int calcola_costo(int, int); // calcola il costo di un arco esistente (restituisce -1 se l'arco non esiste)
	friend class Genetico; // definisco la classe Genetico come classe amica in modo tale da poter accedere agli attributi privati senza utilizzare get e set
};

#endif
