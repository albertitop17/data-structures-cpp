#ifndef cprioH
#define cprioH

#include <iostream>
#include <string>
#include <cmath>

using namespace std;



// Tratamiento de excepciones



/*
 
 especificación COLAS-CON-PRIORIDAD[ELEM<=]
 
 usa BOOLEANOS
 
 tipos colapr
 
 operaciones
 
    cp-vacía      :                       -->   colapr      { constructora }
    añadir        : colapr elemento       -->   colapr      { constructora }
    mínimo        : colapr                -/->  elemento
    eliminar-mín  : colapr                -/->  colapr
    es-cp-vacía?  : colapr                -->   bool
 
 variables
 
    e, f : elemento
    cp   : colapr
    
 ecuaciones
 
    añadir(añadir(cp, e), f)               = añadir(añadir(cp, f), e)
 
    mínimo(cp-vacía)                       = error
    mínimo(añadir(cp-vacía, e))            = e
    mínimo(añadir(añadir(cp, e), f))       = mínimo(añadir(cp, e)) <== mínimo(añadir(cp, e)) <= f
    mínimo(añadir(añadir(cp, e), f))       = f   <== mínimo(añadir(cp, e)) > f
 
    eliminar-mín(cp-vacía)                 = error
    eliminar-mín(añadir(cp-vacía, e))      = cp-vacía
    eliminar-mín(añadir(añadir(cp, e), f)) = añadir(eliminar-mín(añadir(cp, e)), f) <== mínimo(añadir(cp, e)) <= f
    eliminar-mín(añadir(añadir(cp, e), f)) = añadir(cp, e) <== mínimo(añadir(cp, e)) > f
 
    es-cp-vacía?(cp-vacía)                 = cierto
    es-cp-vacía?(añadir(cp, e))            = falso
 
 fespecificación
 
*/
/*
 
 especificación ÁRBOLES-(SEMI)COMPLETOS[ELEM]
 
 usa ÁRBOLES-BINARIOS[ELEM], BOOLEANOS
 
 operaciones
 
    es-completo?     : árbol-bin          -->   bool
    es-semicompleto? : árbol-bin          -->   bool
 
 variables
 
    e      : elemento
    iz, dr : árbol-bin
    
 ecuaciones
 
    es-completo?(árbol-vacío)             = cierto
    es-completo?(plantar(iz, e, dr))      = es-completo?(iz) /\ es-completo?(dr) /\ (altura(iz) == altura(dr))
 
    es-semicompleto?(árbol-vacío)         = cierto
    es-semicompleto?(plantar(iz, e, dr))  = es-completo?(plantar(iz, e, dr)) \/ (altura(iz) == altura(dr) /\ es-completo?(iz) /\ es-semicompleto?(dr)) \/
												(altura(iz) == altura(dr) + 1 /\ es-semicompleto?(iz) /\ es-completo?(dr))
 
 fespecificación
 
*/
/*
 
 especificación ES-MONTÍCULO[ELEM<=]
 
 usa ÁRBOLES-(SEMI)COMPLETOS[ELEM<=], BOOLEANOS
 
 operaciones
 
    es-montículo? : árbol-bin             -->   bool
 
 operaciones privadas
 
    menor-igual?  : elemento árbol-bin    -->   bool
 
 variables
 
    e, f   : elemento
    iz, dr : árbol-bin
    
 ecuaciones
 
    es-montículo?(árbol-vacío)            = cierto
    es-montículo?(plantar(iz, e, dr))     =  es-semicompleto?(plantar(iz, e, dr)) /\ menor-igual?(e, iz) /\ menor-igual?(e, dr) /\ es-montículo?(iz) /\ es-montículo?(dr)
 
    menor-igual?(e, árbol-vacío)          = cierto
    menor-igual?(e, plantar(iz, f, dr))   =  e <= f /\ menor-igual?(e, iz) /\ menor-igual?(e, dr)
 
 fespecificación
 
*/



class EDesbordamiento {
	
  public:
  	
    EDesbordamiento( string mensaje = "" ) : _mensaje(mensaje) { };
    
    string mensaje ( ) {
      return _mensaje;
    };
    
  private:
  	
    string _mensaje;
    
};


class EAccesoIndebido {
	
  public:
  	
    EAccesoIndebido( string mensaje = "" ) : _mensaje(mensaje) { };
    
    string mensaje ( ) {
      return _mensaje;
    };
    
  private:
  	
    string _mensaje;
    
};


class EClaveErronea {
	
  public:
  	
