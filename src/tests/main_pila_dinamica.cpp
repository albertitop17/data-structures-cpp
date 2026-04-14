#include <iostream>
#include "pila_dinamica.h"



int main (int argc, char * const argv[]) {
	
	TPila<char> pila;
	TPila<char> pila1;
	TPila<char> pila2;
	TPila<char> pila3;
	TPila<char> pila4;
	TPila<char> pila5;
	TPila<char> pila6;
	TPila<int> pila7;
	try {
		/*
		cout << endl;
		if ( pila.esVacio() ) cout << "Pila vacia";
		else cout << "Pila NO vacia";
		cout << endl;
		*/
		pila.apila('a');
		pila.apila('b');
		pila.apila('c');
		pila.apila('d');
		pila.apila('e');
		pila.apila('f');
		pila.escribe();
		
		cout << endl;
		cout << "La cima de la pila es: " << pila.cima();
		cout << endl;
		cout << "El fondo de la pila es: " << pila.fondo();
		cout << endl;
		cout << endl;
		
		pila1.apila('1');
		pila1.apila('2');
		pila1.apila('3');
		
		cout << "Pila 1:";
		pila1.escribe();
		cout << endl;
		
		pila2.apila('4');
		pila2.apila('5');
		pila2.apila('6');
		
		cout << "Pila 2:";
		pila2.escribe();
		cout << endl;
		
		cout << "Concatenar pila 1 y pila 2 ";
		pila1.concatenar(pila2);
		pila1.escribe();
		
		cout << endl;
		cout << "La cima de la pila es: " << pila1.cima();
		cout << endl;
		cout << "El fondo de la pila es: " << pila1.fondo();
		cout << endl;
		cout << endl;
		pila1.inversa();
		cout << "La inversa de la pila es: ";
		pila1.escribe();
		cout << endl;
		cout << "La nueva cima de la pila es: " << pila1.cima();
		cout << endl;
		cout << "El nuevo fondo de la pila es: " << pila1.fondo();
		cout << endl;
	
		cout << endl;
		cout << "La pila duplicada sera:";
		cout << endl;
		pila1.duplicar();
		pila1.escribe();
		cout << endl;
		
		pila3.apila('s');
		pila3.apila('t');
		pila3.apila('e');
		pila3.apila('r');
		pila3.apila('p');

		pila4.apila('o');
		pila4.apila('c');
		pila4.apila('f');
		pila4.apila('e');
		cout << "Pila3: ";
		pila3.escribe();
		cout << endl;
		cout << "Pila4: ";
		pila4.escribe();
		cout << endl;
		cout << "Entremezclar Pila3 y Pila4";
		cout << endl;
		pila3.entremezclar(pila4);
		pila3.escribe();
		cout << endl;
	
		pila5.apila('1');
		pila5.apila('3');
		pila5.apila('5');
		cout << "Pila5: ";
		pila5.escribe();
		cout << endl;
		pila6.apila('2');
		pila6.apila('4');
		cout << "Pila6: ";
		pila6.escribe();
		cout << endl;
		cout << "Entremezclar Pila5 y Pila6";
		pila5.entremezclar(pila6);
		pila5.escribe();
		
		pila5.borrar();
		
		/*
		cout << endl;
		if ( pila5.esVacio() ) cout << "Pila vacia";
		else cout << "Pila NO vacia";
		cout << endl;
		*/
		/*
		pila7.apila(3);
		pila7.apila(2);
		pila7.apila(3);
		pila7.apila(4);
		pila7.apila(6);
		pila7.apila(8);
		pila7.apila(7);
		pila7.apila(4);
		pila7.apila(67);
		pila7.escribe();
		cout << endl;
		pila7.pares();
		pila7.escribe();
	*/
	}
	catch ( EAccesoIndebido e ) {
		
		cout << e.mensaje();
		
	}
	
	
	return 0;
	
}
/*
	
	*/