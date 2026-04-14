#ifndef tabla_ordenadaH
#define tabla_ordenadaH


#include <iostream>
#include "secuencia_dinamica.h"

// Excepciones nuevas generadas por las operaciones de este TAD:
// Acceso cuando se accede con una clave que no esta en la tabla
// class EClaveErronea { };


/*
 
 especificación TABLAS[CLAVES, VALORES-MODIFICABLES]
 
 usa BOOLEANOS
 
 tipos tabla
 
 operaciones
 
    tabla-vacía     :                          -->   tabla       { constructora }
    ins-tabla       : clave valor tabla        -->   tabla       { constructora }
    está-tabla?     : clave tabla              -->   bool
    consultar-tabla : clave tabla              -/->  valor
    eliminar-tabla  : clave tabla              -->   tabla
    es-tabla-vacía? : tabla                    -->   bool
 
 variables
 
    c, d : clave
    v, w : valor
    t    : tabla
    
 ecuaciones
 
    ins-tabla(c, w, ins-tabla(c, v, t)) = ins-tabla(c, combinar(v, w), t)
    ins-tabla(d, w, ins-tabla(c, v, t)) = ins-tabla(c, v, ins-tabla(d, w, t)) <== c != d
 
    está-tabla?(c, tabla-vacía)         = falso
    está-tabla?(c, ins-tabla(d, v, t))  = c == d \/ está-tabla?(c, t)
 
    consultar-tabla(c, t)               = error   <== ¬está-tabla?(c, t)
 
    consultar-tabla(c, ins-tabla(c, v, t)) = v <== ¬está-tabla?(c, t)
    consultar-tabla(c, ins-tabla(c, v, t)) = combinar(consultar-tabla(c, t), v) <== está-tabla?(c, t)
    consultar-tabla(c, ins-tabla(d, v, t)) = consultar-tabla(c, t) <== c != d
 
    eliminar-tabla(c, tabla-vacía)      = tabla-vacía
    eliminar-tabla(c, ins-tabla(c, v, t))  = eliminar-tabla(c, t)
    eliminar-tabla(c, ins-tabla(d, v, t))  = ins-tabla(d, v, eliminar-tabla(c, t)) <== c != d
 
    es-tabla-vacía?(tabla-vacía)        = cierto
    es-tabla-vacía?(ins-tabla(c, v, t)) = falso
 
 fespecificación
 
*/

/*
 
 parámetro PARES-ORDENABLES
 
 usa CLAVES<, VALORES-MODIFICABLES
 
 tipos par
 
 operaciones
 
    <_,_> : clave valor    -->   par
    _<_   : clave clave    -->   bool
 
 variables
 
    c, d : clave
    v, w : valor
    
 ecuaciones
 
    <c, v> < <d, w>   =   c < d
 
 fparámetro
 
*/

/*
 
 especificación TABLAS-ORDENADAS[CLAVES<, VALORES-MODIFICABLES]
 
 usa TABLAS[CLAVES<, VALORES-MODIFICABLES],
     LISTAS-ORDENADAS[PARES-ORDENABLES]
 
 operaciones
 
    recorrer-ordenada : tabla   -->   lista[par]
 
 variables
 
    c : clave
    v : valor
    t : tabla
    
 ecuaciones
 
    recorrer-ordenada(tabla-vacía)      = []
    recorrer-ordenada(ins-tabla(c, v, t)) = insertar-ord(<c, v>, recorrer-ordenada(t)) <== ¬está-tabla?(c, t)
    recorrer-ordenada(ins-tabla(c, v, t)) = insertar-ord(<c, combinar(consultar-tabla(c, t), v)>, recorrer-ordenada(eliminar-tabla(c, t))) <== está-tabla?(c, t)
 
 fespecificación
 
*/

using namespace std;


// El tipo 'TClave' debe implementar:
//    operator==
//    operator<
//    operator>


template <class TClave, class TValor>
struct TPares {
    TClave clave;
    TValor valor;
};

template <class TClave, class TValor>
class TTablaOrdenada;


