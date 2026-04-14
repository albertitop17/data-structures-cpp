#ifndef tabla_abiertaH
#define tabla_abiertaH


#include <iostream>
#include <string>


using namespace std;



// Excepciones generadas por las operaciones de este TAD:
// Acceso cuando se accede con una clave que no está en la tabla
// class EClaveErronea { };



class EClaveErronea2 {
	
	public:
	
		EClaveErronea2( string mensaje = "" ) : _mensaje(mensaje) { };
	
		string mensaje ( ) {
			
			return _mensaje;
			
		};
	
	private:
	
		string _mensaje;
	
};



// Funciones auxiliares de localización


int num( int n ) {
	
  return n;
	
}


int num( char ch ) {
	
  return ch;
	
}


int num( string cad ) {
	
  int res = 0;
	
  for ( int i = 0; i < cad.length(); i++ )
	  
    res += cad[i]; //al ser res un int y sumarle un char, c++ lo interpreta en el codigo ASCII
	
  return res;
	
}



// El tipo 'TClave' debe implementar:
//    operator==
//    int TClave::num()


template <class TClave>
int num ( TClave clave ) {
	
  return clave.num();
	
}





template <class TClave, class TValor>
class TTablaAbierta;


//solo necesito igualdad, no hace falta orden
template <class TClave, class TValor>
class TNodoTabla {
	
  private:
	
    TClave _clave;
    TValor _valor;
    TNodoTabla<TClave,TValor>* _sig;
	
    TNodoTabla( TClave, TValor, TNodoTabla<TClave,TValor>* );
	
  public:
	
    TClave clave();
    TValor valor();
    TNodoTabla<TClave,TValor>* sig();
	
    friend class TTablaAbierta<TClave,TValor>;
	
};





template <class TClave, class TValor>
class TTablaAbierta {
	
  public:

	
  // Constructora
	
     TTablaAbierta( ); // O(N)

	
  // Operaciones de las tablas abiertas
	
	
     void inserta( TClave, TValor );
     // Pre  : true
     // Post : inserta un par (clave, valor),
     //        si la clave ya está, se sustituye el valor antiguo
	
	
     void borra( TClave );
     // Pre  : true
     // Post : elimina un par (clave, valor) a partir de una clave dada,
     //        si la clave no está, la tabla no se modifica

	
     TValor consulta( TClave ); // throw ( EClaveErronea2 );
     // Pre  : esta(clave)
     // Post : devuelve el valor asociado con la clave dada
     //        Lanza la excepción 'EClaveErronea2' si la tabla no contiene dicha clave

	
     bool esta( TClave );
     // Pre  : true
     // Post : devuelve true o false según si la tabla contiene o no la clave

	
     bool esVacio( ); 
     // Pre  : true
     // Post : Devuelve true o false según si la tabla está o no vacía
	 // O(N)
	
  // Operaciones auxiliares
	
	 void copia( TTablaAbierta<TClave,TValor> );
	
	
  // Escritura
	
     void escribe( );
	

	
  private:
	
	
  // Variables privadas
	
	//inicializo la tabla de longitud 10
     static const int longMax = 10;
     TNodoTabla<TClave,TValor>* _espacio[longMax];

	
  // Función hash
	
     int localiza( TClave );
	
	
  // Función auxiliar de búsqueda del nodo con una clave dada
	
     void busca ( TClave, TNodoTabla<TClave,TValor>* &, TNodoTabla<TClave,TValor>* & );


};





