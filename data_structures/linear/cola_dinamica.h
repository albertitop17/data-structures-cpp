#ifndef cola_dinamicaH
#define cola_dinamicaH


/*
 
 
 especificación COLAS[ELEM]
 
 usa BOOLEANOS
 
 tipos cola
 
 operaciones
 
	cola-vacía     :                -->   cola     { constructora }
	pedir-vez      : cola elemento  -->   cola     { constructora }
	avanzar        : cola           -/->  cola
	primero        : cola           -/->  elemento
	es-cola-vacía? : cola           -->   bool
 
 variables
 
	e : elemento
	p : cola
 
 ecuaciones
 
	avanzar(cola-vacía)     = error
	avanzar(pedir-vez(c,e)) = cola-vacía               <==   es-cola-vacía?(c)
	avanzar(pedir-vez(c,e)) = pedir-vez(avanzar(c),e)  <==  ¬es-cola-vacía?(c)
 
	primero(cola-vacía)     = error
	primero(pedir-vez(c,e)) = e           <==   es-cola-vacía?(c)
	primero(pedir-vez(c,e)) = primero(c)  <==  ¬es-cola-vacía?(c)
 
	es-cola-vacía?(cola-vacía)     = cierto
	es-cola-vacía?(pedir-vez(c,e)) = falso
 
 fespecificación
 
 
*/


#include <iostream>
#include <string>

using namespace std;



// Tratamiento de excepciones


class EAccesoIndebido {
	
public:
	
    EAccesoIndebido( string mensaje = "" ) : _mensaje(mensaje) { };
	
    string mensaje ( ) {
		return _mensaje;
    };
	
private:
	
    string _mensaje;
	
};



template <class TElem>
class TColaDinamica;


template <class TElem>
class TNodoCola {
	
  public:
	
    TElem elem( );
    TNodoCola<TElem>* sig( );
	
    friend class TColaDinamica<TElem>;
	
  private:
	
    TElem _elem;
    TNodoCola<TElem>* _sig;
	
    TNodoCola( TElem, TNodoCola<TElem>* = 0 );
	
};



template <class TElem>
class TColaDinamica {
  public:

  // Constructora
	
     TColaDinamica( );
     // O(1)

  // Operaciones de las colas
	
     void ponDetras( TElem ); 
     // Pre: true
     // Post: Se añade 'elem' al final de la cola
     // O(1) sobre tipos predefinidos

     TElem primero( ); // throw (EAccesoIndebido);
     // Pre: ! esVacio( )
     // Post: Devuelve el primer elemento de la cola
     // Lanza la excepción "EAccesoIndebido" si la cola está vacía
     // O(1)

     void quitaPrim( ); // throw (EAccesoIndebido);
     // Pre: ! esVacio( )
     // Post: Elimina el primer elemento de la cima
     // Lanza la excepción "EAccesoIndebido" si la cola está vacía
     // O(1) sobre tipos predefinidos

     bool esVacio( );
     // Pre: true
     // Post: Devuelve true o false según si la pila está o no vacía
     // O(1)
	 
	 void dividecola(TColaDinamica<TElem> &colaAux1, TColaDinamica<TElem> &colaAux2); //param de salida & 
	 // Pre: true 
	 // Post: Dividie una cola en 2, la primera las posiciones pares y la segunda las impares
	 // O(n) siendo n el numero de elementos de la cola original
	 
	 TColaDinamica<TElem> copiarCola();
	 // Pre: true
	 // Post: copia una cola
	 // O(n) siendo n el numero de elementos de la cola original
	 
	void colapsar();
	 // Pre: true
	 // Post: suma los elementos de cada tramo comprendido entre ceros
	 // O(n) siendo n el numero de elementos de la cola original
	 
	 void inversa();
	 // Pre: true
	 // Post: inversa de una cola
	 // O(n) siendo n el numero de elementos de la cola original
	 
  // Escritura
	
     void escribe( );
     // O(n)


  private:
	
  // Variables privadas                
	
     TNodoCola<TElem> *_prim, *_ult;   
	 
	 int sumar();
	 //Pre: true (no la usaremos si es vacia)
	 //Post: devuelve la suma de los elementos de una cola
	 // O(n) siendo n el numero de elementos de la cola original          
     
};



