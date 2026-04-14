#ifndef arbin_dinamicoH
#define arbin_dinamicoH

 // para poder poner el include bien ponemos lo de arriba, para no tener que llamar muchas veces en el otro archivo

#include <iostream>
#include "secuencia_dinamica.h"


using namespace std;



template <class TElem>
class TArbinDinamico;

// LA EMPRESITA QUE CONSTRUYE LOS NODOS
template <class TElem>
class TNodoArbin {  
	
  private:
	
    TElem _elem;
    TNodoArbin<TElem> *_iz, *_dr;
	
    TNodoArbin( TElem, TNodoArbin<TElem>*, TNodoArbin<TElem>* ); //CONSTRUCTORA PLANTAR(E, HI, HD)
	
  public:
	
    TElem& elem(); // DEVOLVEMOS LA REFERENCIA DEL ELEMENTO, NO EL ELEMENTO EN SÍ, DEVOLVEMOS EL PUNTERO
    TNodoArbin<TElem>* iz();
    TNodoArbin<TElem>* dr();
	
    friend class TArbinDinamico<TElem>;
	//TRABAJA PARA ESA CLASE
};



template <class TElem>
class TArbinDinamico {
	
  public:
 
  // Constructoras
	
	//ARBOL VACÍO
     TArbinDinamico( ); 
	//PLANTAR
     TArbinDinamico( TArbinDinamico<TElem>&, TElem, TArbinDinamico<TElem>& );
	
	
  // Operaciones de los arboles
  
	 TArbinDinamico<TElem> hijoIz( ); // throw ( EAccesoIndebido );
     // Pre  : ! esVacio( )
     // Post : devuelve una copia del subarbol izquierdo
     // Lanza la excepcion 'EAccesoIndebido' si el arbol esta vacio
	//O(1)
	
     TArbinDinamico<TElem> hijoDr ( ); // throw ( EAccesoIndebido );
     // Pre  : ! esVacio( )
     // Post : devuelve una copia del subarbol derecho
     // Lanza la excepcion 'EAccesoIndebido' si el arbol esta vacio
	//O(1)

     TElem raiz( ); // throw ( EAccesoIndebido );
     // Pre  : ! esVacio( )
     // Post : devuelve el elemento almacenado en la raiz
     // Lanza la excepcion 'EAccesoIndebido' si el arbol esta vacio
	//O(1)
	
     bool esVacio( );
     // Pre : true
     // Post: Devuelve true o false segun si el arbol esta o no vacio
	// O(1)
			
  // Recorridos de arboles
	
	 TSecuenciaDinamica<TElem> preOrd( );
	 // Pre  : true
	 // Post : devuelve el recorrido en pre-orden del arbol
	
	 TSecuenciaDinamica<TElem> postOrd( );
	 // Pre  : true
	 // Post : devuelve el recorrido en post-orden del arbol
	
	 TSecuenciaDinamica<TElem> inOrd( );
	 // Pre  : true
	 // Post : devuelve el recorrido en in-orden del arbol  
	
	
	int numNodos();
	 // Pre: True
	 // Post: Devuelve el numero de nodos del arbin
	 // O(n), con n el numero de nodos del arbin
		 
  // Operacion de escritura
	
     void escribe( );
     
     
  // EJERCICIOS HOJA 4
  
  	int numHojas();
  	//Pre: True
  	//Post: Devuelve el numero de hojas del arbol
  	//0(n), con n el numero de nodos del arbin 
  	
  	void espejo(); 
  	//Pre: True
  	//Post: calcula la imagen especular del arbin 
  	//0(n), con n el numero de nodos del arbin

	TSecuenciaDinamica<TElem> frontera();
	//Pre: True
	//Post: devuelve una secuencia de las hojas de izquierda a derecha
	//0(n), on n el numero de nodos del arbin
	
