#ifndef lista_dinamicaH
#define lista_dinamicaH


/*

 
 especificacion LISTAS[ELEM]
 
 usa
 
    BOOLEANOS, NATURALES
  
 tipo
 
    lista
 
 operaciones
 
    vacio      :             -->  lista        { constructora }
    ponDelante : elem lista  -->  lista        { constructora }
    ponDetras  : lista elem  -->  lista         
    primero    : lista       -/-> elem                        
    quitaPrim  : lista       -/-> lista              
    ultimo     : lista       -/-> elem                        
    quitaUlt   : elem        -/-> lista               
    concatena  : lista lista -->  lista  
    esVacio    : lista       -->  bool                          
    numElem    : lista       -->  nat                           
    elemEn     : lista nat   -/-> elem   
 
  variables
 
    x, y   : elem
    xs, ys : lista
    n      : nat
 
  ecuaciones
 
    concatena(vacio, ys)                     = ys
    concatena(ponDelante(x, xs), ys)         = ponDelante(x, concatena(xs, ys))
 
    ponDetras(xs, x)                         = concatena(xs, ponDelante(x, vacio))
 
    esVacio(vacio)                           = cierto
    esVacio(ponDelante(x, xs))               = falso
 
    primero(vacio)                           = error
    primero(ponDelante(x, xs))               = x
 
    quitaPrim(vacio)                         = error
    quitaPrim(ponDelante(x, xs))             = xs
 
    ultimo(vacio)                            = error
    ultimo(ponDelante(x, xs))                = x            <==  esVacio(xs)
    ultimo(ponDelante(x, xs))                = ultimo(xs)   <== ¬esVacio(xs)
 
    quitaUlt(vacio)                          = error
    quitaUlt(ponDelante(x, xs))              = vacio        <==  esVacio(xs)
    quitaUlt(ponDelante(x, xs))              = ponDelante(x, quitaUlt(xs))
                                                            <== ¬esVacio(xs)
 
    numElem(vacio)                           = cero
    numElem(ponDelante(x, xs))               = suc(numElem(xs))
 
    elemEn(xs, n)                            = error <== ( n == cero ) \/ 
                                                         ( n > (numElem xs) )
    elemEn(ponDelante(x, xs), suc(cero))     = x
    elemEn(ponDelante(x, ponDelante(y, ys)), suc(suc(n))
                                             = elemEn(ponDelante(y, ys), suc(n))
 
 fespecificacion


 La complejidad de las operaciones viene dada por el número "n" de elementos
 de la lista.


ponDetras(elem)
push_back(elem)	 
Añade al final
ponDelante(elem)
push_front(elem)	 
Añade al principio
numElem()
size()	 
Devuelve el tamaño (nota: devuelve size_t, un entero sin signo)
esVacio()	 
empty()
Devuelve true si está vacía
primero()
front()	 
Devuelve el primer elemento
quitaPrim()	 
pop_front()	
Borra el primer elemento
(((std::list)))
ultimo()
back()
Devuelve el último elemento (el valor)
quitaUlt()
pop_back()
Elimina el último elemento.
*/


#include <iostream>
#include <string>

using namespace std;



// Tratamiento de excepciones


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



// Clase de los nodos de la lista


template <class TElem>
class TListaDinamica;


template <class TElem>
class TNodoLista { //pequeña empresita q se dedica a la construccion de los vagones
	
  private:
	
    TElem _elem;
    TNodoLista<TElem> *_sig, *_ant;
	
    TNodoLista( TElem, TNodoLista<TElem>* = 0, TNodoLista<TElem>* = 0 );
	
  public:
	
    TElem elem( ); //lo mismo que _elem pero más elegante
    TNodoLista<TElem>* sig( );
    TNodoLista<TElem>* ant( );
	
    friend class TListaDinamica<TElem>;
	
};



// Clase de las listas genericas


template <class TElem>
class TListaDinamica {
	
  public:

  // Constructora
	
     TListaDinamica( );
     // O(1)


  // Operaciones de las listas
	
     void ponDetras( TElem );
     // Pre: true
     // Post: Se añade 'elem' al final de la lista
     // O(1) sobre tipos predefinidos

     void ponDelante( TElem );
     // Pre: true
     // Post: Se añade 'elem' al principio de la lista
     // OO(1) sobre tipos predefinidos

