#include "genetico.h"

using namespace std;

Genetico::Genetico(Grafo* g, int ind, int num_it, int prob_mut) {
	if(ind == 0) 
	{
		cout << "Inserisci una popolazione con un numero massimo di almeno 1 individuo\n";
		exit(1);
	}
	if(prob_mut < 0 || prob_mut > 100)
	{
		cout << "Inserisci una probabilità di mutazione compresa tra 0 e 100";
		exit(1);
	}
	if (g->n_archi!=(g->n_vertici-1)*(g->n_vertici)) {
		cout << "Inserisci un grafo pieno";
		exit(1);
	}
	
	this->grafo = g;
	this->n_iterazioni = num_it;
	this->prob_mutazione = prob_mut;
	this->n_individui = ind;
}

void Genetico::genera_popolazione() {
		
	vector<int> primo;
	
	int cont,temp,a,b; 
	primo.push_back(grafo->sorgente); 
	for(int i=0; i<grafo->n_vertici; i++) {
		if(i != grafo->sorgente)
			primo.push_back(i);
	}
		int costo = calcola_costo(primo);
	if(costo != -1) {
		popolazione.push_back(make_pair(primo, costo)); 
		cont++; 
	}
		
		while (n_individui!=cont) {
		for (int j=0;j<grafo->n_vertici;j++) {
		do {
		 a = rand() % (grafo->n_vertici-1) +1;
		 b = rand() % (grafo->n_vertici-1) +1;
	} while (a==b);
	
	temp=primo[a];
	primo[a]=primo[b];
	primo[b]=temp;
}
		
	int costo = calcola_costo(primo); 
			
		if(costo != -1 && !genotipo_presente(primo))
		{
			popolazione.push_back(make_pair(primo, costo)); 
			cont++;
		}
	}
	
	
	sort(popolazione.begin(), popolazione.end(), ordinamento()); 
}


bool Genetico::soluzione_ammissibile(std::vector<int>& sol) {
	set<int> soluzione; // gli elementi di un set devono essere unici, se un elemento è duplicato l'insert non viene effettuato e posso quindi verificare
	int n=grafo->n_vertici; // mi salvo il numero di vertici del grafo
	for(int i=0; i<n; i++)
		soluzione.insert(sol[i]);
	
	if(soluzione.size() < n) return false; // modifica!

	for(int i=0; i<n-1; i++)
	{
			if(grafo->calcola_costo(sol[i], sol[i+1]) == -1) return false;
		}
	
			if(grafo->calcola_costo(sol[n-1], sol[0])==-1) return false;

	
	return true;
}

int Genetico::calcola_costo(std::vector<int>& sol) {
	int n=grafo->n_vertici;
	int costo = 0;
	if (this->soluzione_ammissibile(sol) == false) return -1;
	for (int i=0; i<n-1; i++) {
		costo = costo + grafo->calcola_costo(sol[i], sol[i+1]);
	}
	costo = costo + grafo->calcola_costo(sol[n-1], sol[0]);
	return costo;
}

bool Genetico::genotipo_presente(const std::vector<int> & sol) {
	vector<genotipo>::iterator i; // definisco un iteratore per ricercare all'interno della popolazione
		for(i=popolazione.begin(); i!=popolazione.end(); i++)
	{
		const vector<int>& trovato = (*i).first; 
		if(equal(sol.begin(), sol.end(), trovato.begin())) // confronto i vettori, metodo equal vuole in ingresso questi 3 parametri
			return true;
	}
	return false;
}

void Genetico::stampa_popolazione () {
	vector<genotipo>::iterator i;
	int n=grafo->n_vertici;
		cout << "Numero di individui della popolazione: " << n_individui << endl;
	for(i=popolazione.begin(); i!=popolazione.end(); i++)
	{
			const vector<int>& v = (*i).first;
		
		for(int j=0; j<n; j++) 
		cout << v[j] << " ";
		cout << grafo->sorgente; // per chiudere il ciclo hamiltoniano
		cout << " -> Costo: " << (*i).second << endl;
	}

}

