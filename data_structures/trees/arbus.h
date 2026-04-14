#ifndef arbusH
#define arbusH


#include <iostream>
#include "secuencia_dinamica.h"
#include <list>
#include <queue>
#include <cmath>

// Excepciones nuevas generadas por las operaciones de este TAD:
// Acceso cuando se accede con una clave que no esta en el arbol
// class EClaveErronea { };


/*
 
 especificación ÁRBOLES-BINARIOS-DE-BÚSQUEDA[ELEM=<]
 
 usa BOOLEANOS
 
 tipos árbol-bb
 
 operaciones
 
    abb-vacío      :                      -->   árbol-bb    { constructora }
    plantar        : árbol-bb elem árbol-bb -/-> árbol-bb   { constructora }
    insertar       : elem árbol-bb        -->   árbol-bb
    está?          : elem árbol-bb        -->   bool
    mínimo         : árbol-bb             -/->  elem
    máximo         : árbol-bb             -/->  elem
    eliminar       : elem árbol-bb        -->   árbol-bb
    es-abb-vacío?  : árbol-bb             -->   bool
 
 variables
 
    e, f   : elem
    iz, dr : árbol-bb
    
 ecuaciones
 
    plantar(iz, e, dr)                  = error   <== ¬(es-abb-vacío?(iz) \/ e > máximo(iz)) \/  ¬(es-abb-vacío?(dr) \/ e < mínimo(dr))
 
    insertar(e, abb-vacío)              = plantar(abb-vacío, e, abb-vacío)
    insertar(e, plantar(iz, e, dr))     = plantar(iz, e, dr)
    insertar(e, plantar(iz, f, dr))     = plantar(insertar(e, iz), f, dr)   <== e < f
    insertar(e, plantar(iz, f, dr))     = plantar(iz, f, insertar(e, dr))   <== e > f
 
    está?(e, abb-vacío)                 = falso
    está?(e, plantar(iz, e, dr))        = cierto
    está?(e, plantar(iz, f, dr))        = está?(e, iz)                      <== e < f
    está?(e, plantar(iz, f, dr))        = está?(e, dr)                      <== e > f
 
    mínimo(abb-vacío)                   = error
    mínimo(plantar(abb-vacío, e, dr))   = e
    mínimo(plantar(iz, e, dr))          = mínimo(iz)                        <== ¬es-abb-vacío?(iz)
 
    máximo(abb-vacío)                   = error
    máximo(plantar(iz, e, abb-vacío))   = e
    máximo(plantar(iz, e, dr))          = máximo(dr)                        <== ¬es-abb-vacío?(dr)
 
    eliminar(e, abb-vacío)              = abb-vacío
    eliminar(e, plantar(iz, e, abb-vacío)) = iz
    eliminar(e, plantar(abb-vacío, e, dr)) = dr
    eliminar(e, plantar(iz, e, dr))     = plantar(iz, mínimo(dr), eliminar(mínimo(dr), dr)) <== ¬es-abb-vacío?(iz) /\ ¬es-abb-vacío?(dr)
    eliminar(e, plantar(iz, f, dr))     = plantar(eliminar(e, iz), f, dr)   <== e < f
    eliminar(e, plantar(iz, f, dr))     = plantar(iz, f, eliminar(e, dr))   <== e > f
 
    es-abb-vacío?(abb-vacío)            = cierto
    es-abb-vacío?(plantar(iz, e, dr))   = falso
 
 fespecificación
 
*/

using namespace std;


// El tipo 'TClave' debe implementar:
//    operator==
//    operator<
//    operator>

template <class TClave, class TValor>
struct Par { 
    TClave clave;
    TValor valor;
    
    // Constructora vacia
    Par() {}; 
    // Constructora
    Par(TClave c, TValor v) : clave(c), valor(v) {};
    
};

template <class TClave, class TValor>
class TArbus;

template <class TClave, class TValor>
class TNodoArbus {
	
  private:
	
    TClave _clave;
    TValor _valor;
	
    TNodoArbus<TClave,TValor> *_iz, *_dr;
	
    TNodoArbus( TClave, TValor, TNodoArbus<TClave,TValor>*, TNodoArbus<TClave,TValor>* );
	
  public:
	
    TClave clave();
    TValor valor();
	
    TNodoArbus<TClave,TValor>* iz();
    TNodoArbus<TClave,TValor>* dr();
	
    friend class TArbus<TClave,TValor>;
	
};



template <class TClave, class TValor>
class TArbus {
	
	
  public:

	
  // Constructoras
	
     TArbus( );
     TArbus( TArbus<TClave,TValor>& );
    

  // Operaciones de los arboles de busqueda
	