    EClaveErronea( string mensaje = "" ) : _mensaje(mensaje) { };
    
    string mensaje ( ) {
      return _mensaje;
    };
    
  private:
  	
    string _mensaje;
    
};



// CLASE PRINCIPAL DE LAS COLAS DE PRIORIDAD DE MINIMOS

//TElem debe tener orden!!

template <class TElem>
class TCPrio
{
	
  	public:

  	// Tamano inicial por defecto
  	
       static const int MAX = 64 - 1; // ( potencia de 2 ) - 1

    // Constructoras, destructora y operador de asignacion
    
       TCPrio( int capacidad ); //si no decimos nada usa el de MAX = 64 -1 
       
       TCPrio( TCPrio<TElem>& );
       
       ~TCPrio( ); //deconstructora/destructora
       
       TCPrio<TElem>& operator=( TCPrio<TElem>& ); // c = d 

    // Operaciones de las colas
    
       void anyade( TElem );
       // Pre  : true
       // Post : Se anade un elemento a la cola
       //O(logn), siendo n el num de elementos (AVL)

       TElem min( ); // throw (EAccesoIndebido);
       // Pre  : ! esVacio( )
       // Post : Devuelve el minimo elemento de la cola
       // Lanza la excepcion EAccesoIndebido si la cola esta vacia
	   //O(!)
	
       void quitaMin( ); // throw (EAccesoIndebido);
       // Pre  : ! esVacio( )
       // Post : Elimina el minimo elemento de la cola
       // Lanza la excepcion EAccesoIndebido si la cola esta vacia
	   //O(logn), siendo n el num de elementos (AVL)

       bool esVacio( );
       // Pre  : true
       // Post : Devuelve true o false segun si la cola esta o no vacia
	   //O(1)	 
	   
	   int altura();
	   //Pre: true
	   //Post: altura de un monticulo
	   //O(1)
		
	   bool buscar( TElem);
	   //Pre: true
	   //Post: dice si un elemento esta o no en un monticulo 
	   //O(n)
	
	   void eliminar(TElem );
	   //Pre: el elemento tiene que estar en el monticulo
	   //Post: dice si un elemento esta o no en un monticulo 
	   //O(n)
		
		void eliminar_todos(TElem );
	   //Pre: el elemento tiene que estar en el monticulo
	   //Post: dice si un elemento esta o no en un monticulo 
	   //O(n)
	   
	   void podar(TElem e);
	   //Pre: true
	   //Post: criba los elementos menores a un valor dado
	   //O(nlogn)
	   
  	// Escritura
  	
       void escribe( ostream& salida );

  	private:
  	
	// Variables privadas
	
       int _capacidad;
       int _ult;
       TElem *_espacio;
       
       //_espacio *---> ??		     _ult
       //							   |	
       //							  \|/ 
       //_espacio *----> [1][2][3][2][4][][][][][] (_capacidad = 10)

  	// Operaciones privadas
  	
       void libera( );
       void copia( TCPrio<TElem>& pila );
       bool buscar_aux(TElem , int );
       
};