void Genetico::inserisci_figlio(std::vector<int>& v, int c) {
	int i=0;
	int n=n_individui;
	while (popolazione[i].second<c && i<n) i++;
	popolazione.insert(popolazione.begin() + i, make_pair(v,c));
}

int Genetico::crossover(std::vector<int>& genitore1, std::vector<int>& genitore2) {
		int n=grafo->n_vertici;
		int figlio1[n],figlio2[n]; // figli
		vector<int> f1, f2;
		int cp1, cp2;
	    int corr1[n], corr2[n]; // vettori di corrispondenze per vedere se un elemento è gia presente
	    int inseriti=0; // verifico quanti figli genero
	for(int i=0; i<n; i++)
	{	
		corr1[i] = -1;
		corr2[i] = -1;
	}
	do {
	cp1 = rand() % (n-2) + 1; // cross point 1 random tra 1 e n-2
	cp2 = rand() % (n-cp1) + cp1; // cross point 2 random tra cp1 e n-1 (sicuro maggiore uguale, ma devo evitare sia uguale)
} while (cp1==cp2); // e cosi evito siano uguali

//cout <<  "punti di crossover " << cp1 << cp2 << endl;
	
	for(int i=cp1; i<cp2; i++) {
			figlio1[i] = genitore2[i];
			figlio2[i] = genitore1[i];
			corr1[genitore2[i]] = genitore1[i];
			corr2[genitore1[i]] = genitore2[i];     // situazione bug 52341678 - 34578126 - scambio i 4 centrali
		}
	/*	cout << "corrispondenza1:\n" ;
		for (int i=0; i<n; i++) {
			cout << corr1[i] << " " ;
		}
			
			cout << "\ncorrispondenza2:\n" ;
		for (int i=0; i<n; i++) {
			cout << corr2[i] << " " ;
		}  */
		
		int pos,x; // posizione che varia per trovarne una corretta
		bool ok; // per verificare se posso inserire quel valore
	
	for (int i=0; i<cp1; i++) {
			pos=corr1[genitore1[i]];
			ok=true;
		while (pos!=-1) {
		ok=false;
		x=pos;
		pos=corr1[x];
	}
		if (ok) figlio1[i]=genitore1[i];
		else figlio1[i]=x;
		}
	
	for (int i=0; i<cp1; i++) {
			pos=corr2[genitore2[i]];
			ok=true;
		while (pos!=-1) {
		ok=false;
		x=pos;
		pos=corr2[x];
	}
		if (ok) figlio2[i]=genitore2[i];
		else figlio2[i]=x;
		}
	
	for (int i=cp2; i<n; i++) {
			pos=corr1[genitore1[i]];
			ok=true;
		while (pos!=-1) {
		ok=false;
		x=pos;
		pos=corr1[x];
	}
		if (ok) figlio1[i]=genitore1[i];
		else figlio1[i]=x;
		}
		
	for (int i=cp2; i<n; i++) {
			pos=corr2[genitore2[i]];
			ok=true;
		while (pos!=-1) {
		ok=false;
		x=pos;
		pos=corr2[x];
	}
		if (ok) figlio2[i]=genitore2[i];
		else figlio2[i]=x;
		}
/*	
		cout << "\n figlio1 pre mutazione \n" ;
	for (int i=0;i<n;i++) {
		cout << figlio1[i] << " " ;
	}
	cout << "\n figlio 2 pre mutazione \n" ;
		for (int i=0;i<n;i++) {
		cout << figlio2[i] << " " ;
	} */

		// ora mutazione
	int prob = rand() % 100 + 1; // genero un numero da 1 a 100 per la probabilità
	//cout << "\nprobabilita scelta " << prob;
	if(prob <= prob_mutazione)  
	{
		
		int gene1, gene2;
		do {
		gene1 = rand() % (n-1) + 1;
		gene2 = rand() % (n-1) + 1;
	} while (gene1==gene2);
	//	cout << "\nscambio i geni " << gene1 << " e " << gene2 << "\n" ;
		
		int temp = figlio1[gene1];
		figlio1[gene1] = figlio1[gene2];
		figlio1[gene2] = temp;
		
		temp = figlio2[gene1];
		figlio2[gene1] = figlio2[gene2];
		figlio2[gene2] = temp;
	}
	
	for (int i=0;i<n;i++) {
		f1.push_back(figlio1[i]);
		f2.push_back(figlio2[i]);
	}
/*	cout << "\n figlio1 post mutazione \n" ;
	for (int i=0;i<n;i++) {
		cout << f1[i] << " " ;
	}
	cout << "\n figlio 2 post mutazione \n" ;
		for (int i=0;i<n;i++) {
		cout << f2[i] << " " ;
	}
	*/
	int costo1 = calcola_costo(f1);
	int costo2 = calcola_costo(f2);
	if(costo1 != -1 && !genotipo_presente(f1))
	{
		inserisci_figlio(f1, costo1); 
		inseriti++;
	}
	
	if(costo2 != -1 && !genotipo_presente(f2))
	{
		inserisci_figlio(f2, costo2);
		inseriti++;
	}
	
	return inseriti;
}


