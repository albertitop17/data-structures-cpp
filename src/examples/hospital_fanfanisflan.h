#ifndef CONSULTORIO_H
#define CONSULTORIO_H

#include <iostream>
#include <string>
#include "cola_dinamica.h"   // Asumimos que existe para gestionar la cola de pacientes
#include "tabla_ordenada.h"  // Usada para mapear Médicos -> Cola de Pacientes
#include "lista_dinamica.h"  // Usada para devolver listados si fuera necesario

using namespace std;

// --------------------------------------------------------------------------
// EXCEPCIONES ESPECÍFICAS
// --------------------------------------------------------------------------

class EMedicoNoExiste {
  public:
    EMedicoNoExiste(string mensaje = "El medico no esta dado de alta") : _mensaje(mensaje) {};
    string mensaje() { return _mensaje; };
  private:
    string _mensaje;
};

class EMedicoYaExiste {
  public:
    EMedicoYaExiste(string mensaje = "El medico ya figura en el consultorio") : _mensaje(mensaje) {};
    string mensaje() { return _mensaje; };
  private:
    string _mensaje;
};

class ENoHayPacientes {
  public:
    ENoHayPacientes(string mensaje = "No hay pacientes en espera para este medico") : _mensaje(mensaje) {};
    string mensaje() { return _mensaje; };
  private:
    string _mensaje;
};

// --------------------------------------------------------------------------
// CLASE CONSULTORIO
// --------------------------------------------------------------------------
// TMed: Tipo de dato para el Médico (ej: string nombre, o int ID)
// TPac: Tipo de dato para el Paciente (ej: string nombre)

template <class TMed, class TPac>
class Consultorio {

  public:
    // Constructora
    Consultorio();
    // Post: Genera un consultorio vacío.

    // Operaciones Modificadoras

    void alta_medico(TMed medico);
    // Post: Da de alta un nuevo médico con una cola de pacientes vacía.
    // Lanza EMedicoYaExiste si el médico ya está en la tabla.

    void pedir_consulta(TMed medico, TPac paciente);
    // Post: Añade al paciente a la cola de espera del médico indicado.
    // Lanza EMedicoNoExiste si el médico no está.

    void atender_consulta(TMed medico);
    // Post: Elimina al primer paciente de la cola del médico (lo atiende).
    // Lanza EMedicoNoExiste si el médico no está.
    // Lanza ENoHayPacientes si la cola está vacía.

    // Operaciones Observadoras

    bool tiene_pacientes(TMed medico);
    // Post: Devuelve true si el médico tiene alguien esperando.
    // Lanza EMedicoNoExiste.

    TPac siguiente_paciente(TMed medico);
    // Post: Devuelve el paciente que le toca el turno (sin quitarlo).
    // Lanza EMedicoNoExiste o ENoHayPacientes.

    // Escritura (para depuración)
    void escribe();

  private:
    // Representación:
    // Clave: Médico (TMed)
    // Valor: Cola de Pacientes (TCola<TPac>)
    TTablaOrdenada<TMed, TCola<TPac> > _datos;
};

// --------------------------------------------------------------------------
// IMPLEMENTACIÓN
// --------------------------------------------------------------------------

template <class TMed, class TPac>
Consultorio<TMed, TPac>::Consultorio() : _datos() {
    // La tabla se inicializa vacía
}

template <class TMed, class TPac>
void Consultorio<TMed, TPac>::alta_medico(TMed medico) {
    if (_datos.esta(medico)) {
        throw EMedicoYaExiste();
    }
    // Creamos una cola vacía para el nuevo médico
    TCola<TPac> colaVacia;
    _datos.inserta(medico, colaVacia);
}

template <class TMed, class TPac>
void Consultorio<TMed, TPac>::pedir_consulta(TMed medico, TPac paciente) {
    if (!_datos.esta(medico)) {
        throw EMedicoNoExiste();
    }

    // 1. Obtenemos la cola actual del médico
    TCola<TPac> colaActual = _datos.consulta(medico);
    
    // 2. Añadimos el paciente
    colaActual.ponDetras(paciente); // O 'encolar(paciente)' según tu ADT
    
    // 3. Actualizamos la tabla con la cola modificada
    _datos.inserta(medico, colaActual);
}

template <class TMed, class TPac>
void Consultorio<TMed, TPac>::atender_consulta(TMed medico) {
    if (!_datos.esta(medico)) {
        throw EMedicoNoExiste();
    }

    TCola<TPac> colaActual = _datos.consulta(medico);

    if (colaActual.esVacia()) {
        throw ENoHayPacientes();
    }

    // Quitamos al paciente atendido
    colaActual.quitaPrim(); // O 'desencolar()' según tu ADT

    // Guardamos los cambios
    _datos.inserta(medico, colaActual);
}

template <class TMed, class TPac>
bool Consultorio<TMed, TPac>::tiene_pacientes(TMed medico) {
    if (!_datos.esta(medico)) {
        throw EMedicoNoExiste();
    }
    TCola<TPac> c = _datos.consulta(medico);
    return !c.esVacia();
}

template <class TMed, class TPac>
TPac Consultorio<TMed, TPac>::siguiente_paciente(TMed medico) {
    if (!_datos.esta(medico)) {
        throw EMedicoNoExiste();
    }
    
    // Nota: Como consulta devuelve por valor (copia), no necesitamos const &
    TCola<TPac> c = _datos.consulta(medico);

    if (c.esVacia()) {
        throw ENoHayPacientes();
    }
    
    return c.primero();
}

template <class TMed, class TPac>
void Consultorio<TMed, TPac>::escribe() {
    cout << "--- Estado del Consultorio ---" << endl;
    // Como TTablaOrdenada.escribe() es genérico, imprimirá Médico -> [Estructura Cola]
    // Depende de si TCola tiene implementado el operador << o un método escribe.
    _datos.escribe(); 
    cout << "------------------------------" << endl;
}

#endif