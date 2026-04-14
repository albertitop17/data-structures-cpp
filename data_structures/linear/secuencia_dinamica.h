#ifndef secuencia_dinamicaH
#define secuencia_dinamicaH
//#include "pila_dinamica.h"
//#include "pila_dinamica.h"

/*
 
 
 especificacion SECUENCIAS[ELEM]
 
 usa LISTAS[ELEM], BOOLEANOS
 
 tipos secuencia
 
 operaciones
 
	nuevo    :                 -->   secuencia 
	inserta  : secuencia elem  -->   secuencia
    borra    : secuencia       -/->  secuencia
    actual   : secuencia       -/->  elem                 
    avanza   : secuencia       -/->  secuencia             
    reinicia : secuencia       -->   secuencia          
    esVacio  : secuencia       -->   bool                
    esFin    : secuencia       -->   bool                   
 
  operaciones privadas
 
    sec      : lista lista     -->   secuencia    { constructora }
    piz      : secuencia       -->   lista   
    pdr      : secuencia       -->   lista 
    cont     : secuencia       -->   lista 
 
 variables
 
	x        : elem
	s        : secuencia
	iz, dr   : lista
	
 ecuaciones

    nuevo                              = sec(vacio, vacio)
 
    inserta(sec(iz, dr), x)            = sec(ponDetras(iz, x), dr)
 
    esFin(sec(iz, dr))                 = esVacio(dr)
 
	borra(s)                           = error                            <==  esFin(s)
    borra(sec(iz, ponDelante(x, dr)))  = sec(iz, dr)
 
	actual(s)                          = error                            <==  esFin(s)
    actual(sec(iz, ponDelante(x, dr))) = x
 
    avanza(s)                          = error                            <==  esFin(s)
    avanza(sec(iz, ponDelante(x, dr))) = sec(ponDetras(iz, x), dr)
 
    reinicia(sec(iz, dr))              = sec(vacio, concatena(iz, dr))
 
    esVacio(sec(iz, dr))               = esVacio(iz) /\ esVacio(dr)
 
    piz(sec(iz, dr))                   = iz
 
    pdr(sec(iz, dr))                   = dr
 
    cont(sec(iz, dr))                  = concatena(iz, dr)

 
 fespecificacion

 
*/


#include <iostream>
#include <string>

using namespace std;



// Tratamiento de excepciones


class EDesbordamiento3 {
	
  public:
	
    EDesbordamiento3( string mensaje = "" ) : _mensaje(mensaje) { };
	
    string mensaje ( ) {
		
		return _mensaje;
		
    };
	
  private:
	
    string _mensaje;
	
};


class EAccesoIndebido3 {
	
  public:
	
    EAccesoIndebido3( string mensaje = "" ) : _mensaje(mensaje) { };
	
    string mensaje ( ) {
		
		return _mensaje;
		
    };
	
  private:
	
    string _mensaje;
	
};


class EClaveErronea3 {

  public:
	
    EClaveErronea3( string mensaje = "" ) : _mensaje(mensaje) { };
	
    string mensaje ( ) {
		
		return _mensaje;
		
    };
	
  private:
	
    string _mensaje;
	
};



// Clase de los nodos de la secuencia


template <class TElem>
class TSecuenciaDinamica;


template <class TElem>
class TNodoSecuencia {
	
  private:
	
    TElem _elem;
    TNodoSecuencia<TElem>* _sig;
	
    TNodoSecuencia( );
    TNodoSecuencia( TElem, TNodoSecuencia<TElem>* = 0 );
	
  public:
	
    TElem elem( );
    TNodoSecuencia<TElem>* sig( );
	
    friend class TSecuenciaDinamica<TElem>;
	
};



// Clase de las secuencias


template <class TElem>
class TSecuenciaDinamica {
	
	
  public:

  // Constructora
	
     TSecuenciaDinamica( );
     // O(1) sobre tipos predefinidos
     

  // Operaciones de las secuencias
	
     void inserta( TElem );
     // Pre: true
     // Post: Se anade un elemento a la secuencia, delante del punto de interes
     // O(1) sobre tipos predefinidos

