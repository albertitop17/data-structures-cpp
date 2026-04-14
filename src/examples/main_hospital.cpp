#include <iostream>
#include "cprio.h"
#include <list> // PODRIAMOS USAR NUESTRA IMPLEMENTACION DE LISTAS (USO ESTA PARA EVITAR TENER QUE MANDAR MAS ARCHIVOS DISTINTOS)

struct Paciente {
	
	string nombre;
	int gravedad;
	
	bool operator > (Paciente &otro){
		return gravedad < otro.gravedad;
	}
	
	bool operator < (Paciente &otro){
		return gravedad > otro.gravedad;
	}
};


int main (int argc, char * const argv[]){
	
	TCPrio<Paciente> consultas(63);
	list<string> atendidos;
	
	cout << "Introduce el numero de eventos y que eventos son: " << endl;
	
	int numevent;
	cin >> numevent;
	
	while (numevent > 0){
		char evento;
		cin >> evento;
		if (evento == 'I'){
			string nombrePaciente;
			int gravedadPaciente;
			cin >> nombrePaciente >> gravedadPaciente;
			Paciente p;
			p.nombre = nombrePaciente;
			p.gravedad = gravedadPaciente; //lo pongo en negativo para no tener que hacer el cambio a maximo y poder usar minimo
			consultas.anyade(p); 
		}
		if (evento == 'A'){
			atendidos.push_back(consultas.min().nombre);
			consultas.quitaMin();
		}
		numevent --;
	}
	
	int cero;
	cin >> cero;
	
	cout << endl;
	for (string nombre: atendidos){
		cout << nombre << endl;
	}
	
	cout << "---" << endl;
	
	return 0;
	
}




/* 

Puesto que tenemos que es un bucle respecto el numero de eventos y que todas las operaciones interiores son de coste constante menos quitarMIn() que es logaritmico respecto al numero de eventos (pues es AVL)  

Así el coste del programa sera O(nlogn) siendo n = nº de eventos  

*/