template <class TClave, class TValor>
class TNodoTabla {
	
  private:
	
    TClave _clave;
    TValor _valor;
	
    TNodoTabla<TClave,TValor> *_iz, *_dr;
	
    TNodoTabla( TClave, TValor, TNodoTabla<TClave,TValor>*, TNodoTabla<TClave,TValor>* );
	
  public:
	
    TClave clave();
    TValor valor();
	
    TNodoTabla<TClave,TValor>* iz();
    TNodoTabla<TClave,TValor>* dr();
	
    friend class TTablaOrdenada<TClave,TValor>;
	
};



template <class TClave, class TValor>
class TTablaOrdenada {
	
	
  public:

	
  // Constructoras
	
     TTablaOrdenada( );
     TTablaOrdenada( TTablaOrdenada<TClave,TValor>& );
    

  // Operaciones de los arboles de busqueda
	
     void inserta( TClave, TValor );
     // Pre  : true
     // Post : inserta un par (clave,valor) en la tabla
	 //        si la clave ya esta en la tabla, se sustituye el valor antiguo por el nuevo

     void elimina( TClave );
     // Pre  : true
     // Post : elimina un par (clave,valor) de la tabla a partir de una clave dada
     //        si la clave no esta, la tabla no se modifica

     TValor consulta( TClave ); // throw ( EClaveErronea );
     // Pre  : esta( clave )
     // Post : devuelve el valor asociado con la clave dada
     // Lanza la excepcion 'EClaveErronea' si la tabla no contiene dicha clave

     bool esta( TClave );
     // Pre  : true
     // Post : devuelve true o false segun si la tabla contiene o no la clave

     bool esVacio( );
     // Pre: true
     // Post: Devuelve true o false segun si la tabla esta o no vacia

	
  // Recorridos 
	
	 TSecuenciaDinamica<TValor> recorre( );
	 // Pre  : true
	 // Post : devuelve los valores de la tabla, ordenados por la clave
	
	 TSecuenciaDinamica<TClave> recorreClave( );
	 // Pre  : true
	 // Post : devuelve las claves de la tabla ordenadas
	
	 TSecuenciaDinamica< TPares<TClave, TValor> > recorrePares( );
     // Pre: true
     // Post: devuelve los pares (clave, valor) ordenados por clave
    
	
	 // Escritura
     void escribe( );

	
	
  private:

	
  // Variables privadas
	
     TNodoTabla<TClave,TValor>* _ra;
	
  // operacion privada de escritura
	
     void escribeAux( TNodoTabla<TClave, TValor>*, string );
	
  // operaciones auxiliares para los algoritmos recursivos
	
     void insertaAux( TClave, TValor, TNodoTabla<TClave, TValor>* &  );
	
	 TNodoTabla<TClave,TValor>* busca( TClave, TNodoTabla<TClave, TValor>* );
	
     void eliminaAux( TClave, TNodoTabla<TClave,TValor>* & );
     void eliminaRaiz( TNodoTabla<TClave,TValor>* & );
     void eliminaConMin( TNodoTabla<TClave,TValor>* &, TNodoTabla<TClave,TValor>* & );
	 
	 
	 void inOrdAcuPares( TNodoTabla<TClave,TValor>*, TSecuenciaDinamica< TPares<TClave, TValor> >& );
	
};