     void borra( ); // throw ( EAccesoIndebido );
     // Pre: ! esFin( )
     // Post: Elimina el elemento que esta detras del punto de interes
     // Lanza la excepcion "EAccesoIndebido" si el punto de interes esta al final
     // O(1) sobre tipos predefinidos

     TElem actual( ); // throw ( EAccesoIndebido );
     // Pre: ! esFin( )
     // Post: Devuelve el elemento a continuacion del punto de interes
     // Lanza la excepcion "EAccesoIndebido" si el punto de interes esta al final
     // O(1)

     void avanza( ); // throw ( EAccesoIndebido );
     // Pre: ! esFin( )
     // Post: Avanza una posicion el punto de interes
     // Lanza la excepcion "EAccesoIndebido" si el punto de interes esta al final
     // O(1)

     void reinicia( );
     // Pre: true
     // Post: Coloca el punto de interes al principio de la secuencia
     // O(1)

     bool esFin( );
     // Pre: true
     // Post: Determina si el punto de interes esta al final de la secuencia
     // O(1)

     bool esVacio( );
     // Pre: true
     // Post: Determina si la secuencia esta vacia
     // O(1)

	void concatena( TSecuenciaDinamica<TElem>& lista );
     // Pre: true;
     // Post: coloca lista destras de la secuencia
     // O(la longitud de la lista)
	
	void saltaHaciaDelante(int n);
     //Pre: true
     //Post: Situa el punto de interes n elementos más hacia el final de la secuencia de la posicion que tenia.
     //O(n)
      
    int numElemTratados();
     //Pre: true
     //Post: devuelve el numero de elementos que hay entre el comienzo y el punto de interes.
     //O(n), siendo n el numero de elementos antes del punto de interes
      
    bool palindroma();
     //Pre: true
     //Post: devuelve si una secuencia es palindroma
     //O(n) 	 
     
  // Escritura
	
     void escribe( );
	

  private:
	
  // Variables privadas
	
     TNodoSecuencia<TElem> *_pri, *_ant;

	
};



//---------------------------------------------------------------------------
// IMPLEMENTACION
//---------------------------------------------------------------------------


  // Clase de los nodos

    // Es necesaria una constructora sin parametros (sin elem) para poder
    // construir el nodo fantasma. El campo _elem de ese nodo contendra
    // basura si se trata de un tipo primitivo o el resultado de llamar
    // a la constructora por defecto si no lo es.


    template <class TElem>
    TNodoSecuencia<TElem>::TNodoSecuencia( ) : 
	  _sig(0) {
    };


    template <class TElem>
    TNodoSecuencia<TElem>::TNodoSecuencia( TElem elem, TNodoSecuencia<TElem>* sig ) :
      _elem(elem), _sig(sig) {
    };


    template <class TElem>
    TElem TNodoSecuencia<TElem>::elem( ) {
		
      return _elem;
		
    }


    template <class TElem>
    TNodoSecuencia<TElem>* TNodoSecuencia<TElem>::sig( ) {
		
      return _sig;
		
    }


  // Constructora

     template <class TElem>
     TSecuenciaDinamica<TElem>::TSecuenciaDinamica( ) {
		 
       _pri = _ant = new TNodoSecuencia<TElem>( );
		 
     };


  // Operaciones de las secuencias

     template <class TElem>
     void TSecuenciaDinamica<TElem>::inserta( TElem elem ) {
		 
       TNodoSecuencia<TElem>* nuevo = new TNodoSecuencia<TElem> ( elem, _ant -> sig( ) );
		 
       _ant -> _sig = nuevo;
		 
       _ant = nuevo;
		 
     };


     template <class TElem>
     TElem TSecuenciaDinamica<TElem>::actual( ) // throw ( EAccesoIndebido ) 
	 {
		 
       if( esFin( ) )
		   
         throw EAccesoIndebido3( "Error: el punto de interes este al final" );
		 
       return _ant -> sig( ) -> elem( );
		 
     };


     template <class TElem>
     void TSecuenciaDinamica<TElem>::borra( ) // throw ( EAccesoIndebido ) 
	 {
		 
       if( esFin( ) )
		   
         throw EAccesoIndebido3( "Error: el punto de interes esta al final" );
		 
       TNodoSecuencia<TElem>* act = _ant -> sig( );
		 
       _ant -> _sig = act -> sig( );
		 
       delete act;
		 
     };


     template <class TElem>
     void TSecuenciaDinamica<TElem>::avanza( ) // throw ( EAccesoIndebido ) 
	 {
		 
       if( esFin( ) )
		   
         throw EAccesoIndebido3( "Error: el punto de interes esta al final" );
		 
       _ant = _ant -> sig( );
		 
     };


     template <class TElem>
     void TSecuenciaDinamica<TElem>::reinicia( ) {
		 
       _ant = _pri;
		 
     };


     template <class TElem>
     bool TSecuenciaDinamica<TElem>::esFin( ) {
		 
       return _ant -> sig( ) == 0;
		 
     };


     template <class TElem>
     bool TSecuenciaDinamica<TElem>::esVacio( ) {
		 
       return _pri -> sig( ) == 0;
		 
     };

	 template <class TElem>
	void TSecuenciaDinamica<TElem>::concatena( TSecuenciaDinamica<TElem>& lista ){

    	lista.reinicia();
    
    	while ( ! lista.esFin() ) {
        
        	inserta(lista.actual());
        	lista.avanza();
        	
    	}
      
	}
  // Operaciones de entrada/salida

     template <class TElem>
     void TSecuenciaDinamica<TElem>::escribe( ) {
		 
	   cout << endl;
		 
       if ( _pri == _ant ) cout << "<--" << endl;
		 
       TNodoSecuencia<TElem>* tmp = _pri -> sig( );
		 
       while ( tmp != 0 ) {
		   
         cout << tmp -> elem( ) << endl;
		   
         if ( tmp == _ant ) cout << "<--" << endl;
		   
         tmp = tmp -> sig( );
		   
       }
		 
	   cout << endl;
		 
     };

     
   