// IMPLEMENTACION DE LAS COLAS DE PRIORIDAD DE MINIMOS MEDIANTE MONTICULOS


  // Operaciones auxiliares de los monticulos


     template <class TElem>
     void flota( TElem v[], int i ) {
     	
       TElem x;
       int actual, padre;
       bool flotando;

       x        = v[i];
       actual   = i;
       flotando = true;
       
       while ( ( actual > 0 ) && flotando ) {
       	
         padre = ( actual - 1 ) / 2;
         
         if ( x < v[padre] ) { // x > v[padre]
         	
           v[actual] = v[padre];
           actual    = padre;
           
         } else flotando = false;
         
       }
       
       v[actual] = x;
       
     };


     template <class TElem>
     int hijoElegido( TElem v[], int i, int j ) {
     	
       int r;

       if ( 2*i + 1 == j ) r = 2*i + 1;                   // i solo tiene hijo izquierdo
       else if ( v[2*i + 1] < v[2*i + 2] ) r = 2*i + 1;   // i tiene dos hijos   // ( v[2*i + 1] > v[2*i + 2] ) r = 2*i + 1; 
       		else r = 2*i + 2;
       return r;
       
     };


     template <class TElem>
     void hunde( TElem v[], int i, int j ) {
     	
       TElem x;
       int actual, hijo;
       bool hundiendo;

       x         = v[i];
       actual    = i;
       hundiendo = true;
       
       while ( ( 2*actual + 1 <= j ) && hundiendo ) {
       	
         hijo = hijoElegido(v, actual, j);
         
         if ( x > v[hijo] ) { //( x < v[hijo] )
         	
           v[actual] = v[hijo];
           actual    = hijo;
           
         } else hundiendo = false;
         
       }
       
       v[actual] = x;
       
     };




  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
  // Constructoras, destructora y operador de asignacion


     template <class TElem>
     TCPrio<TElem>::TCPrio( int capacidad ) :
     	
       _capacidad(capacidad), _ult(-1), _espacio(new TElem[_capacidad]) {
     
	 };


     template <class TElem>
     TCPrio<TElem>::TCPrio( TCPrio<TElem>& cola ) {
     	
        copia(cola);
        
     };


     template <class TElem>
     TCPrio<TElem>::~TCPrio( ) {
     	
       libera();
       
     };


     template <class TElem>
     TCPrio<TElem>& TCPrio<TElem>::operator=( TCPrio<TElem>& cola ) {
     	
       if( this != &cola ) {
       	
         libera();
         copia(cola);
         
       }
       
       return *this;
       
     };


  // Operaciones de las colas


     template <class TElem>
     void TCPrio<TElem>::anyade( TElem elem ) {
     	
       if ( _ult == _capacidad - 1 ) { //la capacidad es el numero de elementos, pero las posiciones empiezan en 0 (en este caso nos mudamos a una nueva casa)
       	
         _capacidad  *= 2; //nos compramos nueva casa
         TElem* nuevo = new TElem[_capacidad]; //la nueva casa tendra los m2 comprados      
         for( int i = 0; i <= _ult; i++ ) nuevo[i] = _espacio[i]; //llevamos todas nuestras maletas
         delete [] _espacio; //vendemos la casa antigua
         _espacio = nuevo; //cambio mi direccion a la nueva casa
         
       }
       
       _ult++;
       _espacio[_ult] = elem;
       
       flota(_espacio, _ult); //le doy el array y desde donde empiezo a flotar 
       //flota tiene coste logaritmico
       
     };
     

     template <class TElem>
     TElem TCPrio<TElem>::min( ) // throw (EAccesoIndebido) 
	 {
	 	
       if ( esVacio( ) ) throw EAccesoIndebido();
       else return _espacio[0];
       
     };


     template <class TElem>
     void TCPrio<TElem>::quitaMin( ) // throw (EAccesoIndebido) 
	 {
	 	
       if ( esVacio( ) ) throw EAccesoIndebido( );
       else {
       	
         _ult--;
         
         if ( _ult > -1 ) { //no esta vacio
         	
           _espacio[0] = _espacio[_ult+1];
           
           hunde(_espacio, 0, _ult); //desde la posicion hasta donde puedo llegar
           //hunde es logaritmico
         }
         
       }
       
     };


     template <class TElem>
     bool TCPrio<TElem>::esVacio( ) {
     	
       return _ult == -1;
       
     };


  // Operaciones de entrada/salida


     template <class TElem>
     void TCPrio<TElem>::escribe( ostream& salida ) {
     	
       for( int i = 0; i <= _ult; i++ ) salida << _espacio[i] << " ";
       
     };


     template <class TElem>
     ostream& operator<<( ostream& salida, TCPrio<TElem>& cola ) {
     	
       cola.escribe(salida);
       
       return salida;
       
     }


     template <class TElem>
     ostream& operator<<( ostream& salida, TCPrio<TElem>* cola ) {
     	
       cola -> escribe(salida);
       
       return salida;
       
     }


  // Operaciones privadas


     template <class TElem>
     void TCPrio<TElem>::libera( ) {
     	
       delete [] _espacio;
       
     };


     template <class TElem>
     void TCPrio<TElem>::copia( TCPrio<TElem>& cola ) {
     	
       _capacidad = cola._capacidad;
       _ult       = cola._ult;
       _espacio   = new TElem[ _capacidad ];
       
       for( int i = 0; i <= _ult; ++i ) _espacio[i] = cola._espacio[i];
         
     };
     
     
     // Ordenacion mediante monticulos


     template <class TElem>
     void hazMont( TElem v[], int n ) {
     	
       if ( n > 1 )
       
         for ( int i = (n - 2) / 2; i >= 0; i-- ) hunde(v, i, n);
           				//N div 2
     }


     template <class TElem>
     void heapsort( TElem v[], int n ) {
     	
       hazMont(v, n); //monticularizar2 o(n) 
       
       if ( n > 1 )
       
         for ( int i = n - 1; i > 0; i-- ) { // j =N  hasta 1 paso -1
         	
           TElem aux = v[i]; //cambio el elemento
           v[i]      = v[0];
           v[0]      = aux;
           
           hunde(v, 0, i - 1); //sigo hundiendo pero ahora hasta el ultimo elemento menos 1
           
         }
         
     };

	
	
	
	
	template<class TElem> 
	int TCPrio<TElem>::altura( ){
		if (esVacio()) return 0;
		if (_ult == 0) return 1;
		else return floor(log2(_ult))+1;
	}
	
	/*
	buscar: colapr elem -> bool
	buscar(cp-vacio,e) = false 
	buscar(anyadir(cp,e),e) = true
	buscar(anyadir(cp,e),f) = buscar(cp) <= e /= f 
	*/
	template<class TElem>  //O(n) en tiempo y O(1) en memoria auxiliar
	bool TCPrio<TElem>::buscar(TElem e){
		int i = 0;
		return buscar_aux(e, i );
	}
	template<class TElem> 
	bool TCPrio<TElem>::buscar_aux(TElem e, int i){
		if (i < _ult+1){
			if (_espacio[i] == e) return true;
			else if (_espacio[i] > e) return false;
			else{
				return (buscar_aux(e,2*i+1) || buscar_aux(e, 2*i+2));
			}
		}
		else return false;
	}
	
		/*
		template<class TElem>  // O(nlogn) en tiempo y O(n) en memoria auxiliar
		bool TCPrio<TElem>::buscar(TElem x){
			TCPrio<TElem> copiota(*this);
			bool encontrado = false;
			while(!copiota.esVacio() && !encontrado){
				if (x == copiota.min()) encontrado = true;
				copiota.quitaMin();
			}
			return encontrado;
		}
		*/


	
	
	/*
	 O(n + logn) = O(n) siendo n el numero de nodos
	 
	 eliminar: colapr elem -/-> colapr
	 eliminar(cp-vacia, e) = error
	 eliminar(cp,e) = error <= !buscar(cp,e) 
	 eliminar(anadir(cp, e),e) =  cp
	 eliminar(anadir(cp, e),f) =  anadir(eliminar(cp,f),e)
	*/
	
	
	template <class TElem>
	void TCPrio<TElem>:: eliminar(TElem e) {
		if (esVacio()) return;
		
		//Busco el índice 
	    int i = 0;
	    bool encontrado = false;
	    while (i <= _ult && !encontrado) {
	        if (_espacio[i] == e) encontrado = true;
	        else i++;
	    }
		
		if (!encontrado) throw EClaveErronea("No existe esta clave");
		
		// último???
		if (i == _ult) {
		    _ult--;
		    return;
		}
		// Intercambiar con el último
		TElem movido = _espacio[_ult];
		_espacio[i] = movido;
		_ult--;
		// flotar o hundir???
		int padre = (i - 1) / 2;
		if (i > 0 && _espacio[i] < _espacio[padre]) {
		    flota(_espacio, i);
		} else {
		    hunde(_espacio, i, _ult);
		}
	}
	
	template <class TElem>
	void TCPrio<TElem>:: eliminar_todos(TElem e) {
		if (esVacio() || e < _espacio[0]) return;
        int n = 0; 
        for (int i = 0; i <= _ult; i++) { //O(n)
            // Si no es el elemento, lo guardamos en la posición 'n'
            if (_espacio[i] != e) {
            	if (n != i) { 
                	_espacio[n] = _espacio[i];
				}
                n++;
            }
            // Si es el elemento, no incrementamos n, 
        }
        // Si n == _ult + 1 => no hemos borrado nada, terminamos.
        if (n == _ult + 1) return;
        // Actualizamos el último elemento válido
        _ult = n - 1;
        // monticulizamos O(N)
        for (int i = (_ult - 1) / 2; i >= 0; i--) {
            hunde(_espacio, i, _ult);
        }
    }
	
	/*	 
 	podar: colapr elem -> colapr
	podar(colapr-vacia,f) = colapr-vacio
	podar(cp,f) = podar(quitar-min(cp),f) <--- f >= min(cp)
	podar(cp,f) = arb <--- f < min(cp)
		 
	*/
	
	template <class TElem>
	void  TCPrio<TElem>:: podar(TElem e){
		while (!esVacio() &&  (min() <= e)){
			quitaMin();
		}
	}
	
	//si fuese podar mayores
	//monticulo aux, q vayamos introduciendo los menores al quitarlo O(n) en espacio y O(nlogn) 
	//monticulos maximos 
	

#endif