     TElem primero( ); // throw ( EAccesoIndebido );
     // Pre: ! esVacio( )
     // Post: Devuelve el primer elemento de la lista
     // Lanza la excepcion "EAccesoIndebido" si la lista esta vacia
     // O(1)

     TElem ultimo( ); // throw ( EAccesoIndebido );
     // Pre: ! esVacio( )
     // Post: Devuelve el último elemento de la lista
     // Lanza la excepcion "EAccesoIndebido" si la lista esta vacia
     // O(1)

     void quitaPrim( ); // throw ( EAccesoIndebido );
     // Pre: ! esVacio( )
     // Post: Elimina el primer elemento de la lista
     // Lanza la excepción "EAccesoIndebido" si la lista esta vacia
     // O(1) sobre tipos predefinidos

     void quitaUlt( ); // throw ( EAccesoIndebido );
     // Pre: ! esVacio( )
     // Post: Elimina el último elemento de la lista
     // Lanza la excepción "EAccesoIndebido" si la lista esta vacia
     // O(1) sobre tipos predefinidos

     bool esVacio( );
     // Pre: true
     // Post: Devuelve true o false según si la pila esta o no vacia
     // O(1)

     void concatena( TListaDinamica<TElem>& lista );
     // Pre: true
     // Post: concatena la lista pasada como parametro, dejándola vacia
     // O(1)

     int numElem( );
     // Pre: true
     // Post: Devuelve el numero de elementos de la lista
     // O(1)

     TElem elemEn( int n ); // throw ( EAccesoIndebido );
     // Pre: 1 <= n <= numElem( )
     // Post: Devuelve el elemento en la posicion n
     // O(n)
	
			
			
     // EJERCICIOS DESARROLLO HOJA 3 (LISTA)
	
	 void eliminar(TElem e);
	 //Pre: true
	 //Post: Elimina todas las apariciones de un elemento de una lista
	 //O(n), siendo n la longitud de la lista	 
	
	 bool palindroma();
	 //Pre: true
	 //Post: Dice si una lista es palindroma o no lo es
	 //O(n) siendo n la longitud de la lista
	 
	 void quicksort();
	 //Pre: true
	 //Post: Devuelve la lista ordenada mediante el algoritmo de ordenacion rapida (quicksort).
	 // O(n^2) siendo n la longitud de la lista (caso peor)

     void dupimp();
     //Pre:true 
     //Post: Devuelve una lista duplicando los elementos impares
     
     void add_to(int index, int m);
	 //Pre: true (la lista tiene que estar ordenada)
	 //Post: Suma m al elemento del indice concreto y reordena la lista
	 //O(...) 
	
	 TListaDinamica<TElem> copiarLista();
	 //Pre: true
	 //Post: copia lista
	 //O(numero elem lista) 
	
  // Escritura
	
     void escribe( );
     // O(n)
	
	void mergeSort();
	// Pre: true
	// Post: ordenacion por mergeSort
	//O(nlogn)
	/*
	void ordInserc();
	// Pre: true
	// Post: ordenacion por ordenacion por insercion 
	//O(n^2)
	*/
	
  private:
	
  // Variables privadas
	
	 int _longitud;
     TNodoLista<TElem> *_prim, *_ult;
     
};