	TSecuenciaDinamica<TElem> ramaMasLarga();
	//Pre: True
	//Post: devueñve una secuencia con los nodos de la rama mas larga (en caso de empate el hijo izquierdo)
	//O(n), on n el numero de nodos del arbin
	
	int altura(TNodoArbin<TElem>* nodo);
	//Pre: True
	//Post: Devuelve la altura de un arbin
	//O(n), on n el numero de nodos del arbin (logn si fuese AVL, implicando el resto lo mismo)
	
	TSecuenciaDinamica<TElem> nivelN(int n);
	// Pre: True
	//Post: devuelve una secuencia de los nodos del nivel n (de izquierda a derecha)
	//O(n) el numero de nodos del arbin
	
	
	
	
  // Variables privadas
	//UN ARBOL ES UN PUNTERO A LA RAIZ (COMO ES V.PRIVADA GUION)
     TNodoArbin<TElem>* _ra;

	
  // Operaciones privadas

     void copia( TArbinDinamico<TElem>& );
	
     TNodoArbin<TElem>* copiaAux( TNodoArbin<TElem>* );
	
	
  // operacion privada de escritura
	
     void escribeAux( TNodoArbin<TElem>* p, string prefijo );
	
	
  // Constructora privada para los subarboles
	
     TArbinDinamico( TNodoArbin<TElem>* );

	// aux de espejo
	
	void espejoAux(TNodoArbin<TElem>* nodo);
	
	void fronteraAux(TNodoArbin<TElem>* nodo, TSecuenciaDinamica<TElem>& s);
	
	void ramaMasLargaAux(TNodoArbin<TElem>* nodo, TSecuenciaDinamica<TElem>& s);
	
	void nivelNAux(TNodoArbin<TElem>* nodo, TSecuenciaDinamica<TElem>& s, int n);
	
};



//---------------------------------------------------------------------------
//                              IMPLEMENTACION
//---------------------------------------------------------------------------



 // Clase de los nodos del arbol QUE TRABAJA PARA LA FLOTA

	//(LA CONSTRUCTORA)
    template <class TElem>
    TNodoArbin<TElem>::TNodoArbin( TElem elem, TNodoArbin<TElem>* iz, TNodoArbin<TElem>* dr ) :
      _elem(elem), _iz(iz), _dr(dr) {
    };

	//OBSERVADORA 
    template <class TElem>
    TElem& TNodoArbin<TElem>::elem( ) {
		
      return _elem; //DEVUELVO EL PUNTERO
		
    }


    template <class TElem>
    TNodoArbin<TElem>* TNodoArbin<TElem>::iz( ) {
		
      return _iz;
		
    }


    template <class TElem>
    TNodoArbin<TElem>* TNodoArbin<TElem>::dr( ) {
		
      return _dr;
		
    }



  // Constructoras de la clase de los nodos del arbol


     template <class TElem>
     TArbinDinamico<TElem>::TArbinDinamico( ) :
       _ra( 0 ) { //HAGO QUE LA RAIZ APUNTE A NILL 
     };

	//PLANTAR
     template <class TElem>
     TArbinDinamico<TElem>::TArbinDinamico( TArbinDinamico<TElem>& iz, TElem elem, TArbinDinamico<TElem>& dr ) : //PASO LA REFERENCIA PARA QUE SE MANTENGAN LOS CAMBIOS PERO HAGO UNA COPIA??
       _ra( new TNodoArbin<TElem>( elem, copiaAux(iz._ra), copiaAux(dr._ra) ) ) { // NEW ES PARA RESERVAR 
     };



  // Constructora privada para los subarboles


	 template <class TElem>
	 TArbinDinamico<TElem>::TArbinDinamico( TNodoArbin<TElem>* ra ) :
	   _ra( ra ) {
	 };



  // Operaciones de los arboles


     template <class TElem>
     TArbinDinamico<TElem> TArbinDinamico<TElem>::hijoIz ( ) // throw ( EAccesoIndebido ) 
	 {
		 
       if( esVacio() )
		   
         throw EAccesoIndebido3( "Error: no existe el hijo izquierdo de un arbol vacio" );
		 
       else
		   
         return TArbinDinamico<TElem>( copiaAux( _ra -> iz( ) ) );
		 
     };


     template <class TElem>
     TArbinDinamico<TElem> TArbinDinamico<TElem>::hijoDr( ) // throw ( EAccesoIndebido ) 
	 {
		 
       if( esVacio() )
		   
         throw EAccesoIndebido3( "Error: no existe el hijo derecho de un arbol vacio" );
		 
       else
		   
         return TArbinDinamico<TElem>( copiaAux( _ra -> dr( ) ) );
		 
     };


     template <class TElem>
     TElem TArbinDinamico<TElem>::raiz( ) // throw ( EAccesoIndebido ) 
	 {
		 
       if( esVacio() )
		   
         throw EAccesoIndebido3( "Error: no existe la raiz de un arbol vacio" );
		 
       else
		   
         return _ra -> elem( );
		 
     };


     template <class TElem>
     bool TArbinDinamico<TElem>::esVacio( ) {
		 
       return _ra == 0;
		 
     };