//---------------------------------------------------------------------------
//                              IMPLEMENTACION
//---------------------------------------------------------------------------



  // Clase de los nodos de la tabla ordenada

    template <class TClave, class TValor>
    TNodoTabla<TClave,TValor>::TNodoTabla( TClave clave, TValor valor, TNodoTabla<TClave,TValor>* iz, TNodoTabla<TClave,TValor>* dr ) :
      
	  _clave(clave), _valor(valor), _iz(iz), _dr(dr) {
	  	
    };


    template <class TClave, class TValor>
    TClave TNodoTabla<TClave,TValor>::clave( ) {
		
      return _clave;
		
    }


    template <class TClave, class TValor>
    TValor TNodoTabla<TClave,TValor>::valor( ) {
		
      return _valor;
		
    }


    template <class TClave, class TValor>
    TNodoTabla<TClave,TValor>* TNodoTabla<TClave,TValor>::iz( ) {
		
      return _iz;
		
    }


    template <class TClave, class TValor>
    TNodoTabla<TClave,TValor>* TNodoTabla<TClave,TValor>::dr( ) {
		
      return _dr;
		
    }


  // Constructoras de la clase de tablas ordenadas

     template <class TClave, class TValor>
     TTablaOrdenada<TClave,TValor>::TTablaOrdenada( ) :
     	
       _ra( 0 ) {
       	
     };


  // Operaciones de las tablas ordenadas


     // Insercion

     template <class TClave, class TValor>
     void TTablaOrdenada<TClave,TValor>::inserta( TClave clave, TValor valor ) {
		 
       insertaAux( clave, valor, _ra );
		 
     };


     template <class TClave, class TValor>
     void TTablaOrdenada<TClave,TValor>::insertaAux( TClave clave, TValor valor, TNodoTabla<TClave,TValor>* & p) {
		 
       if ( p == 0 )
		   
         p = new TNodoTabla<TClave,TValor>( clave, valor, 0, 0 );
		 
       else if ( clave == p -> clave( ) )
		   
         p -> _valor = valor;
		 
       else if ( clave < p -> clave( ) )
		   
         insertaAux( clave, valor, p -> _iz );
		 
       else
		   
         insertaAux( clave, valor, p -> _dr );
		 
     };



     // Eliminar

     template <class TClave, class TValor>
     void TTablaOrdenada<TClave,TValor>::elimina( TClave clave ) {
		 
       eliminaAux( clave, _ra );
		 
     };


     template <class TClave, class TValor>
     void TTablaOrdenada<TClave,TValor>::eliminaAux( TClave clave, TNodoTabla<TClave,TValor>* & p ) {
		 
       if ( p != 0 ) {
		   
         if ( clave == p -> clave( ) )
			 
           eliminaRaiz(p);
		   
         else if ( clave < p -> clave( ) )
			 
           eliminaAux( clave, p -> _iz );
		   
         else
			 
           eliminaAux( clave, p -> _dr );
		   
       }
		 
     };


     template <class TClave, class TValor>
     void TTablaOrdenada<TClave,TValor>::eliminaRaiz( TNodoTabla<TClave,TValor>* & p ) {
		 
       TNodoTabla<TClave,TValor>* aux;

       if ( p -> iz( ) == 0 ) {
		   
         aux = p;
         p = p -> dr( );
		   
         delete aux;
		   
       }
       else if ( p -> dr() == 0 ) {
		   
         aux = p;
         p = p -> iz();
		   
         delete aux;
		   
       }
       else
		   
         eliminaConMin( p, p -> _dr );
		 
     };


     template <class TClave, class TValor>
     void TTablaOrdenada<TClave,TValor>::eliminaConMin( TNodoTabla<TClave,TValor>* & p, TNodoTabla<TClave,TValor>* & q ) {
		 
       TNodoTabla<TClave,TValor>* aux;

       if ( q -> iz( ) != 0 )
		   
         eliminaConMin( p, q -> _iz );
		 
       else {
		   
         p -> _clave = q -> clave( );
         p -> _valor = q -> valor( );
		   
         aux = q;
         q = q -> dr( );
		   
         delete aux;
		   
       }
		 
     };
 
 

     // Consultas

     template <class TClave, class TValor>
     TValor TTablaOrdenada<TClave,TValor>::consulta( TClave clave ) // throw ( EClaveErronea ) 
	 {
		 
       TNodoTabla<TClave,TValor>* aux;

       aux = busca(clave, _ra);
		 
       if ( aux == 0 )
		   
         throw EClaveErronea3( "Error: la tabla ordenada no contiene la clave" );
		 
       else
		   
         return aux -> valor( );
		 
     };


     template <class TClave, class TValor>
     bool TTablaOrdenada<TClave,TValor>::esta( TClave clave ) {
		 
       return busca(clave, _ra) != 0;
		 
     };


     template <class TClave, class TValor>
     TNodoTabla<TClave,TValor>* TTablaOrdenada<TClave,TValor>::busca( TClave clave, TNodoTabla<TClave,TValor>* p ) {
		 
       TNodoTabla<TClave,TValor>* r;

       if ( p == 0 )
		   
         r = 0;
		 
       else if ( clave == p -> clave( ) )
		   
         r = p;
		 
       else if ( clave < p -> clave( ) )
		   
         r = busca( clave, p -> iz( ) );
		 
       else
		   
         r = busca( clave, p -> dr( ) );
		 
       return r;
		 
     };


     template <class TClave, class TValor>
     bool TTablaOrdenada<TClave,TValor>::esVacio( ) {
		 
       return _ra == 0;
		 
     };



  // Recorridos

     template <class TClave, class TValor>
     void inOrdAcu( TNodoTabla<TClave,TValor>* p, TSecuenciaDinamica<TValor>& xs ) {
		 
       if ( p != 0 ) {
		   
         inOrdAcu( p -> iz( ), xs );
		   
         xs.inserta( p -> valor( ) );
		   
         inOrdAcu( p -> dr( ), xs );
		   
       }
		 
     };


     template <class TClave, class TValor>
     TSecuenciaDinamica<TValor> TTablaOrdenada<TClave,TValor>::recorre( ) {
		 
       TSecuenciaDinamica<TValor> r;

       inOrdAcu( _ra, r );
		 
       return r;
		 
     };


     template <class TClave, class TValor>
     void inOrdAcuClave( TNodoTabla<TClave,TValor>* p, TSecuenciaDinamica<TClave>& xs ) {
		 
       if ( p != 0 ) {
		   
         inOrdAcuClave( p -> iz( ), xs );
		   
         xs.inserta( p -> clave( ) );
		   
         inOrdAcuClave( p -> dr( ), xs );
		   
       }
		 
     };


     template <class TClave, class TValor>
     TSecuenciaDinamica<TClave> TTablaOrdenada<TClave,TValor>::recorreClave( ) {
		 
       TSecuenciaDinamica<TClave> r;

       inOrdAcuClave( _ra, r );
		 
       return r;
		 
     };

 	 template <class TClave, class TValor>
     void  TTablaOrdenada<TClave,TValor>:: inOrdAcuPares( TNodoTabla<TClave,TValor>* p, TSecuenciaDinamica< TPares<TClave, TValor> >& xs ) {
       if ( p != 0 ) {
         inOrdAcuPares( p -> iz( ), xs );
           
         TPares<TClave, TValor> par;
         par.clave = p->clave();
         par.valor = p->valor();
         xs.inserta( par );
           
         inOrdAcuPares( p -> dr( ), xs );
       }
     };

     template <class TClave, class TValor>
     TSecuenciaDinamica< TPares<TClave, TValor> > TTablaOrdenada<TClave,TValor>::recorrePares( ) {
       TSecuenciaDinamica< TPares<TClave, TValor> > r;
       inOrdAcuPares( _ra, r );
       return r;
     };

  // Operaciones de escritura de tablas ordenadas


     template <class TClave, class TValor>
     void TTablaOrdenada<TClave,TValor>::escribeAux( TNodoTabla<TClave,TValor>* p, string prefijo ) {
		 
       if ( p != 0 ) {
		   
         cout << ( prefijo + " : " ) << "(" << p -> clave( ) << "," << p -> valor( ) << ")" << endl;
		   
         escribeAux( p -> iz( ), prefijo + ".1" );
         escribeAux( p -> dr( ), prefijo + ".2" );
		   
       }
		 
     }

	 

     template <class TClave, class TValor>
     void TTablaOrdenada<TClave,TValor>::escribe( ) {
		 
	   cout << endl;
		 
       escribeAux( _ra, "1" );
		 
     };


#endif