//---------------------------------------------------------------------------
// IMPLEMENTACION
//---------------------------------------------------------------------------



  // Clase de los nodos

    template <class TElem>
    TNodoLista<TElem>::TNodoLista( TElem elem, TNodoLista<TElem>* sig, TNodoLista<TElem>* ant ) :
      _elem(elem), _sig(sig), _ant(ant) {
    };


    template <class TElem>
    TElem TNodoLista<TElem>::elem( ) {
		
      return _elem;
		
    }


    template <class TElem>
    TNodoLista<TElem>* TNodoLista<TElem>::sig( ) {
		
      return _sig;
		
    }


    template <class TElem>
    TNodoLista<TElem>* TNodoLista<TElem>::ant( ) {
		
      return _ant;
		
    }


  // Constructora

     template <class TElem>							// TListaDinamica<int> L;
     TListaDinamica<TElem>::TListaDinamica( ) :		// ||<--[*|0|*]-->||
       _prim(0), _ult(0), _longitud(0) {
     };


  // Operaciones de las listas

     template <class TElem>
     void TListaDinamica<TElem>::ponDetras( TElem elem ) {
		 
       TNodoLista<TElem>* p = new TNodoLista<TElem>(elem);
		 
       if( esVacio( ) )
		   
         _prim = _ult = p;
		 
       else {
		   
         _ult -> _sig = p;
         p -> _ant = _ult;
         _ult = p;
		   
       }
		 
       _longitud++;
		 
     };


     template <class TElem>
     void TListaDinamica<TElem>::ponDelante( TElem elem ) {
		 
       TNodoLista<TElem>* p = new TNodoLista<TElem>(elem);
		 
       if( esVacio( ) )
		   
         _prim = _ult = p;
		 
       else {
		   
         _prim -> _ant = p;
         p -> _sig = _prim;
         _prim = p;
		   
       }
		 
       _longitud++;
		 
     };


     template <class TElem>
     TElem TListaDinamica<TElem>::primero( ) // throw ( EAccesoIndebido ) 
	 {
		 
       if( esVacio( ) )
		   
         throw EAccesoIndebido( "Error: no existe el primero de la lista vacia" );
       
	   else
		   
         return _prim -> elem( );
		 
     };


     template <class TElem>
     TElem TListaDinamica<TElem>::ultimo( ) // throw ( EAccesoIndebido ) 
	 {
		 
       if( esVacio() )
		   
         throw EAccesoIndebido( "Error: no existe el ultimo de la lista vacia" );
       
	   else
		   
         return _ult -> elem( );
		 
     };


     template <class TElem>
     void TListaDinamica<TElem>::quitaPrim( ) // throw ( EAccesoIndebido ) 
	 {
		 
       if( esVacio( ) )
		   
         throw EAccesoIndebido( "Error: no se puede quitar el primero de la lista vacia" );
       
	   else {
		   
         TNodoLista<TElem>* tmp = _prim;
		   
         _prim = _prim -> sig( );
		   
         if( _prim == 0 )
			 
           _ult = 0;
         
		 else
			 
           _prim -> _ant = 0;
         
		 delete tmp;
		   
         _longitud--;
		   
       }
		 
     };


     template <class TElem>
     void TListaDinamica<TElem>::quitaUlt( ) // throw ( EAccesoIndebido ) 
	 {
		 
       if( esVacio( ) )
		   
         throw EAccesoIndebido( "Error: no se puede quitar el ultimo de la lista vacia" );
       
	   else {
		   
         TNodoLista<TElem>* tmp = _ult;
		   
         _ult = _ult ->ant( );
		   
         if ( _ult == 0 )
			 
           _prim = 0;
		   
         else
			 
           _ult -> _sig = 0;
		   
         delete tmp;
		   
         _longitud--;
		   
       }
		 
     };


     template <class TElem>
     bool TListaDinamica<TElem>::esVacio( ) {
		 
       return _prim == 0;
		 
     };


     template <class TElem>
     void TListaDinamica<TElem>::concatena( TListaDinamica<TElem>& lista ) {

       if ( ! lista.esVacio( ) ) {
		   
         if ( esVacio( ) ) {
			 
           _prim = lista._prim;
           _ult = lista._ult;
           _longitud = lista._longitud;
			 
         }
         else {
			 
           _ult -> _sig = lista._prim;
           lista._prim -> _ant = _ult;
           _ult = lista._ult;
           _longitud += lista._longitud;
			 
         }
		   
         lista._prim = 0;
         lista._ult = 0;
         lista._longitud = 0;
		   
       }

     }


     template <class TElem>
     int TListaDinamica<TElem>::numElem( ) {

       return _longitud;

     }



     template <class TElem>
     TElem TListaDinamica<TElem>::elemEn( int n ) // throw ( EAccesoIndebido ) 
	 {

       if ( ( n < 1 ) || ( n > numElem( ) ) )
		   
         throw EAccesoIndebido( "Error: posicion inexistente" );

       TNodoLista<TElem>* p = _prim;
		 
       for ( int i = 1; i < n; i++ )
		   
         p = p -> sig( );
		 
       return p -> elem( );
		 
     }
	
	 
	 /*
	 
	 eliminar: lista elemento -> lista
	 vars l: lista, e,f: elemento
	 ecuaciones:
	 	eliminar([], e) = []
	 	eliminar(f:l,e) = f:eliminar(l,e) <= f /= e
	 	eliminar(f:l,e) = eliminar(l,e) <= f == e
	 	
		Tamaño de datos
		n = longitud de la lista
		 
		Al ser un algoritmo recursivo planteo una recurrencia
	 		 
	 		    | k1 si n = 0
	 	T(n) = |
	 			| T(n-1) + k2 si n > 0 (k2 pues las funciones usadas tienen coste costante)
	 			
	 	por el teorema de la resta tenemos que (a = 1, b = 1, k = 0) luego el orden es 
	 	T(n) <- O(n^1) = O(n)
	 */		  
	  
	 template <class TElem>
	 void TListaDinamica<TElem>:: eliminar(TElem e){
	 
	 	if (!esVacio()){
	 		if (primero() == e){
	 			quitaPrim();
	 			eliminar(e);
			 }
	 		else{
	 			TElem primer = primero();
	 			quitaPrim();
	 			eliminar(e);
	 			ponDelante(primer); 
			 }
		 }
	 		
	 }
	 /*
	 palindroma: lista --> bool
	 palindroma([]) = cierto
	 palindroma(e:[]) = cierto
	 palindroma(e:l) = (e == ultimo(l)) and palindroma(quitarUltim(l)) <= ¬ esVacio(L)
	 
	 
	Para calcular el coste llevemos a cabo la ecuacion de recurrencia
	 
	Sea n = longitud de la lista el tamaño de datos
	 
	T(n) = k1              n == 0 y n == 1
	T(n) = T(n-2) + k1     n>1
	 
	Aplicando el teorema de la resta ( a = 1 , b=2 , k= 0) 
	 
	T(n) <- O(n)
	 
	*/
	
	template <class TElem>
	bool TListaDinamica<TElem>:: palindroma(){
		TNodoLista<TElem>*  p = _prim;
		TNodoLista<TElem>*  q = _ult;
		bool palind = true;
		int m = _longitud;
		int i = 0;
		while ((i< m) && palind){
			if (p -> elem() == q -> elem()){
				p = p -> sig();
				q = q -> ant();
				i += 2;
			}
			else
				palind = false;
		}
		
		return palind;
	}
		
	template <class TElem>
     void TListaDinamica<TElem> :: add_to(int index, int m){
     	TElem e = elemEn(index);
     	e = e+m ;
     	ponDetras(e);
     	quicksort();
     	
	 }
	/*
	quicksort : lista --> lista
	quicksort([]) = []
	quicksort(x:xs) = quicksort(elem-menor-ig(x,xs)) ++ [x] ++ quicksort(elem-mayor(x,xs))
	
	elem-menor-ig : elem lista --> lista
	elem-menor-ig(e,[]) = []
	elem-menor-ig(e,x:xs) = x: elem-menor-ig(e,xs)  <= x <=e
	elem-menor-ig(e,x:xs) = x: elem-menor-ig(e,xs) <= x>e
	
	elem-mayor : elem lista --> lista
	elem-mayor(e,[]) = []
	elem-mayor(e,x:xs) = x:elem-mayor(e,xs) <=  x>= e
	elem-mayor(e,x:xs) = elem-mayor(e,xs) <= x<e
	 
	*/	

	template <class TElem>
	void TListaDinamica<TElem> :: quicksort(){
		if(esVacio() || numElem() == 1) return;
		
		TElem pivote = primero();
		TListaDinamica<TElem> menores;
		TListaDinamica<TElem> iguales;
		TListaDinamica<TElem> mayores;
		
		iguales.ponDetras(pivote);
		quitaPrim();
		
		while(!esVacio()){
			if(primero()<pivote) menores.ponDelante(primero());
			else if (primero()>pivote) mayores.ponDelante(primero());
			else iguales.ponDelante(primero());
			quitaPrim();		
		}
		menores.quicksort();
		mayores.quicksort();
		menores.concatena(iguales);
		menores.concatena(mayores);
		*this = menores;
		
	}
	
			
	/*
	version video
	 
	template <class TElem>
	TListaDinamica<TElem> TListaDinamica<TElem>::quicksort() {
    
    TListaDinamica<TElem> resultado;

    if (!esVacio()) {
        
        TElem pivote = primero();
        
        quitaPrim();
        
        TListaDinamica<TElem> menores;
        TListaDinamica<TElem> mayores;
        
        elemMenorIgMayor(pivote, menores, mayores);
        
        menores = menores.quicksort();
        mayores = mayores.quicksort();
        
        resultado.concatena(menores);
        resultado.ponDetras(pivote);
        resultado.concatena(mayores);
    	}
    return resultado;
	}
	 
	*/
	
	/*
	dupimp : lista -> lista
	dupimp([]) =[]
	dupimp(x:xs) = x: dupimp(xs)  <= par(x) 
	dupimp(x:xs) = x:(x:dupimp(xs)) <= ¬par(x)
	
	De esta forma la recurrencia quedaria:
	
	T(n) = k1 si n == 0 
	T(n) = T(n-1) + k2 si n > 1
	Tomando a = 1, b = 1, k = 0 y aplicando el teorema de la resta tenemos que (como a =1)
	
	T(n) <- O(n^(k+1)) = O(n)

	Tomando como tamaño de datos n = longitud de la lista tenemos que 
	Coste en tiempo : O(n) ya que recorremos toda la lista en el caso peor.
	Coste en espacio : O(n) ya que llamamos a una lista auxiliar
	*/	
	
	template <class TElem>
	void TListaDinamica<TElem> :: dupimp(){
		TListaDinamica<TElem> aux;
		while(!esVacio()){
			if( primero() % 2 != 0) {
				aux.ponDetras(primero());
				aux.ponDetras(primero());
			}
			else {
				aux.ponDetras(primero());
			}
			quitaPrim();
		
		}
		*this = aux;

	}
		
	
	template <class TElem>
	TListaDinamica<TElem> TListaDinamica<TElem>::copiarLista() {
	    TListaDinamica<TElem> aux; 
	   
	    TNodoLista<TElem>* actual = _prim; 
	    while (actual != 0) {
	        aux.ponDetras(actual->elem());
	        actual = actual->sig();
	    }
	    return aux; 
	}
	
	/*
	ordenar-mezcla([]) = []
	ordenar-mezcla(e:[]) = e:[]

	ordenar-mezcla(x) = 
    mezclar-ord(ordenar-mezcla(coger(longitud(x) div 2, x)),ordenar-mezcla(tirar(longitud(x) div 2, x)))<= longitud(x) >= 2

	mezclar-ord(x,[]) = x
	mezclar-ord([],y) = y
	mezclar-ord(e:x, f:y) = e : mezclar-ord(x, f:y) <= e <= f
	mezclar-ord(e:x, f:y) = f : mezclar-ord(e:x, y) <= e > f
	 
	 Coste:
    T(n) = k1  si n <= 1
    T(n) = 2*T(n/2) + O(n) si n > 1

    O(n log n)
	*/
	template <class TElem>
	void TListaDinamica<TElem>:: mergeSort(){
		
		if (_longitud <= 1) return;
		TListaDinamica<TElem> listaIz;
		TListaDinamica<TElem> listaDr;
		int mid = _longitud/2;
		
        for (int i = 0; i < mid; i++) {
            listaIz.ponDetras(primero());
            quitaPrim();
        }

        while (!esVacio()) {
            listaDr.ponDetras(primero());
            quitaPrim();
        }
        listaIz.mergesort();
        listaDr.mergesort();
        while (!listaIz.esVacio() && !listaDr.esVacio()) {
            if (listaIz.primero() <= listaDr.primero()) {
                ponDetras(listaIz.primero());
                listaIz.quitaPrim();
            } else {
                ponDetras(listaDr.primero());
                listaDr.quitaPrim();
            }
        }
        concatena(listaIz);
        concatena(listaDr);
	}
	
	/*
	ordenar-inserción([]) = []
	ordenar-inserción(e:x) = insertar-ord(e, ordenar-inserción(x))

	insertar-ord(e, []) = [e]
	insertar-ord(e, f:x) = e : (f:x) <= e <= f
	insertar-ord(e, f:x) = f : insertar-ord(e, x) <= e > f
	
	
	template <class TElem>
	void TListaDinamica<TElem>::ordenarInsercion() {
		// por hacer
	}
	
	*/
  // Operaciones de entrada/salida

     template <class TElem>
     void TListaDinamica<TElem>::escribe( ) {
		 
       TNodoLista<TElem>* tmp = _prim;
		 
		 cout << endl;
		 
       while ( tmp != 0 ) {
		   
         cout << tmp -> elem( ) << " ";
         tmp = tmp -> sig( );
		   
       }
		 
	   cout << endl;
		 
     };
     
	


#endif