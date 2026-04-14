#ifndef tabla_cerradaH
#define tabla_cerradaH



#include <iostream>
#include <string>

#include "secuencia_dinamica.h"


using namespace std;



// Excepciones generadas por las operaciones de este TAD:
// Acceso cuando se accede con una clave que no esta en la tabla:
// class EClaveErronea { };
// Insercion cuando el array esta lleno:
// class EDesbordamiento { };



// Funciones auxiliares de localizacion


template <class TClave>
int num( TClave clave ) {
	
  return clave.num( );
	
}


template< >
int num<int>( int n ) {
	
  return n;
	
}


template< >
int num<char>( char ch ) {
	
  return ch;

}


template< >
int num<string>( string cad ) {
	
  int res = 0;
	
  for ( int i = 0; i < cad.length(); i++ )
	  
    res += cad[i];
	
  return res;
	
}


/*

template< >
int num<string*>( string* puntero ) {
	
  return int(puntero);
	
}

*/



// Posibles longitudes del array donde se almacena la tabla


const int maxLongitudes = 5;
const int longitudes[maxLongitudes] = { 23, 57, 101, 213, 427 };



// El tipo TClave debe implementar
//    operator==
//    int TClave::num() const



template <class TClave, class TValor>
class TTablaCerrada;


enum TPosicion { vacia, ocupada, borrada };


template <class TClave, class TValor>
class TNodoTabla {
	
  private:
	
    TClave _clave;
    TValor _valor;
    TPosicion _posicion;
	
    TNodoTabla();
	
  public:
	
    TClave clave();
    TValor valor();
    TPosicion posicion();
	
    friend class TTablaCerrada<TClave,TValor>;
	
};



template <class TClave, class TValor>
class TTablaCerrada {
	
  public:

	
  // Constructora
	
     TTablaCerrada();

	
  // Operaciones de las tablas
	
     void inserta( TClave, TValor );
     // Pre  : true
     // Post : inserta un par (clave, valor),
     //        si la clave ya esta, se sustituye el valor antiguo

	
     void borra( TClave );
     // Pre  : true
     // Post : elimina un par (clave, valor) a partir de una clave dada,
     //        si la clave no esta, la tabla no se modifica

	
  // observadoras
	
     TValor consulta( TClave ); // throw ( EClaveErronea );
     // Pre  : esta(clave)
     // Post : devuelve el valor asociado con la clave dada
     //        Lanza la excepcion 'EClaveErronea' si la tabla no contiene dicha clave

	
     bool esta( TClave );
     // Pre  : true
     // Post : devuelve true o false segun si la tabla contiene o no la clave

	
     bool esVacio( );
     // Pre  : true
     // Post : Devuelve true o false segun si la tabla esta o no vacia

	
     int numElem( );
     // Pre  : true
     // Post : Devuelve el numero de elementos almacenados en la tabla

	
  // Recorrido de tablas	
	 
     TSecuenciaDinamica<TClave> enumeraClave();
     // Pre  : true
     // Post : Devuelve una secuencia con las claves de la tabla

	
     TSecuenciaDinamica<TValor> enumeraValor();
     // Pre  : true
     // Post : Devuelve una secuencia con los valores de la tabla
	 
	
  // Operaciones auxiliares
	
  	 void copia( TTablaCerrada<TClave,TValor> );
	

  // Escritura
	
     void escribe();


  private:
	
	
  // Variables privadas
	
     static const int ocupacion = 50;        // en tanto por ciento
	
     TNodoTabla<TClave,TValor>* _espacio;  /// _espacio *-----> [][][][] 
	
     int _numElem, _numBorradas, _longitud;


  // Funcion auxiliar de busqueda del nodo con una clave dada
	
     int busca( TClave );
	
	
  // Reagrupa las posiciones de la tabla para eliminar las posiciones borradas
	
     void limpia( );
	
	
  // Hace crecer el array donde se almacena la tabla
	
     void amplia( );
	
	
};





