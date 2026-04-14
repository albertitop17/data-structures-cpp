#include "tabla_abierta.h"
#include <iostream>


int main (int argc, char * const argv[]) {
	
	try {
		
		TTablaAbierta<string,float> tabla;
	
		if ( tabla.esVacio() ) cout << endl << "La tabla SI esta vacia" << endl;
		else cout << endl << "La tabla NO esta vacia" << endl;
	
		tabla.inserta("Rafael",  9.75);
		tabla.inserta("Carlos",  6.55);
		tabla.inserta("Maria",   7.25);
		tabla.inserta("Juan",    3.24);
		tabla.inserta("Raquel",  0.75);
		tabla.inserta("Raul",    3.25);
		tabla.inserta("Laura",   5.00);
		tabla.inserta("David",   4.35);
		tabla.inserta("Roberto", 1.55);
		tabla.inserta("Alicia",  8.00);
		tabla.inserta("Nuria",   6.75);
		tabla.inserta("Jose",    4.85);
		tabla.inserta("Pilar",   7.75);

		tabla.escribe();
	
		if ( tabla.esVacio() ) cout << "La tabla SI esta vacia" << endl;
		else cout << "La tabla NO esta vacia" << endl;
		
		string clave1 = "Juan";
	
		if ( tabla.esta(clave1) ) cout << endl << "La clave " << "'" << clave1 << "'" << " SI esta en la tabla" << endl;
		else cout << "La clave " << "'" << clave1 << "'" << " NO esta en la tabla" << endl;
		
		string clave2 = "Roger";

		if ( tabla.esta(clave2) ) cout << endl << "La clave " << "'" << clave2 << "'" << " SI esta en la tabla" << endl;
		else cout << "La clave " << "'" << clave2 << "'" << " NO esta en la tabla" << endl;
	
		string nombre = "Raquel";
		cout << endl << "El valor asociado a la clave " << "'" << nombre << "'" << " es: " << tabla.consulta(nombre) << endl;
	
		cout << endl << "Borramos la clave " << "'" << nombre << "'" << " de la tabla: " << endl;
		
		tabla.borra(nombre);
		
		tabla.escribe();
		
		cout << endl << "El valor asociado a la clave " << "'" << nombre << "'" << " es: " << tabla.consulta(nombre) << endl;
		
	}
	catch( EClaveErronea2 e ) {
		
		cout << e.mensaje( ) << endl;
		
	}
	
	try {
		
		TTablaAbierta<string,float> tabla;
		
		tabla.inserta("Rafael",  9.75);
		tabla.inserta("Carlos",  6.55);
		tabla.inserta("Maria",   7.25);
		tabla.inserta("Juan",    3.24);
		tabla.inserta("Raquel",  0.75);
		tabla.inserta("Raul",    3.25);
		tabla.inserta("Laura",   5.00);
		tabla.inserta("David",   4.35);
		tabla.inserta("Roberto", 1.55);
		tabla.inserta("Alicia",  8.00);
		tabla.inserta("Nuria",   6.75);
		tabla.inserta("Jose",    4.85);
		tabla.inserta("Pilar",   7.75);
		
		cout << endl << "Creamos una tabla vacia: " << endl;
		
		TTablaAbierta<string,float> tabla_copia;
		
		tabla_copia.escribe();
		
		cout << "Hacemos una copia de la tabla: " << endl;
		
		tabla_copia.copia(tabla);
		
		tabla_copia.escribe();
		
	}	
	catch( EClaveErronea2 e ) {
			
			cout << e.mensaje( ) << endl << endl;
			
	}
		
	
    return 0;
	
}