     void inserta( TClave, TValor );
     // Pre  : true
     // Post : inserta un par (clave,valor) en el arbol
	 //        si la clave ya esta en el arbol, se sustituye el valor antiguo por el nuevo

     void borra( TClave );
     // Pre  : true
     // Post : elimina un par (clave,valor) del arbol a partir de una clave dada
     //        si la clave no esta, el arbol no se modifica

     TValor consulta( TClave ); // throw ( EClaveErronea );
     // Pre  : esta( clave )
     // Post : devuelve el valor asociado con la clave dada
     // Lanza la excepcion 'EClaveErronea' si el arbol no contiene dicha clave

     bool esta( TClave );
     // Pre  : true
     // Post : devuelve true o false segun si el arbol contiene o no la clave

     bool esVacio( );
     // Pre: true
     // Post: Devuelve true o false segun si el arbol esta o no vacio

	
  // Recorridos 
	
	 TSecuenciaDinamica<TValor> recorre( );
	 // Pre  : true
	 // Post : devuelve los valores del arbol, ordenados por la clave
	
	 TSecuenciaDinamica<TClave> recorreClave( );
	 // Pre  : true
	 // Post : devuelve las claves del arbol ordenadas
	
	
	void escribe();
	
	
	
	
	
	

  // EJERCICIO HOJA 4
  
  TClave minimo();
  //Pre: el árbol no sea vacío
  //Post: devuelve la clave mínima en el árbol 
  // 0(n), siendo n el 	numero de nodos del arbus (logn si es AVL)
	
  TClave anterior(TClave);
  //Pre: el arbol no sea vacio o la clave no sea la minima 
  //Post: devuelve la clave anterior en orden a una dada del arbus 
  // 0(n), siendo n el 	numero de nodos del arbus (logn si es AVL)
  
  TArbus<TClave, TValor> creaArbol(TSecuenciaDinamica<TClave>);
  //Pre: True
  //Post: devuelve un arbol dada una secuencia (insertados en el orden de aparicion)
  //O(n^2) siendo n el numero de nodos	(O(nlogn) en caso de AVL)
  	
  TSecuenciaDinamica<TClave> obtenerSec();
  //Pre: True
  //Post: devuelve una secuencia ordenada de las claves
  //O(n) siendo n el numero de nodos
	
  TSecuenciaDinamica<TClave> obtenerMenores(TClave);
  //Pre: True
  //Post: devuelve una secuencia ordenada de las claves menores a la clave dada
  //O(n) siendo n el numero de nodos
	
  TValor minimo_valor();
  //Pre: el árbol no sea vacío
  //Post: devuelve el valor asociado a la clave mínima en el árbol 
  // 0(n), siendo n el numero de nodos del arbus
	
  TClave maximo_clave();
  //Pre: el árbol no sea vacío
  //Post: devuelve el valor asociado a la clave mínima en el árbol 
  // 0(n), siendo n el numero de nodos del arbus
	
	
	
	
	
  int numHojasProfundas(int );
  bool zurdo();
  //TListaDinamica<TClave> perfil();
  
  TClave siguiente(TClave );
  //Pre: si es una hoja da error
  //Post: devuelve la clave siguiente del arbol dado un elemento dado 
	
  TSecuenciaDinamica<TClave> enRango(TClave , TClave);
  //Pre: que la cota inferior sea menor que la cota superior
  //Post: devuelve la secuencia de los elementos comprendidos entre esas dos claves
  // 0(n), siendo n el numero de nodos del arbus
  

  int numEnRango(TClave , TClave);
  //Pre: que la cota inferior sea menor que la cota superior
  //Post: devuelve el numero de elementos comprendidos entre esas dos claves
  // 0(n), siendo n el numero de nodos del arbus
  
	
  bool equilibrado();
  //Pre: true
  //Post: dice si un arbol es o no es equilibrado
  // 0(n), siendo n el numero de nodos del arbus
  	
  private:

	
  // Variables privadas
	
     TNodoArbus<TClave,TValor>* _ra;
	
  // operacion privada de escritura
	
     void escribeAux( TNodoArbus<TClave, TValor>*, string );
	
  // operaciones auxiliares para los algoritmos recursivos
	
     void insertaAux( TClave, TValor, TNodoArbus<TClave, TValor>* &  );
	
	 TNodoArbus<TClave,TValor>* busca( TClave, TNodoArbus<TClave, TValor>* );
	
     void borraAux( TClave, TNodoArbus<TClave,TValor>* & );
     void borraRaiz( TNodoArbus<TClave,TValor>* & );
     void borraConMin( TNodoArbus<TClave,TValor>* &, TNodoArbus<TClave,TValor>* & );
	 
