#include <iostream>
#include <string>
#include "tienda.h" 
// Asegúrate de que tienda.h incluye a su vez a lista_dinamica.h y tabla_ordenada.h

using namespace std;

int main() {
    // Instanciamos una tienda de strings (nombre del producto)
    Tienda<string> miTienda;

    cout << "=== APERTURA DE LA TIENDA ===" << endl;

    // ---------------------------------------------------------
    // 1. AÑADIR PRODUCTOS
    // ---------------------------------------------------------
    cout << "\n[1] Llenando el almacen..." << endl;
    
    miTienda.anadir(10, "Manzanas"); // Stock de sobra
    miTienda.anadir(5,  "Peras");    // Stock medio
    miTienda.anadir(2,  "Leche");    // Stock bajo (debería salir en reposición)
    miTienda.anadir(0,  "Pan");      // Sin stock (solo catálogo)
    
    // Añadimos más stock a un producto existente
    miTienda.anadir(5, "Manzanas"); 
    
    try {
        cout << "Stock actual de Manzanas (deberia ser 15): " << miTienda.consultar("Manzanas") << endl;
        cout << "Stock actual de Peras (deberia ser 5): " << miTienda.consultar("Peras") << endl;
        cout << "Stock actual de Leche (deberia ser 2): " << miTienda.consultar("Leche") << endl;
        cout << "Stock actual de Pan (deberia ser 0): " << miTienda.consultar("Pan") << endl;
    } catch (EProductoNoExiste &e) {
        cout << "Error: " << e.mensaje() << endl;
    }

    // ---------------------------------------------------------
    // 2. VENDER PRODUCTOS
    // ---------------------------------------------------------
    cout << "\n[2] Realizando ventas..." << endl;

    try {
        cout << "Vendiendo 1 Peras..." << endl;
        miTienda.vender("Peras");
        cout << "Quedan " << miTienda.consultar("Peras") << " Peras." << endl;

        cout << "Vendiendo 1 Leche..." << endl;
        miTienda.vender("Leche");
        cout << "Quedan " << miTienda.consultar("Leche") << " de Leche." << endl;
        
    } catch (EStockInsuficiente &e) {
        cout << "Error de stock: " << e.mensaje() << endl;
    } catch (EProductoNoExiste &e) {
        cout << "Error de producto: " << e.mensaje() << endl;
    }

    // ---------------------------------------------------------
    // 3. PROBAR ERRORES (EXCEPCIONES)
    // ---------------------------------------------------------
    cout << "\n[3] Probando errores y excepciones..." << endl;

    // Caso A: Vender producto que no existe
    try {
        cout << "Intentando vender 'Coches'..." << endl;
        miTienda.vender("Coches");
    } catch (EProductoNoExiste &e) {
        cout << "-> Excepcion atrapada correctamente: " << e.mensaje() << endl;
    }

    // Caso B: Vender producto sin stock (Pan tiene 0)
    try {
        cout << "Intentando vender 'Pan'..." << endl;
        miTienda.vender("Pan");
    } catch (EStockInsuficiente &e) {
        cout << "-> Excepcion atrapada correctamente: " << e.mensaje() << endl;
    }


    // ---------------------------------------------------------
    // 4. LISTAR INVENTARIO (Recorrer lista devuelta)
    // ---------------------------------------------------------
    cout << "\n[4] Generando Inventario Completo..." << endl;
    
    // Obtenemos la lista
    TListaDinamica<ParProductoCantidad<string> > listaInv = miTienda.inventario();

    if (listaInv.esVacio()) {
        cout << "El inventario esta vacio." << endl;
    } else {
        // Recorremos la lista destruyéndola (o copiándola si prefieres) para mostrar
        // Como 'ParProductoCantidad' es un struct simple, imprimimos sus campos manualmente
        while (!listaInv.esVacio()) {
            ParProductoCantidad<string> item = listaInv.primero();
            
            cout << " - Producto: " << item.producto 
                 << " \t| Stock: " << item.cantidad << endl;
            
            listaInv.quitaPrim();
        }
    }

    // ---------------------------------------------------------
    // 5. LISTAR REPOSICION (Stock < 3)
    // ---------------------------------------------------------
    cout << "\n[5] Generando Lista de Reposicion (Stock < 3)..." << endl;

    TListaDinamica<string> listaRep = miTienda.reposicion();

    if (listaRep.esVacio()) {
        cout << "No hay nada que reponer." << endl;
    } else {
        while (!listaRep.esVacio()) {
            string prod = listaRep.primero();
            cout << " (!) ALERTA: Reponer " << prod << endl;
            listaRep.quitaPrim();
        }
    }
    
    // Nota: Deberían salir "Leche" (quedaba 1) y "Pan" (quedaban 0).
    
    cout << "\n=== CIERRE DE LA TIENDA ===" << endl;

    return 0;
}