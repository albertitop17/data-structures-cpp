#ifndef TIENDA_H
#define TIENDA_H

#include <iostream>
#include <string>
#include "lista_dinamica.h"
#include "tabla_ordenada.h"

using namespace std;

// Excepciones específicas del sistema de Tienda
class EProductoNoExiste {
  public:
    EProductoNoExiste(string mensaje = "El producto no esta en el catalogo") : _mensaje(mensaje) {};
    string mensaje() { return _mensaje; };
  private:
    string _mensaje;
};

class EStockInsuficiente {
  public:
    EStockInsuficiente(string mensaje = "No quedan existencias del producto") : _mensaje(mensaje) {};
    string mensaje() { return _mensaje; };
  private:
    string _mensaje;
};

// Estructura auxiliar para devolver pares en el inventario
template <class TProd>
struct ParProductoCantidad {
    TProd producto;
    int cantidad;

    // Sobrecarga necesaria para ser elemento de una Lista Dinámica
    bool operator==(const ParProductoCantidad<TProd>& otro) {
        return producto == otro.producto;
    }
};

//---------------------------------------------------------------------------
// CLASE TIENDA
//---------------------------------------------------------------------------

template <class TProd>
class Tienda {

  public:
    // Constructora
    Tienda(); 
    // Pre: true
    // Post: Genera una tienda vacía
    // O(1)

    // Operaciones modificadoras

    void anadir(int cantidad, TProd prod);
    // Pre: cantidad >= 0
    // Post: Añade 'cantidad' unidades al producto. Si ya existía, suma la cantidad.
    //       Si no existía, lo añade al catálogo.
    // O(log n) donde n es el número de productos distintos

    void vender(TProd prod);
    // Pre: El producto debe existir en el catálogo y tener stock > 0
    // Post: Decrementa en 1 la cantidad del producto.
    // Lanza EProductoNoExiste si no está en catálogo.
    // Lanza EStockInsuficiente si el stock es 0.
    // O(log n)

    // Operaciones observadoras

    int consultar(TProd prod);
    // Pre: El producto debe existir en el catálogo
    // Post: Devuelve las existencias disponibles.
    // Lanza EProductoNoExiste si no está en catálogo.
    // O(log n)

    TListaDinamica<ParProductoCantidad<TProd> > inventario();
    // Pre: true
    // Post: Devuelve una lista de pares (producto, cantidad) ordenada por producto.
    // O(n) asumiendo que el recorrido de la tabla es lineal

    TListaDinamica<TProd> reposicion();
    // Pre: true
    // Post: Devuelve una lista de productos cuyas existencias sean < 3, ordenada por producto.
    // O(n)

    // Escritura (para depuración)
    void escribe();

  private:
    // Representación basada en Tabla Ordenada 
    // Clave: Producto, Valor: Cantidad (int)
    TTablaOrdenada<TProd, int> _almacen;

};

//---------------------------------------------------------------------------
// IMPLEMENTACION
//---------------------------------------------------------------------------

template <class TProd>
Tienda<TProd>::Tienda() : _almacen() {
    // La constructora de TTablaOrdenada inicializa _ra a 0
}

template <class TProd>
void Tienda<TProd>::anadir(int cantidad, TProd prod) {
    if (_almacen.esta(prod)) {
        // Si ya está, sumamos a lo existente
        int stockActual = _almacen.consulta(prod);
        _almacen.inserta(prod, stockActual + cantidad);
    } else {
        // Si no está, se crea la entrada nueva
        _almacen.inserta(prod, cantidad);
    }
}

template <class TProd>
void Tienda<TProd>::vender(TProd prod) {
    // Verificamos si está en el catálogo
    if (!_almacen.esta(prod)) {
        throw EProductoNoExiste();
    }

    int stockActual = _almacen.consulta(prod);

    // Verificamos si hay stock físico
    if (stockActual == 0) {
        throw EStockInsuficiente(); 
    }

    // Decrementamos stock
    _almacen.inserta(prod, stockActual - 1);
}

template <class TProd>
int Tienda<TProd>::consultar(TProd prod) {
    if (!_almacen.esta(prod)) {
        throw EProductoNoExiste(); 
    }
    return _almacen.consulta(prod);
}

template <class TProd>
TListaDinamica<ParProductoCantidad<TProd> > Tienda<TProd>::inventario() {
	
    TListaDinamica<ParProductoCantidad<TProd> > listaResultado;
    TSecuenciaDinamica< TPares<TProd, int> > pares = _almacen.recorrePares();
    pares.reinicia();

    while (!pares.esFin()) { 
        
        TPares<TProd, int> parActual = pares.actual(); 
        
        ParProductoCantidad<TProd> elemento;
        elemento.producto = parActual.clave;
        elemento.cantidad = parActual.valor;

        listaResultado.ponDetras(elemento);
        

        pares.avanza(); 
    }
    
    return listaResultado;
}
template <class TProd>
TListaDinamica<TProd> Tienda<TProd>::reposicion() {
	
    TListaDinamica<TProd> listaReposicion;
    TSecuenciaDinamica< TPares<TProd, int> > pares = _almacen.recorrePares();
	pares.reinicia();
	
    while (!pares.esFin()) {
    	
        TPares<TProd, int> parActual = pares.actual();

        if (parActual.valor < 3) {
            listaReposicion.ponDetras(parActual.clave);
        }

        pares.avanza();
    }
    return listaReposicion;
}

template <class TProd>
void Tienda<TProd>::escribe() {
    cout << "--- Estado de la Tienda ---" << endl;
    _almacen.escribe();
    cout << "---------------------------" << endl;
}

#endif