// Recorrido en pre-orden del arbol


   template <class TElem>
   void preOrdAcu( TNodoArbin<TElem>* p, TSecuenciaDinamica<TElem>& xs ) {
	   
      if ( p != 0 ) {
		  
		  xs.inserta( p -> elem( ) );
		  
		  preOrdAcu( p -> iz( ), xs );
		  preOrdAcu( p -> dr( ), xs );
		  
	  }
	   
   };


   template <class TElem>
   TSecuenciaDinamica<TElem> TArbinDinamico<TElem>::preOrd( ) {
	   
	   TSecuenciaDinamica<TElem> r;
	   
	   preOrdAcu( _ra, r );
	   
	   return r;
   
   };



// Recorrido en post-orden del arbol


   template <class TElem>
   void postOrdAcu( TNodoArbin<TElem>* p, TSecuenciaDinamica<TElem>& xs ) {
	   
	   if ( p != 0 ) {
		   
		   postOrdAcu( p -> iz( ), xs );
		   postOrdAcu( p -> dr( ), xs );
		   
		   xs.inserta( p -> elem( ) );
		   
	   }
	   
   };



   template <class TElem>
   TSecuenciaDinamica<TElem> TArbinDinamico<TElem>::postOrd( ) {
	   
	   TSecuenciaDinamica<TElem> r;
	   
	   postOrdAcu( _ra, r );
	   
	   return r;
	   
   };



