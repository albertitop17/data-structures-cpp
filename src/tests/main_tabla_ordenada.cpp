#include <iostream>
#include "tabla_ordenada.h"


int main (int argc, char * const argv[]) {
	
	
	try {
		
		TTablaOrdenada<char,int> t;
		
		t.inserta('d',7);
		t.inserta('f',5);
		t.inserta('e',9);
		t.inserta('a',3);
		t.inserta('c',4);
		t.inserta('b',6);
		
		t.escribe();
		
		cout << endl << "Las claves de la tabla ordenada son: " << endl;
		
		TSecuenciaDinamica<char> s1;
		
		s1 = t.recorreClave();
		
		s1.escribe();
		
		cout << endl << "Los valores de la tabla ordenada por la clave son: " << endl;
		
		TSecuenciaDinamica<int> s2;
		
		s2 = t.recorre();
		
		s2.escribe();
		
		
		char clave = 'z';
		
		cout << endl << "El valor asociado a la clave " << clave << " es: " << t.consulta(clave) << endl;
		
	}
	catch( EClaveErronea3 e ) {
		
		cout << endl << endl << e.mensaje( ) << endl;
		
	}
	
	
	try {
		
		TTablaOrdenada<int,char> tabla;
	
		if ( tabla.esVacio() ) cout << endl << "La tabla SI esta vacia" << endl;
		else cout << endl << "La tabla NO esta vacia" << endl;
	
		tabla.inserta(7,'a');
		tabla.inserta(5,'b');
		tabla.inserta(9,'c');
		tabla.inserta(3,'d');
		tabla.inserta(4,'e');
		tabla.inserta(6,'f');
	
		tabla.escribe();
	
		tabla.inserta(7,'z');
		tabla.inserta(4,'v');
	
		tabla.escribe();
	
		if ( tabla.esVacio() ) cout << endl << "La tabla SI esta vacia" << endl;
		else cout << endl << "La tabla NO esta vacia" << endl;
	
		int clave1 = 4;
	
		cout << endl << "El valor asociado a la clave " << clave1 << " es: " << tabla.consulta(clave1) << endl;
	
		if ( tabla.esta(clave1) ) cout << endl << "La tabla SI contiene la clave " << clave1 << endl;
		else cout << endl << "La tabla NO contiene la clave " << clave1 << endl;
	
		int clave2 = 12;
	
		if ( tabla.esta(clave2) ) cout << endl << "La tabla SI contiene la clave " << clave2 << endl;
		else cout << endl << "La tabla NO contiene la clave " << clave2 << endl;
	
		int clave3 = 5;
	
		cout << endl << "Eliminamos el par (" << clave3 << "," << tabla.consulta(clave3) << ") en la tabla: " << endl;
	
		tabla.elimina(clave3);
	
		tabla.escribe();
	
		cout << endl << "Las claves de la tabla ordenada son: " << endl;
	
		TSecuenciaDinamica<int> sec1;
	
		sec1 = tabla.recorreClave();
	
		sec1.escribe();
	
		cout << endl << "Los valores de la tabla, ordenados por la clave, son: " << endl;
	
		TSecuenciaDinamica<char> sec2;
	
		sec2 = tabla.recorre();
	
		sec2.escribe();
	
		cout << endl;
		
		TSecuenciaDinamica< TPares<int, char>> secuenciagod;
		
		// En lugar de: cout << secuenciagod.actual();
		secuenciagod = tabla.recorrePares();
		secuenciagod.reinicia();
		TPares<int, char> p = secuenciagod.actual();
		cout << "(" << p.clave << ", " << p.valor << ")";
		secuenciagod.avanza();
		TPares<int, char> p2 = secuenciagod.actual();
		cout << "(" << p2.clave << ", " << p2.valor << ")";
		secuenciagod.avanza();
		TPares<int, char> p3 = secuenciagod.actual();
		cout << "(" << p3.clave << ", " << p3.valor << ")";
		secuenciagod.avanza();
		TPares<int, char> p4 = secuenciagod.actual();
		cout << "(" << p4.clave << ", " << p4.valor << ")";
		
		
	}
	catch( EClaveErronea3 e ) {
		
		cout << endl << endl << e.mensaje( ) << endl << endl;
		
	}
	
    return 0;
	
}