//---------------------------------------------------------------------------
//   IMPLEMENTACION
//---------------------------------------------------------------------------



  // Clase de los nodos


    template <class TClave, class TValor>
    TNodoTabla<TClave,TValor>::TNodoTabla( TClave clave,
                                           TValor valor,
                                           TNodoTabla<TClave,TValor>* sig ) :
                                           	
      _clave(clave), _valor(valor), _sig(sig) {
      	
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
    TNodoTabla<TClave,TValor>* TNodoTabla<TClave,TValor>::sig() {
		
      return _sig;
		
    }



  // Constructora ********************************************************************************************


     template <class TClave, class TValor>
     TTablaAbierta<TClave,TValor>::TTablaAbierta( ) {
		 
       for ( int i = 0; i < longMax; i++ )
		   
         _espacio[i] = 0; //inicializo el vector 0..N-1 de punteros a nill
		 
     };



  // Operaciones de las tablas abiertas


     // Inserción

     template <class TClave, class TValor>
     void TTablaAbierta<TClave,TValor>::inserta( TClave clave, TValor valor ) {
		 
       int i;
		 
       TNodoTabla<TClave,TValor> *act, *ant;
		 
       i = localiza( clave ); //funcion hass
		 
       act = _espacio[i]; //en la posicion en la que estoy
		 
       busca( clave, act, ant ); //lo que antes llamabamos localizar
		 
       if ( act != 0 )
		   
         act -> _valor = valor; //ESTO SERIA COMBINAR
		 
       else {
		   
         act = new TNodoTabla<TClave,TValor>(clave, valor, _espacio[i]); //reservar(p)
		   
         _espacio[i] = act;
		   
       }
		 
     };



     // Borrado

     template <class TClave, class TValor>
     void TTablaAbierta<TClave,TValor>::borra( TClave clave ) {
		 
       int i;
		 
       TNodoTabla<TClave,TValor> *act, *ant;

       i = localiza(clave);
		 
       act = _espacio[i];
		 
       busca( clave, act, ant );
		 
       if ( act != 0 ) {
		   
         if ( ant != 0 )
			 
           ant -> _sig = act -> sig();
		   
         else
			 
           _espacio[i] = act -> sig();
		   
         delete act;
		   
       }
		 
     };



     // Consultas

     template <class TClave, class TValor>
     TValor TTablaAbierta<TClave,TValor>::consulta( TClave clave ) // throw (EClaveErronea2) 
	 {
		 
       int i;
		 
       TNodoTabla<TClave,TValor> *act, *ant;

       i = localiza(clave);
		 
       act = _espacio[i];
		 
       busca( clave, act, ant );
		 
       if ( act == 0 )
		   
         throw EClaveErronea2("Error: la tabla abierta no contiene la clave");
		 
       return act -> valor();
		 
     };



     template <class TClave, class TValor>
     bool TTablaAbierta<TClave,TValor>::esta( TClave clave ) {
		 
       int i;
		 
       TNodoTabla<TClave,TValor> *act, *ant;

       i = localiza(clave);
		 
       act = _espacio[i];
		 
       busca( clave, act, ant );
		 
       return act != 0;
		 
     };



     template <class TClave, class TValor>
     bool TTablaAbierta<TClave,TValor>::esVacio( ) {
		 
       int i = 0;
		 
       bool vacio = true;

       while ( vacio && (i < longMax) ) {
		   
         vacio = _espacio[i] == 0;
         i++;
		   
       }
		 
       return vacio;
		 
     };



  // Operaciones de entrada/salida

     template <class TClave, class TValor>
     void TTablaAbierta<TClave,TValor>::escribe( ) {
		 
       TNodoTabla<TClave,TValor> *act;
		 
	   cout << endl;

       for ( int i = 0; i < longMax; i++ ) {
		   
         act = _espacio[i];
		   
         cout << i << ":";
		   
         while ( act != 0 ) {
			 
           cout << "(" << act -> clave() << ", " << act -> valor() << + ") ";
			 
           act = act -> sig();
			 
         }
		   
		 cout << endl;
		   
       }
		 
	   cout << endl;
		 
     };





  // Operaciones auxiliares


     // Copia

     template <class TClave, class TValor>
     void TTablaAbierta<TClave,TValor>::copia( TTablaAbierta<TClave,TValor> tabla ) {
		 
       TNodoTabla<TClave,TValor> *act, *actCopia, *antCopia;

       for ( int i = 0; i < longMax; i++ ) {
		   
         if ( tabla._espacio[i] != 0 ) {
			 
           act = tabla._espacio[i];
           actCopia = new TNodoTabla<TClave,TValor>( act -> clave(), act -> valor(), 0 );
           _espacio[i] = actCopia;
			 
           while ( act -> sig() != 0 ) {
			   
             act = act -> sig();
             antCopia = actCopia;
             actCopia = new TNodoTabla<TClave,TValor>( act -> clave(), act -> valor(), 0 );
             antCopia -> _sig = actCopia;
			   
           }
			 
         }
		   
         else
			 
           _espacio[i] = 0;
		   
       }
		 
     };
 
 

     // Función hash -------------------------------------------------------------------------------------------

     template <class TClave, class TValor>
     int TTablaAbierta<TClave,TValor>::localiza( TClave clave ) {
		
        return num(clave) % longMax; //primero convierte la clave en un numero si no lo era
		 
	 // return clave.num() % longMax;
		 
     };



     // Función auxiliar de búsqueda del nodo con una clave dada

     template <class TClave, class TValor>
     void TTablaAbierta<TClave,TValor>::busca( TClave clave,
                                               TNodoTabla<TClave,TValor>* & act,
                                               TNodoTabla<TClave,TValor>* & ant ) {
		 
       bool encontrado = false;

       ant = 0;
		 
       while ( (! encontrado) && (act != 0) ) {
		   
         encontrado = ( clave == act -> clave() );
		   
         if ( ! encontrado ) {
			 
           ant = act;
			 
           act = act -> sig();
			 
         }
		   
       }
		 
     };



#endif