//     
//     
//	 // EJERCICIO 2 PRACTICA 
//	 /*
//	 saltaHaciaDelante : secuencia nat -> secuencia
//	 saltaHaciaDelante(<iz,dr>,0) = <iz,dr>
//	 saltaHaciaDelante(<iz,pila-vacia>,n) = <iz,pila-vacia> <= n>0
//	 saltaHaciaDelante(<iz,apilar(e,dr)>,n) = saltaHaciaDelante(<apilar(e,iz),dr>,n-1) <= ¬es-pila-vacia?(dr) /\ n>0
//	 */
//	 template <class TElem>
//	 void TSecuenciaDinamica<TElem>::saltaHaciaDelante(int n){
//	 	while(!esFin() && n>0){
//	 		avanza();
//	 		n -= 1;
//		}
//	 }
//	 
//	 
//	 /*
//	 numElementosTratados : secuencia -> nat
//	 numElementosTratados(<pila-vacia,dr>) = 0 
//	 numElementosTratados(<apilar(e,iz),dr>) = 1 + numElementosTratados(<iz,dr>)
//	 
//	 */
//	 
//	 template <class TElem>
//	 int TSecuenciaDinamica<TElem>:: numElemTratados(){
//	 	int contador = 0;
//	 	TNodoSecuencia<TElem>* aux = _pri;
//	 	while (aux!= _ant){
//	 		aux = aux -> sig();
//	 		contador += 1;
//		 }
//		return contador;
//	 }
//	 
//	 
//	 /*
//	 palindroma: secuencia ---> bool
//	 palindroma(s) = true <= long(s) <= 1
//	 palindroma(s) = primero(s) == ultimo(s) and palindromo(quitarPrim(quitarUlt(s))) <= long(s) > 1
//	 */
//	 template <class TElem>
//	 bool TSecuenciaDinamica<TElem>::palindroma(){ // O(n) en tiempo de ejecucion (caso peor)
//	 	// O(n) en espacio o memoria auxiliar
//		TPila<TElem> p;
//	 	TColaDinamica<TElem> c; 
//	 	reinicia();
//	 	while(!esFin()){
//	 		p.apila(actual());
//	 		c.ponDetras(actual());
//	 		avanza();
//		}
//		bool palindroma = true;
//		while(palindroma && !c.esVacio()){
//			if (c.primero() != p.cima()) palindroma = false;
//			c.quitaPrim();
//			p.desapila();
//		}
//		return palindroma;
//	 }
	
#endif