  //operacion auxiliar para ej Hoja 4
  
	TClave minimo_aux(TNodoArbus<TClave, TValor>* );
	TClave anterior_aux(TNodoArbus<TClave, TValor>* , TClave );
	void obtenerSecAux(TNodoArbus<TClave, TValor>* , TSecuenciaDinamica<TClave>&);
	void obtenerMenoresAux(TNodoArbus<TClave,TValor>* , TSecuenciaDinamica<TClave>& , TClave);
	
	TValor minimo_valor_aux(TNodoArbus<TClave, TValor>* );
	TClave maximo_clave_aux(TNodoArbus<TClave, TValor>* );
	
	int numHojasProfundas_aux(int , TNodoArbus<TClave,TValor>* );
	bool zurdo_aux(TNodoArbus<TClave,TValor>* , int& );
	//void perfil_aux(TNodoArbus<TClave,TValor>* , TListaDinamica<TClave>& , int);
	TClave siguiente_aux(TClave ,TNodoArbus<TClave,TValor>* );
	
	void enRango_aux(TClave, TClave, TNodoArbus<TClave,TValor>* , TSecuenciaDinamica<TClave>& );
  	int numEnRango_aux(TClave, TClave, TNodoArbus<TClave,TValor>*);
  	
  	bool equilibrado_aux(TNodoArbus<TClave,TValor>* , int& );
};



