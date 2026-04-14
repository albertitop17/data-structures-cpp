#include <iostream>
#include "arbus.h"


int main (int argc, char * const argv[]) {
	
	
	try {
		
		TArbus<char,int> b;
		
		b.inserta('a',7);
		b.inserta('b',5);
		b.inserta('c',9);
		b.inserta('d',3);
		b.inserta('e',4);
		b.inserta('f',6);
		
		b.escribe();
		
		cout << endl << "Las claves del arbol ordenadas son: " << endl;
		
		TSecuenciaDinamica<char> s1;
		
		s1 = b.recorreClave();
		
		s1.escribe();
		
		cout << endl << "Los valores del arbol ordenados por la clave son: " << endl;
		
		TSecuenciaDinamica<int> s2;
		
		s2 = b.recorre();
		
		s2.escribe();
		
		
		char clave = 'z';
		
		cout << endl << "El valor asociado a la clave " << clave << " es: " << b.consulta(clave) << endl;
		
	}
	catch( EClaveErronea3 e ) {
		
		cout << endl << endl << e.mensaje( ) << endl;
		
	}
	
	
	try {
		
		TArbus<int,char> arbol;
	
		if ( arbol.esVacio() ) cout << endl << "El arbol SI esta vacio" << endl;
		else cout << endl << "El arbol NO esta vacio" << endl;
	
		arbol.inserta(7,'a');
		arbol.inserta(5,'b');
		arbol.inserta(9,'c');
		arbol.inserta(3,'d');
		arbol.inserta(4,'e');
		arbol.inserta(6,'f');
	
		arbol.escribe();
	
		arbol.inserta(7,'z');
		arbol.inserta(4,'v');
	
		arbol.escribe();
	
		if ( arbol.esVacio() ) cout << endl << "El arbol SI esta vacio" << endl;
		else cout << endl << "El arbol NO esta vacio" << endl;
	
		int clave1 = 4;
	
		cout << endl << "El valor asociado a la clave " << clave1 << " es: " << arbol.consulta(clave1) << endl;
	
		if ( arbol.esta(clave1) ) cout << endl << "El arbol SI contiene la clave " << clave1 << endl;
		else cout << endl << "El arbol NO contiene la clave " << clave1 << endl;
	
		int clave2 = 12;
	
		if ( arbol.esta(clave2) ) cout << endl << "El arbol SI contiene la clave " << clave2 << endl;
		else cout << endl << "El arbol NO contiene la clave " << clave2 << endl;
	
		int clave3 = 5;
	
		cout << endl << "Eliminamos el par (" << clave3 << "," << arbol.consulta(clave3) << ") en el arbol: " << endl;
	
		arbol.borra(clave3);
	
		arbol.escribe();
	
		cout << endl << "Las claves del arbol ordenadas, son: " << endl;
	
		TSecuenciaDinamica<int> sec1;
	
		sec1 = arbol.recorreClave();
	
		sec1.escribe();
	
		cout << endl << "Los valores del arbol, ordenados por la clave, son: " << endl;
	
		TSecuenciaDinamica<char> sec2;
	
		sec2 = arbol.recorre();
		
		cout << "ESTA ES LA SECUENCIA 2:" << endl;
		
		sec2.escribe();
	
		cout << endl;
		cout << endl;
		cout << endl;
		cout << "LA CLAVE MINIMA ES: "<<endl;
		
				
		
		cout << arbol.minimo();
		
		cout << endl;
		cout << endl;
		
		
		TArbus<char,int> arb2;
		
		arb2 = arb2.creaArbol(sec2);
		cout << "EL ARBOL DE LA SECUENCIA 2 ES: "<<endl;
		arb2.escribe();
		
		TSecuenciaDinamica<char> sec33;
		
		sec33 = arb2.obtenerSec();
		
		cout << endl << endl;
		cout << "RECUPERAMOS LA SECUENCIA DEL ARBOL CREADO: "<<endl;
		sec33.escribe();
		
	
		int ant;
		
//		cout<< arbol.maximo_clave();
		
		cout << endl << "Del arbol: " << endl;
		arbol.escribe();
			
		cout << endl << endl;
		cout << "LOS NODOS MENORES AL 7 SON: "<<endl;
		TSecuenciaDinamica<int> asiu;
		asiu = arbol.obtenerMenores(7);
		asiu.escribe();
		try{
			cout << endl << "EL anterior de 7 es : " << endl;
			ant = arbol.anterior(7);
			cout << ant;
			cout << endl << "EL anterior de 6 es : " << endl;
			ant = arbol.anterior(6);
			cout << ant;
			cout << endl << "EL anterior de 4 es : " << endl;
			ant = arbol.anterior(4);
			cout << ant;
			cout << endl << "EL anterior de 9 es : " << endl;
			ant = arbol.anterior(9);
			cout << ant;
//			cout << endl << "EL anterior de 3 es : " << endl;
//			ant = arbol.anterior(3);
//			cout << ant;
			
			cout << endl << endl;
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			cout << "EL NUMERO DE HOJAS PROFUNDAS ES: "<< endl;
			cout << arbol.numHojasProfundas(1) << endl;
			cout << "EL NUMERO DE HOJAS PROFUNDAS ES: "<< endl;
			cout << arbol.numHojasProfundas(2)<< endl;
			cout << "EL NUMERO DE HOJAS PROFUNDAS ES: "<< endl;
			cout << arbol.numHojasProfundas(3) << endl;
			cout << "EL NUMERO DE HOJAS PROFUNDAS ES: "<< endl;
			cout << arbol.numHojasProfundas(4) << endl;
			
			cout << "Es zurdo?: "<< endl;
			cout << arbol.zurdo();
			cout << endl << endl;
			arbol.inserta(2,'d');
			arbol.inserta(1,'d');
			cout << "Es zurdo?: "<< endl;
			cout << arbol.zurdo();
			arbol.escribe();
			
			
			
			TArbus<int,char> arbolito;
			arbolito.inserta(4,'*');
			arbolito.inserta(2,'*');
			arbolito.inserta(1,'*');
			arbolito.inserta(3,'*');
			arbolito.inserta(6,'*');
			arbolito.inserta(5,'*');
			arbolito.inserta(7,'*');
			
			arbolito.escribe();
			cout << endl << endl;
			cout << "EL SIGUIENTE A 1 ES: "<< endl;
			cout << arbolito.siguiente(1)<< endl;
			cout << "EL SIGUIENTE A 2 ES: "<< endl;
			cout << arbolito.siguiente(2)<< endl;
			cout << "EL SIGUIENTE A 3 ES: "<< endl;
			cout << arbolito.siguiente(3)<< endl;
			cout << "EL SIGUIENTE A 4 ES: "<< endl;
			cout << arbolito.siguiente(4)<< endl;
			cout << "EL SIGUIENTE A 5 ES: "<< endl;
			cout << arbolito.siguiente(5)<< endl;
			cout << "EL SIGUIENTE A 6 ES: "<< endl;
			cout << arbolito.siguiente(6)<< endl;
//			cout << "EL SIGUIENTE A 1 ES: "<< endl;
//			cout << arbolito.siguiente(1)<< endl;
			
			TSecuenciaDinamica<int> entre2y6;
			entre2y6 = arbolito.enRango(2,6);
			entre2y6.escribe();
			
			cout << endl;
			cout << arbolito.numEnRango(2,6);
			cout << endl;
			
			TSecuenciaDinamica<int> entre0y9;
			entre0y9 = arbolito.enRango(0,9);
			entre0y9.escribe();
			
			cout << endl;
			cout << arbolito.numEnRango(0,9);
			cout << endl;
			
			cout << endl;
			if (arbolito.equilibrado()) cout << "EL ARBOLITO ESTA EQUILIBRADO";
			else cout << "EL ARBOLITO NO ESTA EQUILIBRADO";
			cout << endl;
			arbol.escribe();
			cout << endl;
			if (arbol.equilibrado()) cout << "EL ARBOLITO ESTA EQUILIBRADO";
			else cout << "EL ARBOLITO NO ESTA EQUILIBRADO";
			cout << endl;
		}
		catch(EAccesoIndebido3 e){	
			cout << endl << endl << e.mensaje( ) << endl;
		}
		
		
		
//		TSecuenciaDinamica<Par<int,char>> sp;
//		
//		sp.inserta(Par<int, char>(5,'f'));
//		sp.inserta(Par<int, char>(2,'j'));
//		sp.inserta(Par<int, char>(3,'l'));
//		sp.inserta(Par<int, char>(7,'a'));
//		sp.inserta(Par<int, char>(8,'s'));
//		sp.inserta(Par<int, char>(4,'p'));
//		sp.inserta(Par<int, char>(1,'s'));
//		
//		
		//TArbus<int,char> arbus2;
		
		//arbus2.creaArbol(sec2);
		
//		sp.escribe();
		
		
		
		
	}
	catch( EClaveErronea3 e ) {
		
		cout << endl << endl << e.mensaje( ) << endl << endl;
		
	}
	
    return 0;
	
}