// Recorrido en in-orden

   
   template <class TElem>
   void inOrdAcu( TNodoArbin<TElem>* p, TSecuenciaDinamica<TElem>& xs ) {
	   
	   if ( p != 0 ) {
		   
		   inOrdAcu( p -> iz( ), xs );
		   
		   xs.inserta( p -> elem( ) );
		   
		   inOrdAcu( p -> dr( ), xs );
	   
	   }
   
   };


   template <class TElem>
   TSecuenciaDinamica<TElem> TArbinDinamico<TElem>::inOrd( ) {
	   
	   TSecuenciaDinamica<TElem> r;
	   
	   inOrdAcu( _ra, r );
	   
	   return r;
   
   };
	  /*
    numNodos : arbin -> nat
    numNodos(arbol-vacio) = 0
    numNodos(plantar(iz,e,dr)) = 1 + numNodos(iz) + numNodos(dr)
   
    Tamaño de datos: n = numero de nodos
    T(n) = k1 si n = 0
    T(n) = T(p) + T(q) + k2 si n>0
    siendo p + q + 1 = n,  k1,k2 constantes reales positivas. Por el ejercicio 6.6 del libro:
    T(n) <- O(n)
    */
   
    template <class TElem>
    int TArbinDinamico<TElem>::numNodos(){
       	if (esVacio()) return 0;
	   	else return 1 + hijoIz().numNodos() + hijoDr().numNodos();
	}
	/* 
	
	EJERCICIOS HOJA 4
	
	
	
	numHojas: arbin -> nat 
	numHojas(arbol-vacio) = 0
	numHojas(plantar(arbol-vacio,e,arbol-vacio) = 1
	numHojas(plantar(iz,e,dr) = numHojas(iz) + numHojas(dr) <-- !esVacio(iz) v !esVacio(dr)
	
	*/


	template <class TElem> 
	int TArbinDinamico<TElem>:: numHojas(){
		if (esVacio()){ //O(n) 
			return 0;
			}
		else if ((hijoIz().esVacio()) && (hijoDr().esVacio())){
			return 1; //O(n)
		}
		else{
			return hijoIz().numHojas() + hijoDr().numHojas(); // recursion
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
	
	espejo: arbin -> arbin
	
	espejo(arbol-vacio) = arbol-vacio
	espejo(plantar(iz,e,dr) = plantar(espejo(dr), e, espejo(iz))
	
	*/
	
	template <class TElem>
	void TArbinDinamico<TElem>:: espejo(){
		espejoAux(_ra);
	}
	
	template <class TElem>
	void TArbinDinamico<TElem>:: espejoAux(TNodoArbin<TElem>* nodo){
		if (nodo != 0){ //no es nill
			TNodoArbin<TElem>* provisional; 
			provisional = nodo -> iz();
			nodo -> _iz = nodo -> dr();
			nodo -> _dr = provisional;
			espejoAux(nodo -> iz());
			espejoAux(nodo -> dr());
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
	
	frontera: arbin -> secuencia
	frontera(arbol-vacio) = secuencia-vacia
	frontera(plantar(arbol-vacio,e,arbol-vacio) = insertar(e,secuencia-vacia)
	frontera(plantar(iz,e,dr) = frontera(iz) ++ frontera(dr) <-- !esVacio(iz) v !esVacio(dr)
	
	*/
	
	
	template <class TElem>
	TSecuenciaDinamica<TElem> TArbinDinamico<TElem> :: frontera(){
		TSecuenciaDinamica<TElem> s;
		fronteraAux(_ra, s);
		return s;
	}
	
	template <class TElem>
	void TArbinDinamico<TElem> :: fronteraAux(TNodoArbin<TElem>* nodo, TSecuenciaDinamica<TElem>& s){
		if (nodo != 0){
			if ((nodo -> iz() == 0) && (nodo -> dr() == 0)) {
				s.inserta(nodo -> elem()); // O(1)
			}
			else{
				fronteraAux(nodo -> iz(), s);
				fronteraAux(nodo -> dr(), s);
			}
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
	version sin punteros--------------------------------------------------
	
	template<class TElem>
    TSecuenciaDinamica<TElem> TArbinDinamico<TElem>::frontera(){
   		TSecuenciaDinamica<TElem> r;
   		frontera_aux(r);
   		return r;
   	
    }
   template<class TElem>
   void TArbinDinamico<TElem>::frontera_aux(TSecuenciaDinamica<TElem> &r){
   		if (esVacio()) return;
   		else if (hijoIz().esVacio() && hijoDr().esVacio()) r.inserta(raiz());
   		else{
   			hijoIz().frontera_aux(r);
   			hijoDr().frontera_aux(r);
		   }
    }
   
	*/




	

	/* 
	
	ramaMasLarga: arbin -> secuencia
	ramaMasLarga(arbol-vacio) = secuencia-vacia
	ramaMasLarga(plantar(iz,e,dr) = insertar(e, ramaMasLarga(iz)) <--  (altura(iz) >= altura(dr))   
	ramaMasLarga(plantar(iz,e,dr) = insertar(e, ramaMasLarga(dr)) <--  (altura(iz) < altura(dr))   
	
	*/

	template <class TElem>
	TSecuenciaDinamica<TElem> TArbinDinamico<TElem>:: ramaMasLarga(){
		TSecuenciaDinamica<TElem> s;
		ramaMasLargaAux(_ra, s);
		return s;
	}
	

	template <class TElem>
	void TArbinDinamico<TElem>:: ramaMasLargaAux(TNodoArbin<TElem>* nodo, TSecuenciaDinamica<TElem>& s){
		if (nodo != 0){
			s.inserta(nodo->elem());
			if (altura(nodo->iz()) >= altura(nodo -> dr())){
				ramaMasLargaAux(nodo -> iz(), s);
			}
			else{
				ramaMasLargaAux(nodo -> dr(), s);
			}
		} 
	}
	
	/* 
	
	Tamaño de los datos n siendo n el número de nodos del arbin
			
			/ k0 si n=0
	T(n) = |
			\ T(p) + n*k1 si n>0   <--- viene de la altura (logn si fuese AVL) 
			
	con p numero nodos del HI o del HD (el mayor), k1, k2 ctes positivas 
	
	T(n) tendrá coste cuadratico O(n^2) 
	
	*/
	
	
	

	/*
	
	altura: arbin -> nat
	altura(arbol-vacio) = 0
	altura(plantar(iz,e,dr) = 1 + max(altura(iz),altura(dr))
	
	*/


	template <class TElem> 
	int TArbinDinamico<TElem>:: altura(TNodoArbin<TElem>* nodo){
		if (nodo == 0){
			return 0;
		}
		else{
			return 1 + max(altura(nodo -> iz()),altura(nodo -> dr()));
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
	
	nivelN: arbin  nat -> secuencia
	nivelN(arbol-vacio, n)= secuencia-vacia
	nivelN(arb, 0) = secuencia-vacia
	nivelN(plantar(iz,e,dr), n) = insertar(e,secuencia-vacia) <-- n == 1
	nivelN(plantar(iz,e,dr), n) = nivelN(iz, n-1) ++ nivelN(dr, n-1) <-- n >= 1
	
	*/

	
	template <class TElem>
	TSecuenciaDinamica<TElem> TArbinDinamico<TElem>:: nivelN(int n){
		TSecuenciaDinamica<TElem> s;
		nivelNAux(_ra, s, n);
		return s;
	}
	

	template <class TElem>
	void TArbinDinamico<TElem>::nivelNAux(TNodoArbin<TElem>* nodo, TSecuenciaDinamica<TElem>& s, int n){
		if ((nodo != 0) && (n >= 1)){
			if (n==1){
				s.inserta(nodo -> elem());
			}
			else{
				nivelNAux(nodo-> iz(), s, n-1);
				nivelNAux(nodo-> dr(), s, n-1);
			}
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













  // Operaciones de escritura de arboles


     template <class TElem>
     void TArbinDinamico<TElem>::escribeAux( TNodoArbin<TElem>* p, string prefijo ) {
		 
       if ( p != 0 ) {
		   
		   cout << ( prefijo + " : " ) << p -> elem( ) << endl;
		   
		   escribeAux( p -> iz( ), prefijo + ".1" );
		   escribeAux( p -> dr( ), prefijo + ".2" );
		   
       }
		 
     }


     template <class TElem>
     void TArbinDinamico<TElem>::escribe( ) {
		 
		 cout << endl;
		 
		 escribeAux( _ra, "1" );
		 
     };



  // Operaciones privadas


     template <class TElem>
     TNodoArbin<TElem>* TArbinDinamico<TElem>::copiaAux( TNodoArbin<TElem>* p ) {
		 
       TNodoArbin<TElem>* r;

       if ( p == 0 )
		   
         r = 0;
		 
       else
		   
         r = new TNodoArbin<TElem>( p -> elem( ), copiaAux( p -> iz( ) ), copiaAux( p -> dr( ) ) );
		 
       return r;
		 
     };


     template <class TElem>
     void TArbinDinamico<TElem>::copia( TArbinDinamico<TElem>& arb) {
		 
       _ra = copiaAux( arb._ra );
		 
     };



#endif