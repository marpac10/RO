#ifndef GENETICO_H
#define GENETICO_H

#include <map> // per la definizione del tipo map
#include <vector> // per la definizione di vettori
#include <set> // per la definizione dei set
#include <utility>  // per la definizione del tipo pair
#include <time.h>  // per generare numeri casuali
#include <stdlib.h> // utilizzata per le funzioni rand e srand
#include <iostream> // libreria generica per cin e cout
#include <algorithm> // per ordinare gli elementi e altre funzioni di base
#include "grafo.h"

typedef std::pair<std::vector<int>, int> genotipo; // definisco il genotipo come una coppia vettore (insieme dei geni) e fitness associata

class Genetico
{
private:
	Grafo* grafo; // il grafo associato all'algoritmo genetico
	std::vector<genotipo> popolazione; // un vettore di genotipi definisce l'intera popolazione che evolverà durante l'algoritmo 
	int n_individui; // numero di individui della popolazione
	int n_iterazioni; 
	int prob_mutazione; // intero che indica la probabilità in percentuale di avere una mutazione
public:
	void genera_popolazione(); // genera la popolazione dal quale parte il nostro algoritmo
	Genetico(Grafo*, int, int, int); // costruttore con argomenti
	bool soluzione_ammissibile(std::vector<int>&); // verifica se una soluzione è ammissibile
	int calcola_costo(std::vector<int>&); // calcola il costo di una soluzione
	bool genotipo_presente(const std::vector<int> &); // verifica se un dato genotipo in ingresso è gia presente nella soluzione
	void stampa_popolazione(); // stampa la popolazione attuale
	void inserisci_figlio(std::vector<int>&, int); // inserisci figlio generato nella popolazione in ordine crescente di costo
	int crossover(std::vector<int>&, std::vector<int>&); // operatore di crossover
	void simulazione_montecarlo(int&, int&);
	int start(); // Avvia l'algoritmo
};


struct ordinamento
{
	bool operator()(const genotipo& firstElem, const genotipo& secondElem)
	{
		return firstElem.second < secondElem.second;
	}
};













#endif