int Genetico::start() {
	int n=grafo->n_vertici;	
	
	genera_popolazione(); // genero la popolazione iniziale
	
//	cout << "terminata la popolazione iniziale!" << endl;
	int iterazioni = 0;
	int stop = 0;

	for(int i = 0; i < n_iterazioni; i++)
	{
				
		int genitore1, genitore2;
			
		simulazione_montecarlo(genitore1,genitore2);
		int x = crossover(popolazione[genitore1].first, popolazione[genitore2].first);
			
			 
		for (int j=0;j<x;j++) popolazione.pop_back();
			
			iterazioni++; // conto il numero di iterazioni fatte
			if (x==0) stop++; // se per 20 iterazioni non faccio figli convergenza e esco
			else stop=0;
			
			if (stop==20) break;
	
	}
	
	cout << "Numero iterazioni completate : " << iterazioni << endl;
	cout << "Soluzione migliore calcolata: \n";
	const vector<int>& v = popolazione[0].first;
	for(int i=0; i<n; i++)
		cout << v[i] << " ";
	cout << grafo->sorgente;
	cout << " -> Costo: " << popolazione[0].second;
	
	return popolazione[0].second;

}


void Genetico::simulazione_montecarlo(int& genitore1, int& genitore2) {
	float F=0.0;
	vector<genotipo>::iterator i;
	for(i=popolazione.begin(); i!=popolazione.end(); i++)
	{
		F=F+(1.0/(*i).second);
	//	cout << "\nAttuale valore di F : " << F << endl; 
}
	float fitness_cumulata[n_individui];
	int j=0;
	float tot_fitness=0.0;
	for(i=popolazione.begin(); i!=popolazione.end(); i++) {
		fitness_cumulata[j]=((1.0/(*i).second) + tot_fitness)/F;
		tot_fitness= tot_fitness + (1.0/(*i).second);
	//	cout << "\n Fitness cumulata dell'elemento " << j << " = " << fitness_cumulata[j] << " fitness totale finora = " << tot_fitness << endl;
		j++;
	}
	float a = float(rand() % 1000)/ 1000.0;
	float b = float(rand() % 1000)/ 1000.0;
	// cout << "a = " << a << " b = " << b << endl;
	int k=0;
   while (k<n_individui && fitness_cumulata[k]<a) k++;
   genitore1=k;
  // cout << "genitore 1 = " << genitore1 << endl;
   k=0;
   while (k<n_individui && fitness_cumulata[k]<b) k++;
   genitore2=k;
  // cout << "genitore 2 = " << genitore2 << endl;
   if (genitore2==genitore1) {
   	if (genitore2>n_individui/2) genitore2--;
   	else genitore2++;
   }
   //cout << "Se erano uguali: ora sono genitore 1 = " << genitore1 << " e genitore 2 = " << genitore2 << endl;
}
