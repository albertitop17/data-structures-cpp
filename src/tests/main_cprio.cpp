#include <iostream>
#include "cprio.h"


int main (int argc, char * const argv[]) {
	
	TCPrio<int> cp(10);
	
	cp.anyade(4);
	cp.anyade(3);
	cp.anyade(7);
	cp.anyade(1);
	cp.anyade(6);
	cp.anyade(5);
	cp.anyade(2);
	cp.anyade(8);
	cp.anyade(9);
	
	cout << "La cola de prioridad (de minimos) es: " << endl << endl << cp << endl;
	cout << endl << "El minimo de la cola de prioridad es: " << endl << endl << cp.min() << endl;
	cout << endl << "La altura de la cola de prioridad es: " << endl << endl << cp.altura() << endl;
	cout << endl << "Quitamos el minimo de la cola de prioridad: " << endl ;
	cp.quitaMin();
	cout << endl << cp << endl;
	
	if ( cp.esVacio( ) ) cout << endl << "La cola SI es vacia" << endl << endl;
	else cout << endl << "La cola NO es vacia" << endl << endl;
	
	int n = 10;
	
	int vector[n];
	
	vector[0] = 2;
	vector[1] = 8;
	vector[2] = 6;
	vector[3] = 7;
	vector[4] = 0;
	vector[5] = 4;
	vector[6] = 9;
	vector[7] = 1;
	vector[8] = 3;
	vector[9] = 5;
	
	cout << endl << "heapsort" << endl;
	
	for( int i = 0; i < n; i++ ) cout << vector[i] << " ";
	
	heapsort(vector, n);
	
	cout << endl << endl;
	
	for( int i = 0; i < n; i++ ) cout << vector[i] << " ";
	
	cout << endl << endl;
	
	
	if(cp.buscar(2)) cout <<"El 2 esta en la cola"<< endl;
	else cout << "El 2 no esta en la cola";
	if (cp.buscar(13) ) cout <<"El 13 esta en la cola"  << endl;
	else cout << "El 13 no esta en la cola"<< endl;
	
	cp.anyade(13);
	cout << endl << "Anyadimos el 13 a la cola"<< endl;
	if (cp.buscar(13) ) cout <<"El 13 esta en la cola"  << endl;
	else cout << "El 13 no esta en la cola"<< endl;
		
	cout << cp;	
		
	cp.eliminar (5);
	
	cout << endl << "El montiuclo sera: " << cp << endl;
	
	cout<< "Ahora anadimos varios 7"<<endl;
	cp.anyade(7);
	cp.anyade(7);
	cp.anyade(7);
	cp.anyade(7);
	cp.anyade(7);
	cp.anyade(7);
	cout<<cp;
	cout << endl;
	cp.eliminar_todos(7);
	cout << endl << "El montiuclo eliminando todos los 7: " << cp << endl;
	
	cout << endl;
	cp.podar(5);
	cout << endl << "Podo los elementos menores a 5: " << endl << cp << endl;
	
	
	
    return 0;

}