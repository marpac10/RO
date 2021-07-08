#include <iostream>
#include "grafo.h"
#include "genetico.h"
#include <sys/time.h>
#include <math.h>
#include <cstring>
#include <fstream>
using namespace std;

int main(int argc, char** argv) {
	
	srand(time(NULL));
	
	int z, ottimo, n;
	ifstream myfile;
	char nome_file[100];
	char tipo = 'r';
	cout << "Inserisci il nome del file da aprire : " ;
	cin.getline (nome_file,100);
	myfile.open(nome_file,ios::in);
	if (!myfile) {
	    cout << "Impossibile aprire il file!!" << endl;
		exit (1);
	}
	else cout << "Apertura file in corso.." << endl;
	
	myfile >> n; // lettura della dimensione
	myfile >> tipo; // lettura del tipo di dati
	myfile >> ottimo; // soluzione ottima per quel problema
	
	Grafo* g = new Grafo(n, 0);
	
	cout << endl << endl;
	
	if (tipo=='r') { // random
		
			for (int i=0;i<20;i++) {
		for (int j=0;j<20;j++) {
			if (i!=j) g->inserisci_arco(i,j,rand()%20);
		}
	}
}
		
	if (tipo=='c') {  // completa
	for (int i=0;i<n;i++) {
		for (int j=0;j<n;j++) {
			myfile >> z;
			if ((i!=j)) {
			g->inserisci_arco(i,j,z);
		}
	}
}
}
		
		
		if (tipo=='u') // upper row
		for (int i=0;i<n;i++) {
		for (int j=0;j<n;j++) {
		
			if ((i!=j)) {
				if (g->calcola_costo(j,i)==-1) {
					myfile >> z;
			g->inserisci_arco(i,j,z);
		}
		else g->inserisci_arco(i,j,g->calcola_costo(j,i));
		}
}
}

	if (tipo=='p')  {//posizione dei nodi 
	int x[n];
	int y[n];
	
	for (int i=0;i<n;i++) {
			myfile >> z;
			myfile >> x[i];
			myfile >> y[i];
		}
	for (int i=0;i<n;i++) {
		for (int j=0;j<n;j++) {
			if (i!=j) g->inserisci_arco(i,j,sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[j]-y[j])));
		}
	}
		
	}



	myfile.close();
	

	
//	g->stampa_grafo();
	
	Genetico gen(g,500,100000,20);

	
	timeval start, stop;
double elapsedTime;

gettimeofday(&start, NULL);

  int sol= gen.start();
   
gettimeofday(&stop, NULL);

elapsedTime = (stop.tv_sec - start.tv_sec) * 1000.0;               // sec to ms
elapsedTime += (stop.tv_usec - start.tv_usec) / 1000.0;            // us to ms
   
   	cout << "\nSoluzione ottima : " << ottimo << endl;
	cout << "Errore assoluto : " << sol-ottimo << endl;
	cout << "Errore percentuale : " << (float)((sol-ottimo)*100.0)/ottimo << " % " ;
	
cout  << "\nIl tempo di esecuzione e' :  " << elapsedTime << " ms.\n";
     
	
	return 0;
}