//---------------------------------------------------------------------------
// IMPLEMENTACION
//---------------------------------------------------------------------------



  // Clase de los nodos


    template <class TElem>
    TNodoCola<TElem>::TNodoCola( TElem elem, TNodoCola<TElem>* sig ) :
      _elem(elem), _sig(sig) {
    };


    template <class TElem>
    TElem TNodoCola<TElem>::elem( ) {
		
      return _elem;
		
    }


    template <class TElem>
    TNodoCola<TElem>* TNodoCola<TElem>::sig( ) {
		
      return _sig;
		
    }





  // Constructora
  
  TColaDinamica<char> c ;
  
        									
     template <class TElem>
     TColaDinamica<TElem>::TColaDinamica( ) :
       _prim(0), _ult(0) {
     };

	
	

  // Operaciones de las colas
  
     template <class TElem>
     void TColaDinamica<TElem>::ponDetras( TElem elem ) {
		 
       TNodoCola<TElem>* p = new TNodoCola<TElem>(elem);
		 
       if( _ult != 0 )
	   
         _ult -> _sig = p;
      
       else
       
         _prim = p;
      
       _ult = p;
		 
     };


     template <class TElem>
     TElem TColaDinamica<TElem>::primero( ) // throw (EAccesoIndebido) 
	 {
		 
       if( esVacio() )
         throw EAccesoIndebido("Error: no existe el primero de la cola vacia");
       else
         return _prim -> elem();   
		 
     };

	
												                                         
     template <class TElem>
     void TColaDinamica<TElem>::quitaPrim( ) // throw (EAccesoIndebido) 
	 {
		 
       if( esVacio() )
         throw EAccesoIndebido("Error: no se puede quitar el primero de la cola vacia");
       else {
		   
         TNodoCola<TElem>* tmp = _prim;
         _prim = _prim -> sig();
		   
         if( _prim == 0 )
           _ult = 0;
		   
         delete tmp;
		   
       }
		 
     };
	


     template <class TElem>
     bool TColaDinamica<TElem>::esVacio( ) {
		 
       return _prim == 0;
		 
     };
     
     template <class TElem>
     TColaDinamica<TElem> TColaDinamica<TElem>::copiarCola() {
        TColaDinamica<TElem> aux; 
        TNodoCola<TElem>* actual = _prim; 
        while (actual != 0) {
            aux.ponDetras(actual->elem());
            actual = actual->sig();
        }

        return aux; 
    }
					
	/*
	YA VEREMOS LA ESPECIFICACION ALGEBRAICA
	*/

	 template <class TElem>
	 void TColaDinamica<TElem>::dividecola(TColaDinamica<TElem> &colaAux1, TColaDinamica<TElem> &colaAux2){
	 	
	 	while (!esVacio()){
	 		colaAux1.ponDetras(primero());
	 		quitaPrim();
	 		if (!esVacio()){
	 			colaAux2.ponDetras(primero());
	 			quitaPrim();
			 }
	 			
		 }
	 }
	 
	 template <class TElem>
	 int TColaDinamica<TElem>:: sumar(){
	 	int i=0;
	 	while (!esVacio()){
	 		i += primero();
	 		quitaPrim();
		 }
		 return i;
	}

	/*
	YA VEREMOS LA ESPECIFICACION ALGEBRAICA
	*/
	 template <class TElem>
	 void TColaDinamica<TElem>:: colapsar(){
	 	
	 	TColaDinamica<TElem> aux; 
	 	TColaDinamica<TElem> temp;
	 	while (!esVacio()){
	 		if (primero() == 0 && !(temp.esVacio())){
				aux.ponDetras(temp.sumar());
				aux.ponDetras(0);
				quitaPrim();
			}
			else{
				temp.ponDetras(primero());
				quitaPrim();	 		
			}
		 }
		 aux.ponDetras(temp.sumar());
		 *this = aux;
	 }
	
	/*
     inversa : cola --> cola
     inversa(cola-vacia) = cola-vacia
     inversa(c) = pedir-vez(inversa(avanzar(c)),primero(c))

     */
     template <class TElem>
     void TColaDinamica<TElem> :: inversa(){
         if (esVacio()) return;
         TElem e = primero();
         quitaPrim();
         inversa();
         ponDetras(e);

     }
  // Operaciones de entrada/salida
													                                           
     template <class TElem>
     void TColaDinamica<TElem>::escribe( ) {
		 
       TNodoCola<TElem>* tmp = _prim;
		 
	   cout << endl;
		 
       while ( tmp != 0 ) {
		   
         cout << tmp -> elem() << " ";
         tmp = tmp -> sig();
		   
       }
		 
	   cout << endl;
		 
     };
	
	


#endif
