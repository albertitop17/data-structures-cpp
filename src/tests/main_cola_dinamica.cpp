#include <iostream>
#include "cola_dinamica.h"



int main (int argc, char * const argv[]) {
	
	try {
	
		TColaDinamica<char> cola;
		TColaDinamica<char> cola1;
		TColaDinamica<char> cola2;
		TColaDinamica<char> cola3;
		TColaDinamica<int> colaInts;
		
	
		cola.ponDetras('a');
		cola.ponDetras('b');
		cola.ponDetras('c');
		cola.ponDetras('d');
		//cola.escribe();
		cola.ponDetras('e');
		//cola.escribe();
		cola.ponDetras('f');
		//cola.escribe();
		cola.ponDetras('g');
		cola.ponDetras('h');
		cola.escribe();
	
		cout << endl;
		cout << "El primer elemento de la cola es: " << cola.primero();
		cout << endl;
	
		cola.quitaPrim();
	
		cola.escribe();
	
		cout << endl;
		cout << "El primer elemento de la cola es: " << cola.primero();
		cout << endl;
	
		cout << endl;
		if ( cola.esVacio() ) cout << "La cola SI esta vacia";
		else cout << "La cola NO esta vacia";
		cout << endl;
		cout << endl;
		cout << endl;
		
		cout << "EJERCICIOS HOJA 3:";
		cout << endl;
		cout << endl;
		cout << endl;
		
		cout << "Divido la siguiente cola en 2 colas:";
		cola.escribe();
		cola.dividecola(cola1,cola2);
		cout << endl;
		cout << "Cola 1:";
		cola1.escribe();
		cout << endl;
		cout << "Cola 2:";
		cola2.escribe();
		cout << endl;
		
		
		cout << "Sea la cola:";
		colaInts.ponDetras(5);
		colaInts.ponDetras(0);
		colaInts.ponDetras(2);
		colaInts.ponDetras(-1);
		colaInts.ponDetras(9);
		colaInts.ponDetras(0);
		colaInts.ponDetras(-8);
		colaInts.ponDetras(3);
		colaInts.ponDetras(0);
		colaInts.ponDetras(2);
		colaInts.ponDetras(0);
		colaInts.ponDetras(2);
		colaInts.ponDetras(6);
		colaInts.ponDetras(-4);
		colaInts.ponDetras(8);
		cout << endl;
		colaInts.escribe();	
		cout << endl;	
		cout << "Colapsamos la cola en:";
		cout << endl;
		colaInts.colapsar();
		colaInts.escribe();
		cout << endl;
			
		
	}
	catch( EAccesoIndebido e ) {
		cout << e.mensaje( );
	}
	
    return 0;
	
}