//---------------------------------------------------------------------------
//                              IMPLEMENTACION
//---------------------------------------------------------------------------



  // Clase de los nodos del arbol de busqueda

    template <class TClave, class TValor>
    TNodoArbus<TClave,TValor>::TNodoArbus( TClave clave, TValor valor,  TNodoArbus<TClave,TValor>* iz, TNodoArbus<TClave,TValor>* dr ) :
      _clave(clave), _valor(valor), _iz(iz), _dr(dr) {
    };


    template <class TClave, class TValor>
    TClave TNodoArbus<TClave,TValor>::clave( ) {
		
      return _clave;
		
    }


    template <class TClave, class TValor>
    TValor TNodoArbus<TClave,TValor>::valor( ) {
		
      return _valor;
		
    }


    template <class TClave, class TValor>
    TNodoArbus<TClave,TValor>* TNodoArbus<TClave,TValor>::iz( ) {
		
      return _iz;
		
    }


    template <class TClave, class TValor>
    TNodoArbus<TClave,TValor>* TNodoArbus<TClave,TValor>::dr( ) {
		
      return _dr;
		
    }


  // Constructoras de la clase de arboles de busqueda

     template <class TClave, class TValor>
     TArbus<TClave,TValor>::TArbus( ) :
       _ra( 0 ) {   // _ra *--> ||
     };


  // Operaciones de los arboles de busqueda


     // Insercion

     template <class TClave, class TValor>
     void TArbus<TClave,TValor>::inserta( TClave clave, TValor valor ) {
		 
       insertaAux( clave, valor, _ra );
		 
     };


     template <class TClave, class TValor>
     void TArbus<TClave,TValor>::insertaAux( TClave clave, TValor valor, TNodoArbus<TClave,TValor>* & p) {
		 
       if ( p == 0 )
		   
         p = new TNodoArbus<TClave,TValor>( clave, valor, 0, 0 );
		 
       else if ( clave == p -> clave( ) )
		   
         p -> _valor = valor;
		 
       else if ( clave < p -> clave( ) )
		   
         insertaAux( clave, valor, p -> _iz );
		 
       else
		   
         insertaAux( clave, valor, p -> _dr );
		 
     };



     // Borrado

     template <class TClave, class TValor>
     void TArbus<TClave,TValor>::borra( TClave clave ) {
		 
       borraAux( clave, _ra ); 
		 
     };


     template <class TClave, class TValor>
     void TArbus<TClave,TValor>::borraAux( TClave clave, TNodoArbus<TClave,TValor>* & p ) {
		 
       if ( p != 0 ) {
		   
         if ( clave == p -> clave( ) )
			 
           borraRaiz(p);
		   
         else if ( clave < p -> clave( ) )
			 
           borraAux( clave, p -> _iz );
		   
         else
			 
           borraAux( clave, p -> _dr );
		   
       }
		 
     };


     template <class TClave, class TValor>
     void TArbus<TClave,TValor>::borraRaiz( TNodoArbus<TClave,TValor>* & p ) {
		 
       TNodoArbus<TClave,TValor>* aux;

       if ( p -> iz( ) == 0 ) {
		   
         aux = p;
         p = p -> dr( );
         //aux -> dr = 0; ??
		   
         delete aux;
		   
       }
       else if ( p -> dr() == 0 ) {
		   
         aux = p;
         p = p -> iz();
		   
         delete aux;
		   
       }
       else
		   
         borraConMin( p, p -> _dr );
		 
     };


     template <class TClave, class TValor>
     void TArbus<TClave,TValor>::borraConMin( TNodoArbus<TClave,TValor>* & p, TNodoArbus<TClave,TValor>* & q ) {
		 
       TNodoArbus<TClave,TValor>* aux;

       if ( q -> iz( ) != 0 )
		   
         borraConMin( p, q -> _iz );
		 
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
     TValor TArbus<TClave,TValor>::consulta( TClave clave ) // throw ( EClaveErronea ) 
	 {
		 
       TNodoArbus<TClave,TValor>* aux;

       aux = busca(clave, _ra);
		 
       if ( aux == 0 )
		   
         throw EClaveErronea3( "Error: el arbol no contiene la clave" );
		 
       else
		   
         return aux -> valor( );
		 
     };


     template <class TClave, class TValor>
     bool TArbus<TClave,TValor>::esta( TClave clave ) {
		 
       return busca(clave, _ra) != 0;
		 
     };


     template <class TClave, class TValor>
     TNodoArbus<TClave,TValor>* TArbus<TClave,TValor>::busca( TClave clave, TNodoArbus<TClave,TValor>* p ) {
		 
       TNodoArbus<TClave,TValor>* r;

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
     bool TArbus<TClave,TValor>::esVacio( ) {
		 
       return _ra == 0;
		 
     };



  // Recorridos

     template <class TClave, class TValor>
     void inOrdAcu( TNodoArbus<TClave,TValor>* p, TSecuenciaDinamica<TValor>& xs ) {
		 
       if ( p != 0 ) {
		   
         inOrdAcu( p -> iz( ), xs );
		   
         xs.inserta( p -> valor( ) );
		   
         inOrdAcu( p -> dr( ), xs );
		   
       }
		 
     };


     template <class TClave, class TValor>
     TSecuenciaDinamica<TValor> TArbus<TClave,TValor>::recorre( ) {
		 
       TSecuenciaDinamica<TValor> r;

       inOrdAcu( _ra, r );
		 
       return r;
		 
     };


     template <class TClave, class TValor>
     void inOrdAcuClave( TNodoArbus<TClave,TValor>* p, TSecuenciaDinamica<TClave>& xs ) {
		 
       if ( p != 0 ) {
		   
         inOrdAcuClave( p -> iz( ), xs );
		   
         xs.inserta( p -> clave( ) );
		   
         inOrdAcuClave( p -> dr( ), xs );
		   
       }
		 
     };


     template <class TClave, class TValor>
     TSecuenciaDinamica<TClave> TArbus<TClave,TValor>::recorreClave( ) {
		 
       TSecuenciaDinamica<TClave> r;

       inOrdAcuClave( _ra, r );
		 
       return r;
		 
     };

 

  // Operaciones de escritura de arboles binarios de busqueda


     template <class TClave, class TValor>
     void TArbus<TClave,TValor>::escribeAux( TNodoArbus<TClave,TValor>* p, string prefijo ) {
		 
       if ( p != 0 ) {
		   
         cout << ( prefijo + " : " ) << "(" << p -> clave( ) << "," << p -> valor( ) << ")" << endl;
		   
         escribeAux( p -> iz( ), prefijo + ".1" );
         escribeAux( p -> dr( ), prefijo + ".2" );
		   
       }
		 
     }


     template <class TClave, class TValor>
     void TArbus<TClave,TValor>::escribe( ) {
		 
	   cout << endl;
		 
       escribeAux( _ra, "1" );
		 
     };
	
	// EJERCICIO HOJA 4
	
	/*
		minimo: arbus -/-> valor
		iz,dr: arbin c:clave, v:valor
		minimo(arbol_vacio)= error
		minimo(plantar(iz,c,v,dr)) = v          <= es-arbol-vacio(iz)
		minimo(plantar(iz,c,v,dr)) = minimo(iz) <= ¬es-arbol-vacio(iz)
	*/
	//esta operación a la parte pública. minimo_aux() a la parte privada
	template <class TClave, class TValor>
	TClave TArbus<TClave, TValor>:: minimo(){
		if (esVacio()) throw EAccesoIndebido3("Error: el arbol esta vacio");
		else return minimo_aux(_ra);
	}
	
	template <class TClave, class TValor>
	TClave TArbus<TClave, TValor>::minimo_aux(TNodoArbus<TClave, TValor>* r){
		if (r->iz() == 0) return r-> _clave;
		else return minimo_aux(r->iz());
	}

	/*
	anterior: arbus clave -/-> clave
	iz,dr: arbus    c,d: clave  v,w: valor
	anterior(arbol-vacio, c) = error
	anterior(arbol, c) = error      <--- c <= minimo(arbol) and !esVacio(arbol)
	anterior(plantar(iz,c,v,dr),d) = anterior(iz,z) <= d < c
	anterior(plantar(iz,c,v,dr),d) = maximo(iz) <= d == c
	anterior(plantar(iz,c,v,dr),d) = c <--- d > c /\ d == minimo(dr)
	anterior(plantar(iz,c,v,dr),d) = anterior(dr,d) <= d>c 
	*/
	
	template <class TClave, class TValor>
	TClave TArbus<TClave, TValor>:: anterior(TClave c){
		if (esVacio()) throw EAccesoIndebido3("Error: el arbol esta vacio");
		if ( c <= minimo()) throw EAccesoIndebido3("Error: es el minimo, no hay una clave menor");
		else return anterior_aux(_ra, c);
	}
	
	template <class TClave, class TValor>
	TClave TArbus<TClave, TValor>::anterior_aux(TNodoArbus<TClave, TValor>* r, TClave c){
		//if (r -> iz() != 0){ NO HACE FALTA VERLO PUES YA HA PASADO LA CRIBA ANTERIOR
		if ((r-> dr() != 0) &&minimo_aux(r -> dr())  == c ) return r->clave(); 		
		else if((r -> clave())  == c ) return maximo_clave_aux(r-> iz());			 
		else if((r -> clave())  > c ) return anterior_aux(r->iz(), c);			 
		else return anterior_aux(r->dr(), c);
	}
	
	/*
	
	analogo a un buscar, que sera en caso peor lineal y en un AVL logaritmico
	
	*/
	
	/*
	 
	 creaArbol: secuencia -> arbin
	 creaArbol: secuencia-vacia -> arbol-vacio
	 creaArbol: insertar(par,s) -> insertar(par,creaArbol(s))
	 
	*/ 

	
	
	template <class TClave, class TValor>
	TArbus<TClave, TValor> TArbus<TClave, TValor>::creaArbol(TSecuenciaDinamica<TClave> s){
    	TArbus<TClave, TValor> a;
   		s.reinicia();
    	while (!s.esFin()){
    	    a.inserta(s.actual(),1);
    	    s.avanza();
    	}
        return a;
	}
	
	/*
	
	tomando el tamano de dato n = el numero de nodos 
	La complejidad sera O(n^2) si es degenerado y O(nlogn)  si es AVL  (un bucle recorre los elementos y luego por cada uno insertar O(altura))
	
	*/
	
//	
//		template <class TClave, class TValor>
//	TArbus<TClave, TValor> TArbus<TClave, TValor>::creaArbol(TSecuenciaDinamica<Par<TClave,TValor>> s){
//    	TArbus<TClave, TValor> a;
//   		s.reinicia();
//    	while (!s.esFin()){
//    	    a.inserta(s.actual());
//    	}
//	}
	
	/*
	
	obtenerSec: arbus -> secuencia
	obtenerSec(arbol-vacio) = secuencia-vacia
	obtenerSec(plantar(iz,c,v,dr))= obtenerSec(iz) ++ insertar(c,secuencia-vacia) ++ obtenerSec(iz) 
	 
	*/
	
	template <class TClave, class TValor>
	TSecuenciaDinamica<TClave> TArbus<TClave, TValor>:: obtenerSec(){
		TSecuenciaDinamica<TClave> s;
		obtenerSecAux(_ra, s);
		return s;
	}
	
	template <class TClave, class TValor>
	void TArbus<TClave, TValor>:: obtenerSecAux(TNodoArbus<TClave,TValor>* r, TSecuenciaDinamica<TClave>& s){
		if (r == 0) return;
		else{
			obtenerSecAux(r-> iz(), s);
			s.inserta(r-> clave());
			obtenerSecAux(r-> dr(), s);
		}
	}
	
	 /* 
	
	Tamaño de los datos n siendo n el número de nodos del arbin
			
			/ k0 si n=0
	T(n) = |
			\ T(p) + T(q) + k1 si n>0
			
	con p,q numero nodos del HI y del HD respectivamente tq p + q + 1 = n, k1, k2 ctes positivas 
	
	T(n) tendrá coste lineal O(n) (pues es analogo a como vimos el coste de altura en el ejercicio 6.6) 
	
	*/
	
	
	
	/*
	
	obtenerMenores: arbus clave-> secuencia
	obtenerMenores(arbol-vacio, d) = secuencia-vacia
	obtenerMenores(plantar(iz,c,v,dr),d) = obtenerMenores(iz,d) ++ insertar(c,secuencia-vacia) ++ obtenerMenores(iz,d) <= c < d
	obtenerMenores(plantar(iz,c,v,dr),d) = obtenerMenores(iz,d) <= c >= d
	
	*/
	
	template <class TClave, class TValor>
	TSecuenciaDinamica<TClave> TArbus<TClave, TValor>:: obtenerMenores(TClave c){
		TSecuenciaDinamica<TClave> s;
		obtenerMenoresAux(_ra, s, c);
		return s;
	}
	
	template <class TClave, class TValor>
	void TArbus<TClave, TValor>:: obtenerMenoresAux(TNodoArbus<TClave,TValor>* r, TSecuenciaDinamica<TClave>& s, TClave c){
		if (r == 0) return;
		else if ((r -> clave()) < c){
			obtenerMenoresAux(r-> iz(), s,c);
			s.inserta(r-> clave());
			obtenerMenoresAux(r-> dr(), s,c);
		}
		else{
			obtenerMenoresAux(r-> iz(), s,c);
		}
	}
	
	 /* 
	
	Tamaño de los datos n siendo n el número de nodos del arbin
			
			/ k0 si n=0
	T(n) = |
			\ T(p) + T(q) + k1 si n>0
			
	con p,q numero nodos del HI y del HD respectivamente tq p + q + 1 = n, k1, k2 ctes positivas 
	
	T(n) tendrá coste lineal O(n) (pues es analogo a como vimos el coste de altura en el ejercicio 6.6) 
	
	*/

	
	
	/*
	 maximo: arbus -/-> clave
	 iz,dr: arbus    c: clave  v: valor
	 maximo(arbol-vacio) = error
	 maximo(plantar(iz,c,v,dr)) = c <= es-arbol-vacio?(dr)
	 maximo(plantar(iz,c,v,dr))= maximo(dr)  <= ¬es-arbol-vacio?(dr)
	*/
	
	template <class TClave, class TValor>
	TValor TArbus<TClave, TValor>:: minimo_valor(){
		if (esVacio()) throw EAccesoIndebido3("Error: el arbol esta vacio");
		else return minimo_aux(_ra);
	}
	
	template <class TClave, class TValor>
	TValor TArbus<TClave, TValor>::minimo_valor_aux(TNodoArbus<TClave, TValor>* r){
		if (r->iz() == 0) return r-> _clave;
		else return minimo_aux(r->iz());
	}
	
	
	template <class TClave, class TValor>
	TClave TArbus<TClave, TValor>:: maximo_clave(){
		if (esVacio()) throw EAccesoIndebido3("Error: el arbol esta vacio");
		else return maximo_clave_aux(_ra);
	}
	
	template <class TClave, class TValor>
	TClave TArbus<TClave, TValor>::maximo_clave_aux(TNodoArbus<TClave, TValor>* r){
		if (r->dr() == 0) return r-> _clave;
		else return maximo_clave_aux(r->dr());
	}
	
	/*
	template <class TClave, class TValor>
	TValor TArbus<TClave,TValor>::anterior(TClave z){
    if (esVacio()) throw EAccesoIndebido( "Error: arbol vacio" );
    else if (z<=minimo()) throw EAccesoIndebido( "Error: no hay valor mas peque" );
    else {
        TNodoArbus<TClave,TValor>* a = _ra;
        while (true) {
             if (z>a->_clave && (a->_dr==0 || z<=a->_dr->_clave)) return a->_valor;
             else if (z<=a->_clave) a=a->_iz;
             else if (z>a->_clave && z>a->_dr->_clave) a=a->_dr;
        }
    }
}
	*/









	/*
	numHojasProfundas: arbus nat -> nat
	numHojasProfundas(arbol-vacio, n) = 0
	numHojasProfundas(arb,n) = 0 <-- n > altura(arb)
	numHojasProfundas(arb,0) = numHojas(arb)
	numHojasPrfoundas(plantar(iz,e,dr),n)) = numHojasPrfoundas(iz,n-1) + numHojasPrfoundas(dr,n-1)
	*/
	
	template<class TClave,class TValor>
	int TArbus<TClave, TValor>::numHojasProfundas(int n){
		return numHojasProfundas_aux(n, _ra);
	}
	
	template<class TClave,class TValor>
	int TArbus<TClave, TValor>::numHojasProfundas_aux(int n, TNodoArbus<TClave,TValor>* r){
		
		if (r == 0) return 0;
		else if (n!=0){ //  && r -> iz() != 0 && r -> dr() != 0
			return numHojasProfundas_aux(n-1, r -> iz()) + numHojasProfundas_aux(n-1, r -> dr());
		}
		else{
			if (r -> iz() == 0 && r -> dr() == 0) return 1;
			//else if (r -> iz() != 0) return numHojasProfundas_aux(n,r -> iz());
			else return numHojasProfundas_aux(n,r -> iz()) + numHojasProfundas_aux(n,r -> dr());
			
			
		}
	}


	/*
	zurdo: arbus -> bool
	zurdo(arbol-vacio) = true
	zurdo(plantar(arbol-vacio,e,arbol-vacio)) = true
	zurdo(plantar(iz,e,dr)) = true <-- numNodos(iz) > numNodos(dr) ^ zurdo(iz) ^ zurdo(dr)
	zurdo(plantar(iz,e,dr)) = false <-- numNodos(iz) <= numNodos(dr) v ¬zurdo(iz) v ¬zurdo(dr) 
	*/

	template<class TClave, class TValor>
	bool TArbus<TClave, TValor>:: zurdo(){
		int n = 0;
		return zurdo_aux(_ra, n);
	}
	
	template<class TClave, class TValor>
	bool TArbus<TClave, TValor>:: zurdo_aux(TNodoArbus<TClave,TValor>* r, int& n){
		
		if (r == 0 ) return true;
		if (r -> dr() == 0  && r -> iz() == 0){
			n++;
			return true;
		} 
		
		else{
			int m = n;
			if (zurdo_aux(r-> iz(), n) && zurdo_aux(r-> dr(), m)){
				if (n  > m){
					n = n+m+1;
					return true;
				}
				else return false;
			}
			else return false;
				
		}
		
	}
	
	/*
	
	siguiente: arbus -/-> clave
	siguiente(arbol-vacio,e) = error
	siguiente(arb,e) = error <= maximo(arb) < e
	siguiente(plantar(iz,e,dr),e) = minimo(dr) <= !esVacio(dr) 
	siguiente(plantar(iz,e,dr),f) = e <= !esVacio(iz) /\ maximo(iz)==f 
	siguiente(plantar(iz,e,dr),f) = siguiente(iz) <= e > f /\ maximo(iz) > f 
	siguiente(plantar(iz,e,dr),f) = siguiente(dr) <= e < f  
	
	
	*/
	
	
	template<class TClave, class TValor>
	TClave TArbus<TClave, TValor>:: siguiente(TClave e){
		if ( esVacio() ) throw EAccesoIndebido3("Error: el arbol esta vacio");
		else if ( e >= maximo_clave()) throw EAccesoIndebido3("Error: es el maximo, no hay una clave mayor");
		else return siguiente_aux(e, _ra);
	}
	
	template<class TClave, class TValor>
	TClave TArbus<TClave, TValor>:: siguiente_aux(TClave e, TNodoArbus<TClave,TValor>* r){
		if (e < r -> clave() && maximo_clave_aux(r -> _iz) > e) return siguiente_aux(e, r -> _iz);
		else if (e > r -> clave() && r -> dr()) return siguiente_aux(e, r ->_dr);
		else if (maximo_clave_aux(r -> _iz) == e) return r->clave();
		else if ((r -> clave()) == e) return minimo_aux(r->_dr);
		throw EAccesoIndebido3("elemento no encontrado");
	}
	
	/*
	enRango: arbus clave clave -/-> secuencia
	enRango(arbolvacio, b, a) = error <- b > a 
	enRango(arbolvacio, a, b) = sec-vacia
	enRango(plantar(iz,e,dr),a,b)=enRango(dr) <= e <= a 
	enRango(plantar(iz,e,dr),a,b)=enRango(iz) <= e >= b
	enRango(plantar(iz, e, dr),a,b)= concat(enRango(iz),insertar(e,enRango(dr))) <=  a < e < b
	*/

	template<class TClave, class TValor>
	TSecuenciaDinamica<TClave> TArbus<TClave, TValor>:: enRango(TClave a, TClave b){
		if (b<a) throw EAccesoIndebido3("Error: la cota inferior debe ser menor que la cota superior");
		TSecuenciaDinamica<TClave> s;
		enRango_aux(a,b, _ra, s);
		return s;
	}
	
	template<class TClave, class TValor>
	void TArbus<TClave, TValor>:: enRango_aux(TClave a, TClave b, TNodoArbus<TClave,TValor>* r, TSecuenciaDinamica<TClave>& s){
		if (r==0) return;
		else if (a >= r -> clave()) return enRango_aux(a,b,r->_dr,s);
		else if (b <= r -> clave()) return enRango_aux(a,b,r->_iz,s);
		else{
			enRango_aux(a,b,r->_iz,s);
			s.inserta(r-> _clave);
			enRango_aux(a,b,r->_dr,s);
		}	
	}
	
	/*
	enRango: arbus clave clave -/-> secuencia
	enRango(arbolvacio, b, a) = error <- b > a 
	enRango(arbolvacio, a, b) = sec-vacia
	enRango(plantar(iz,e,dr),a,b)=enRango(dr) <= e <= a 
	enRango(plantar(iz,e,dr),a,b)=enRango(iz) <= e >= b
	enRango(plantar(iz, e, dr),a,b)= enRango(iz) + 1 + enRango(dr) <=  a < e < b
	*/
	
	template<class TClave, class TValor>
	int TArbus<TClave, TValor>:: numEnRango(TClave a, TClave b){
		if (b<a) throw EAccesoIndebido3("Error: la cota inferior debe ser menor que la cota superior");
		return numEnRango_aux(a,b, _ra);
	}
	
	template<class TClave, class TValor>
	int TArbus<TClave, TValor>:: numEnRango_aux(TClave a, TClave b, TNodoArbus<TClave,TValor>* r){
		if (r==0) return 0;
		else if (a >= r -> clave()) return numEnRango_aux(a,b,r->_dr);
		else if (b <= r -> clave()) return numEnRango_aux(a,b,r->_iz);
		else{
			return numEnRango_aux(a,b,r->_iz) + 1 + numEnRango_aux(a,b,r->_dr);
		}	
	}
	
	/*
	equilibrado: arbus -> bool
	equilibrado(arbol-vacio) = true
	equilibrado(plantar(iz,e,dr)) = false <=  abs(altura(iz)-altura(iz))> 1
	equilibrado(plantar(iz,e,dr)) = true <= equilibrado(iz) /\ equilibrado(dr) /\ abs(altura(iz)-altura(iz))<= 1
	*/
	
	
	
	template<class TClave, class TValor>
	bool TArbus<TClave, TValor>:: equilibrado(){
		int n;
		return equilibrado_aux(_ra, n);
	}
	
	template<class TClave, class TValor>
	bool TArbus<TClave, TValor>:: equilibrado_aux(TNodoArbus<TClave,TValor>* r,  int& n){
	if (r == 0){
		n=0;
		return true;
	}
	else{
		int m = n;
		if (equilibrado_aux(r-> _iz, n) && equilibrado_aux(r-> _dr, m)){
			if (abs(n-m)<= 1){
				n = 1 + max(n,m); 
				return true;	
			}
			else return false;
			}
		else return false;
		}
	}
		
	
	
	
/*
	template<class TClave, class TValor>
	TListaDinamica<TClave> TArbus<TClave, TValor>:: perfil(){
		TListaDinamica<TClave> ls;
		int n = 0;
		perfil_aux(_ra, ls, n);
		return ls;
	}

/

	template<class TClave, class TValor>
	void TArbus< TClave, TValor>:: perfil_aux(TNodoArbus<TClave,TValor>* r, TListaDinamica<TClave>& ls, int n){
		
		
		if (r == 0) return;
		else if (ls.numElem() == n){
			ls.ponDetras(r->elem());
		}
		perfil_aux(r -> iz(), ls, n+1);
		perfil_aux(r -> dr(), ls, n+1);
	}
*/


/*
template <class TClave, class TValor>
TSecuenciaDinamica<TClave> TArbus<TClave, TValor>::recorreNiveles() {
    TSecuenciaDinamica<TClave> resultado;

    // Si el árbol está vacío, devolvemos la secuencia vacía
    if (this->esVacio()) {
        return resultado;
    }

    // Usamos una cola de punteros a nodos
    std::queue<TNodoArbus<TClave, TValor>*> cola;

    // 1. Encolamos la raíz
    cola.push(_ra);

    // 2. Bucle mientras haya elementos en la cola
    while (!cola.empty()) {
        // Obtenemos el primer elemento de la cola (frente)
        TNodoArbus<TClave, TValor>* actual = cola.front();
        cola.pop(); // Lo sacamos de la cola

        // Procesamos el nodo (guardamos su clave en la secuencia resultado)
        resultado.inserta(actual->clave());

        // Encolamos los hijos si existen (primero Izq, luego Der)
        // Esto coincide con la lógica de la imagen: "si no es vacío hijo, pedir-vez"
        if (actual->iz() != 0) {
            cola.push(actual->iz());
        }
        if (actual->dr() != 0) {
            cola.push(actual->dr());
        }
    }

    return resultado;
}
*/ 


	







#endif