//---------------------------------------------------------------------------
//   IMPLEMENTACION
//---------------------------------------------------------------------------



  // Clase de los nodos


    template <class TClave, class TValor>
    TNodoTabla<TClave,TValor>::TNodoTabla() :
    	
      _posicion(vacia) {
      	
    };


    template <class TClave, class TValor>
    TClave TNodoTabla<TClave,TValor>::clave() {
		
      return _clave;
		
    }


    template <class TClave, class TValor>
    TValor TNodoTabla<TClave,TValor>::valor() {
		
      return _valor;
		
    }


    template <class TClave, class TValor>
    TPosicion TNodoTabla<TClave,TValor>::posicion() {
		
      return _posicion;
		
    }



  // Constructora

     template <class TClave, class TValor>
     TTablaCerrada<TClave,TValor>::TTablaCerrada() :
     	
       _numElem(0), _numBorradas(0), _longitud(0),
       _espacio(new TNodoTabla<TClave,TValor>[longitudes[0]]) {
       	
     };



  // Operaciones de las tablas


     // Insercion

     template <class TClave, class TValor>
     void TTablaCerrada<TClave,TValor>::inserta( TClave clave, TValor valor ) {
		 
       int i, n, d, m;
       bool encontrado;

       if ( ( ( _numElem + _numBorradas ) * 100 / longitudes[_longitud] ) > ocupacion )
		   
	   // limpia( );
	      amplia( );
		 
       n = num<TClave>(clave);
       i = n % longitudes[_longitud];
       d = ( n % ( longitudes[_longitud] - 2 ) ) + 1;
       m = 0;     // contabiliza el numero de pruebas por si la tabla esta llena
       encontrado = false;
		 
       while ( ( ! encontrado ) && ( _espacio[i].posicion() == ocupada ) && ( m < longitudes[_longitud] ) ) {
		   
         if ( _espacio[i]._posicion == ocupada )
			 
           encontrado = ( clave == _espacio[i].clave() );
		   
         if ( ! encontrado ) {
			 
           m++;
           i = ( i + d ) % longitudes[_longitud];
			 
         }
		   
       }
		 
       if ( m == longitudes[_longitud] )
		   
         throw EDesbordamiento3( "Error: el array esta lleno" );
		 
       else if ( encontrado )
		   
         _espacio[i]._valor = valor;
		 
       else if ( _espacio[i].posicion() == vacia ) {
		   
         _espacio[i]._clave = clave;
         _espacio[i]._valor = valor;
         _espacio[i]._posicion = ocupada;
         _numElem++;
		   
       }
       else if ( _espacio[i].posicion() == borrada ) {
		   
         _espacio[i]._clave = clave;
         _espacio[i]._valor = valor;
         _espacio[i]._posicion = ocupada;
         _numElem++;
         _numBorradas--;
		   
         m++;
         i = ( i + d ) % longitudes[_longitud];
		   
         while ( ( ! encontrado ) && ( _espacio[i].posicion() != vacia ) && ( m < longitudes[_longitud] ) ) {
			 
           if ( _espacio[i].posicion() == ocupada )
			   
             encontrado = ( clave == _espacio[i].clave() );
			 
           if ( ! encontrado ) {
			   
             m++;
             i = (i + d) % longitudes[_longitud];
			   
           }
			 
         }
		   
         if ( encontrado ) {
			 
           _espacio[i]._posicion = borrada;
           _numBorradas++;
			 
         }
		   
       }
		 
     };



     // Borrado

     template <class TClave, class TValor>
     void TTablaCerrada<TClave,TValor>::borra( TClave clave ) {
		 
       int i;

       i = busca(clave);
		 
       if ( i != longitudes[_longitud] ) {
		   
         _espacio[i]._posicion = borrada;
         _numElem--;
         _numBorradas++;
		   
       }
		 
     };



     // Consultas

     template <class TClave, class TValor>
     TValor TTablaCerrada<TClave,TValor>::consulta( TClave clave ) // throw ( EClaveErronea ) 
	 {
		 
       int i;

       i = busca(clave);
		 
       if ( i == longitudes[_longitud] )
		   
         throw EClaveErronea3( "Error: la tabla no contiene la clave" );
		 
       return _espacio[i].valor();
		 
     };



     template <class TClave, class TValor>
     bool TTablaCerrada<TClave,TValor>::esta( TClave clave ) {
		 
       int i;

       i = busca(clave);
		 
       return i != longitudes[_longitud];
		 
     };



     template <class TClave, class TValor>
     bool TTablaCerrada<TClave,TValor>::esVacio( ) {
		 
       return _numElem == 0;
		 
     };



     template <class TClave, class TValor>
     int TTablaCerrada<TClave,TValor>::numElem() {
		 
       return _numElem;
		 
     };



     template <class TClave, class TValor>
     TSecuenciaDinamica<TClave> TTablaCerrada<TClave,TValor>::enumeraClave() {
		 
       TSecuenciaDinamica<TClave> resultado;

       for ( int i = 0; i < longitudes[_longitud]; i++ ) {
		   
         if ( _espacio[i].posicion() == ocupada )
			 
           resultado.inserta( _espacio[i].clave() );
		   
       }
		 
       return resultado;
		 
     };



     template <class TClave, class TValor>
     TSecuenciaDinamica<TValor> TTablaCerrada<TClave,TValor>::enumeraValor( ) {
		 
       TSecuenciaDinamica< TValor > resultado;

       for ( int i = 0; i < longitudes[_longitud]; i++ ) {
		   
         if ( _espacio[i].posicion() == ocupada )
			 
           resultado.inserta( _espacio[i].valor() );
		   
       }
		 
       return resultado;
		 
     };
 
 

  // Operaciones de entrada/salida

     template <class TClave, class TValor>
     void TTablaCerrada<TClave,TValor>::escribe( ) {
		 
	   cout << endl;

       for ( int i = 0; i < longitudes[_longitud]; i++ ) {
		   
         cout << i << ":";
		   
         if ( _espacio[i].posicion() == ocupada )
			 
           cout << "(" << _espacio[i].clave() << ", " << _espacio[i].valor() << ")";
		   
         else if ( _espacio[i].posicion() == borrada )
			 
           cout << "###";
		   
         cout << endl;
		   
       }
		 
	   cout << endl;
		 
     };



  // Operaciones privadas


     // Copia

     template <class TClave, class TValor>
     void TTablaCerrada<TClave,TValor>::copia( TTablaCerrada<TClave,TValor> tabla ) {
		 
       _longitud = tabla._longitud;
		 
       _espacio = new TNodoTabla<TClave,TValor>[longitudes[_longitud]];
		 
       for ( int i = 0; i < longitudes[_longitud]; i++ ) {
		   
         _espacio[i]._posicion = tabla._espacio[i]._posicion;
		   
         if ( _espacio[i]._posicion == ocupada ) {
			 
           _espacio[i]._clave = tabla._espacio[i].clave();
           _espacio[i]._valor = tabla._espacio[i].valor();
			 
         }
		   
       }
		 
       _numElem = tabla._numElem;
       _numBorradas = tabla._numBorradas;
		 
     };



     // Funcion auxiliar de busqueda del nodo con una clave dada

     template <class TClave, class TValor>
     int TTablaCerrada<TClave,TValor>::busca( TClave clave ) {
		 
       int i, n, d, m;
       bool encontrado;

    // n = clave.num( );
		 
       n = num<TClave>(clave);
       i = n % longitudes[_longitud];
       d = ( n % ( longitudes[_longitud] - 2 ) ) + 1;
       m = 0;     //contabiliza el numero de pruebas por si la tabla esta llena
       encontrado = false;
		 
       while ( ( ! encontrado ) && ( _espacio[i].posicion() != vacia ) && ( m < longitudes[_longitud] ) ) {
		   
         if ( _espacio[i]._posicion == ocupada )
			 
           encontrado = ( clave == _espacio[i].clave( ) );
		   
         if ( ! encontrado ) {
			 
           m++;
           i = (i + d) % longitudes[_longitud];
			 
         }
		   
       }
		 
       if ( ! encontrado )
		   
         i = longitudes[_longitud];
		 
       return i;
		 
     };



     // funcion auxiliar que limpia la tabla
     //
     //  h(clave) = num(clave) % longitudes[_longitud]
     //  k(clave) = d = ( num(clave) % ( longitudes[_longitud] - 2 ) ) + 1
     //
     //  i_0 = h(clave)
     //  i_m = ( i_m-1 + d ) % longitudes[_longitud]
     //
     //  i_m-1 = i_m - d        si i_m - d >= 0
     //  i_m-1 = N + i_m - d    si i_m - d <  0



     template <class TClave, class TValor>
     void TTablaCerrada<TClave,TValor>::limpia( ) {
		 
       int n, i_0, i_m, d, pos;
       bool movimiento = true;

       while ( movimiento ) {
		   
         movimiento = false;
		   
         for ( int i = 0; i < longitudes[_longitud]; i++ )
			 
           if ( _espacio[i].posicion( ) == ocupada ) {
			   
             n = num(_espacio[i].clave( ));
             i_0 = n % longitudes[_longitud];
             d = ( n % (longitudes[_longitud] - 2 ) ) + 1;
             pos = i_m = i;
			   
             while ( i_m != i_0 ) {
				 
               if ( (i_m - d) >= 0 )
				   
                 i_m = i_m - d;
				 
               else
				   
                 i_m = longitudes[_longitud] + i_m - d;
				 
               if ( _espacio[i_m].posicion( ) == borrada )
				   
                 pos = i_m;
				 
             }
			   
             if ( pos != i ) {
				 
               _espacio[pos]._clave = _espacio[i].clave( );
               _espacio[pos]._valor = _espacio[i].valor( );
				 
               _espacio[pos]._posicion = ocupada;
               _espacio[i]._posicion = borrada;
				 
               movimiento = true;
				 
             }
			   
           }
		   
       }
		 
       for (int i = 0; i < longitudes[_longitud]; i++ )
		   
         if ( _espacio[i].posicion( ) == borrada )
			 
           _espacio[i]._posicion = vacia;
		 
         _numBorradas = 0;
		 
     }



     template <class TClave, class TValor>
     void TTablaCerrada<TClave,TValor>::amplia( ) {
		 
       if ( _longitud < ( maxLongitudes - 1 ) ) {
		   
         _longitud++;
		   
         TNodoTabla<TClave,TValor>* aux = _espacio;
		   
         _espacio = new TNodoTabla<TClave,TValor>[longitudes[_longitud]];
		   
         _numBorradas = _numElem = 0;
		   
         for ( int i = 0; i < longitudes[_longitud-1]; i++ )
			 
           if ( aux[i].posicion( ) == ocupada )
			   
             inserta(aux[i].clave( ), aux[i].valor( ));
		   
         delete [] aux;
		   
       }
		 
     }
 


#endif
