#include <iostream>
#include "secuencia_dinamica.h"



// Programa principal para probar las secuencias


int main (int argc, char * const argv[]) {

	TSecuenciaDinamica<int> s;
	
	if ( s.esVacio( ) ) cout << "La secuencia SI es vacia" << endl;
	else cout << "La secuencia NO es vacia" << endl;
	
	s.reinicia( );
	
	s.inserta(1);
	s.inserta(2);
	s.inserta(3);
	s.escribe( );
	
	try{
		
		cout << "El elemento a continuacion del punto de interes es: " << s.actual( ) << endl;
		
	}
	catch( EDesbordamiento3 e ) {
		
		cout << endl << e.mensaje( ) << endl;
		
	}
	catch ( EAccesoIndebido3 e ) {
		
		cout << endl << e.mensaje( ) << endl;
		
	}
	
	cout << endl;
	if ( s.esFin( ) ) cout << "El punto de interes SI esta al final de la secuencia." << endl;
	else cout << "El punto de interes NO esta al final de la secuencia." << endl;
	
	s.reinicia( );
	s.escribe( );
	
	try{
		
		cout << "El elemento a continuacion del punto de interes es: " << s.actual( ) << endl;
		
	}
	catch( EDesbordamiento3 e ) {
		
		cout << endl << e.mensaje( ) << endl;
		
	}
	catch ( EAccesoIndebido3 e ) {
		
		cout << endl << e.mensaje( ) << endl;
		
	}
	
	s.avanza( );
	s.escribe( );
	
	try{
		
		cout << "El elemento a continuacion del punto de interes es: " << s.actual( ) << endl;
		
	}
	catch( EDesbordamiento3 e ) {
		
		cout << endl << e.mensaje( ) << endl;
		
	}
	catch ( EAccesoIndebido3 e ) {
		
		cout << endl << e.mensaje( ) << endl;
		
	}
	
	s.borra( );
	s.escribe( );
	
	s.inserta(8);
	s.inserta(9);
	s.escribe( );
	
	s.avanza( );
	s.escribe( );
	
	try{
		
		s.avanza( );
		
	}
	catch( EDesbordamiento3 e ) {
		
		cout << endl << e.mensaje( ) << endl;
		
	}
	catch ( EAccesoIndebido3 e ) {
		
		cout << endl << e.mensaje( ) << endl;
		
	}
	
	s.reinicia( );
	s.escribe( );
	
	s.avanza( );
	s.avanza( );
	s.escribe( );
	
	s.borra( );
	s.borra( );
	s.escribe( );
	
	try{
		
		s.borra( );
		
	}
	catch( EDesbordamiento3 e ) {
		
		cout << endl << e.mensaje( ) << endl;
		
	}
	catch ( EAccesoIndebido3 e ) {
		
		cout << endl << e.mensaje( ) << endl;
		
	}
	
	s.reinicia( );
	s.escribe( );
	
    return 0;
    
}