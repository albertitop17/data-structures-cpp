#include <iostream>
#include "lista_dinamica.h"


int main (int argc, char * const argv[]) {
   
	TListaDinamica<int> l;
	
	l.ponDetras(3);
	l.ponDetras(4);
	//l.escribe( );
	l.ponDelante(2);
	l.ponDelante(2);
	l.ponDelante(2);
	l.ponDelante(1);
	//l.escribe( );
	l.eliminar(2);
	l.escribe();
	TListaDinamica<int> m;
	m.ponDelante(6);
	m.ponDelante(5);
	m.escribe( );
	cout << endl;
	cout << "Concatenar:";
	cout << endl;
	l.concatena(m);
	l.escribe( );
	
	
	int n = 3;
	cout << endl << "El elemento de la lista en la posicion " << n << " es: " << l.elemEn(n) << endl;
	
	try{
		
		cout << "El ultimo elemento de la lista es: " << l.ultimo( ) << endl;
		
	}	
	
	catch( EDesbordamiento e ) {
		
		cout << endl << e.mensaje( ) << endl;
		
	}
	catch ( EAccesoIndebido e ) {
		
		cout << endl << e.mensaje( ) << endl;
		
	}
	cout << endl;
	cout << endl;	
	cout << "EJERCICIOS HOJA 3.2";
	cout << endl;
	cout << endl;
	l.eliminar(3);
	l.eliminar(4);
	l.eliminar(5);
	l.escribe();
	cout << endl;
	cout << "Es la lista anterior palindroma? " << (l.palindroma() ? "True" : "False") << endl;
	l.ponDelante(6);
	l.ponDelante(7);
	l.ponDetras(7);
	l.escribe();
	cout << endl;
	cout << "Es la lista anterior palindroma? " << (l.palindroma() ? "True" : "False") << endl;
	
	l.quitaUlt( );
	l.quitaUlt( );

	l.ponDelante(2);
	l.ponDelante(12);
	l.ponDetras(31);
	l.ponDetras(-51);
	l.ponDetras(31);
	l.ponDelante(-22);
	l.ponDelante(2);
	l.ponDelante(-2);
	cout << endl;	
	cout << endl;
	cout << "Dada la siguiente lista:";
	cout << endl;
	l.escribe();
	cout << endl;
	cout << "Ordenando mediante quicksort:";
	cout << endl;
	l.quicksort();
	l.escribe();
	cout << endl;
	cout << endl;
	
	int casos;   
	cout << "Ejercicio 3: Eliminar todas las apariciones de un elemento en una lista:";
	cout << endl;
	cout << endl;
	cout << "Introduce el numero de casos que quieras probar:";
	cin >> casos;
	cout << endl;
	
	for (int i = 0; i < casos; i++){
		TListaDinamica<int> aux;
		cout << "Dime los elementos de la lista: ";
		int elemento;
		cin >> elemento;
		while (elemento != -1){
			aux.ponDetras(elemento);
			cin>> elemento;
		}
		cout << "Dime el elemento que quieres eliminar: ";
		int eliminado;
		cin >> eliminado;
		aux.eliminar(eliminado);
		aux.escribe();
		cout << endl;
	}

	/*
	try{
		
		l.quitaUlt( );
		
	}
	catch( EDesbordamiento e ) {
		
		cout << endl << e.mensaje( ) << endl;
		
	}
	catch ( EAccesoIndebido e ) {
		
		cout << endl << e.mensaje( ) << endl;
		
	}	
	try{
		
		l.ultimo( );
		
	}
	catch( EDesbordamiento e ) {
		
		cout << endl << e.mensaje( ) << endl;
	}
	catch ( EAccesoIndebido e ) {
		
		cout << endl << e.mensaje( ) << endl;
		
	}
	cout << endl;
    return 0;
    */
    
}