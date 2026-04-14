#include <iostream>
#include "arbin.h"


int main (int argc, char * const argv[]) {
	
	try {
		
		TArbinDinamico<int> b1; //LO CREO POR DEFECTO (ES VACIO)
		
		if ( b1.esVacio() ) cout << "El arbol SI es vacio";
		else cout << "El arbol NO es vacio";
		cout << endl;
		
		cout << endl << "La raiz del arbol es: " << b1.raiz() << endl << endl;
		
	}
	catch( EAccesoIndebido3 e ) {
		
		cout << endl << e.mensaje( ) << endl << endl;
		
	}
	
	try {
		
		TArbinDinamico<int> b2;
		
		if ( b2.esVacio() ) cout << "El arbol SI es vacio";
		else cout << "El arbol NO es vacio";
		cout << endl;
		
		(b2.hijoIz()).escribe();
		
	}
	catch( EAccesoIndebido3 e ) {
		
		cout << endl << e.mensaje( ) << endl << endl;
		
	}
	
	try {
		
		TArbinDinamico<int> b3;
		
		if ( b3.esVacio() ) cout << "El arbol SI es vacio";
		else cout << "El arbol NO es vacio";
		cout << endl;
		
		(b3.hijoDr()).escribe();
		
	}
	catch( EAccesoIndebido3 e ) {
		
		cout << endl << e.mensaje( ) << endl << endl;
		
	}
	
	try {
		
		//CONSTRUYO EL ÁRBOL 7 - 5  3 - X X 2 1
		
		//CREO LA HOJA 1.1
		TArbinDinamico<int> a11;
		TArbinDinamico<int> a12;
		TArbinDinamico<int> arbol1(a11,5,a12);									
		
		//CREO LA HOJA 1.2.1
		TArbinDinamico<int> a211;
		TArbinDinamico<int> a212;
		TArbinDinamico<int> arbol21(a211,2,a212);
	
		//CREO LA HOJA 1.2.2
		TArbinDinamico<int> a221;
		TArbinDinamico<int> a222;
		TArbinDinamico<int> arbol22(a221,1,a222);
		
		//CREO EL NODO 1.2
		TArbinDinamico<int> arbol2(arbol21,3,arbol22);
	
		//CREO LA RAIZ 1
		TArbinDinamico<int> arbol(arbol1,7,arbol2);
		
		if ( arbol.esVacio() ) cout << "El arbol SI es vacio";
		else cout << "El arbol NO es vacio";
		cout << endl;
	
		cout << endl << "El arbol es:" << endl;
	
		arbol.escribe();
	
		cout << endl << "La raiz del arbol es: " << arbol.raiz() << endl;
	
		cout << endl << "El hijo izquierdo del arbol es:" << endl;
	
		(arbol.hijoIz()).escribe();
	
		cout << endl << "El hijo derecho del arbol es:" << endl;
	
		(arbol.hijoDr()).escribe();
	
		cout << endl << "El recorrido en pre-orden del arbol es:" << endl;
	
		TSecuenciaDinamica<int> sec1;
	
		sec1 = arbol.preOrd();
	
		sec1.escribe();
	
		cout << endl << "El recorrido en post-orden del arbol es:" << endl;
	
		TSecuenciaDinamica<int> sec2;
	
		sec2 = arbol.postOrd();
	
		sec2.escribe();
	
		cout << endl << "El recorrido en in-orden del arbol es:" << endl;
	
		TSecuenciaDinamica<int> sec3;
	
		sec3 = arbol.inOrd();
	
		sec3.escribe();
		
		cout << endl;
		
		cout<< "EL numero de hojas del arbol es: ";
		
		cout<< arbol.numHojas();
		
		cout << endl << endl;
		cout<< "Del arbol: "<< endl;
		arbol.escribe();
		cout << endl << endl;
		cout <<"Su espejo: "<<endl;
			
		arbol.espejo();
		
		arbol.escribe();
		
		cout << endl << endl;
		cout << endl << endl;
	
		TSecuenciaDinamica<int> sec33;
			
		sec33 = arbol.frontera();
		
		cout << endl;
		
		cout<< "La frontera es:  ";
		cout<< endl;
		
		sec33.escribe();
		
		TSecuenciaDinamica<int> sec34;
		
		sec34 = arbol.ramaMasLarga();
		
		cout << endl;
		
		cout<< "La rama mas larga es:  ";
		cout<< endl;
		
		sec34.escribe();
		
		TSecuenciaDinamica<int> sec35;
		
		sec35 = arbol.nivelN(0);
		
		cout << endl;
		
		cout<< "El nivel 0 del arbol es:  ";
		cout<< endl;
		
		sec35.escribe();
		
		TSecuenciaDinamica<int> sec36;
		
		sec36 = arbol.nivelN(1);
		
		cout << endl;
		
		cout<< "El nivel 1 del arbol es:  ";
		cout<< endl;
		
		sec36.escribe();
		
		TSecuenciaDinamica<int> sec37;
		
		sec37 = arbol.nivelN(2);
		
		cout << endl;
		
		cout<< "El nivel 2 del arbol es:  ";
		cout<< endl;
		
		sec37.escribe();
		
		TSecuenciaDinamica<int> sec38;
		
		sec38 = arbol.nivelN(3);
		
		cout << endl;
		
		cout<< "El nivel 3 del arbol es:  ";
		cout<< endl;
		
		sec38.escribe();
		
		
		TSecuenciaDinamica<int> sec39;
		
		sec38 = arbol.nivelN(4);
		
		cout << endl;
		
		cout<< "El nivel 4 del arbol es:  ";
		cout<< endl;
		
		sec39.escribe();
	}
	catch( EAccesoIndebido3 e ) {
		
		cout << endl << endl << e.mensaje( ) << endl ;
		
	}
	
    return 0;

}