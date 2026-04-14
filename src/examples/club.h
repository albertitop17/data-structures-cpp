#ifndef CLUB_H
#define CLUB_H

#include "tabla_abierta.h"
#include "cprio.h"


// Practica 4
// Realizada por Fabio Torres y Alberto Peña

using namespace std;

/*
LA ESPECIFICACION ALGEBRAICA ESTA REALIZADA EN EL ARCHIVO PDF QUE SE ADJUNTA EN LA ENTREGA

     tipos
        club = reg
	            registro: tabla-hash[fan,nat]
	            fanatismo: cprioridad[pares]
               freg
        pares = reg
                    fan : string
                    nivel: nat     // definida una operacion de orden
                freg

     ftipos
*/

// Al tratarse de un monticulo de maximos me defino esta estructura 
// con la siguiente relacion de orden para poder aprovechar las funciones creadas para monticulos de minimos (cprio.h)
struct Pares { 
	string fan;
	int nivel;
	
	bool operator>(Pares &otro){
		return nivel<otro.nivel;
	}
	
	bool operator<(Pares &otro){
		return nivel > otro.nivel;
	}
};

//Voy a suponer que los fans se identifican con su nombre (string)
class Club
{
	public:
		//Constructora
		Club();	//O(F),siendo F el numero de fans
		
		void insertar(string fan, int nivel);
		//Pre: true
		//Post: inserta un fan con su nivel de fanatismo en la tabla y en el monticulo
		//O(log F), siendo F el numero de fans.
		
		int nivel(string fan);
		//Pre: esta?(fan)
		//Post: devuelve el nivel de fanatismo de un fan
		//O(1)
		
		void borraRad(int max);
		//Pre: true
		//Post: borra del club a los fans radicales con un nivel de fanatismo mayor o igual al dado (en la tabla y en el monticulo)
		//O(F*log(F)), siendo F el numero de fans del club
		
		void mostrar();
		//Pre: true
		//Post: Muestra por pantalla el club de fans
		

		
	
	private:
		TTablaAbierta<string,int> _registro;
		TCPrio<Pares> _fanatismo;

};
	
	Club::Club() :
	 _registro() ,_fanatismo(63){
	};
		
	void Club::insertar(string fan, int nivel){
		Pares pareja;
		pareja.fan = fan;
		pareja.nivel = nivel;
		_registro.inserta(fan,nivel); //O(1)
		_fanatismo.anyade(pareja);  //O(log F)
	}
	
	int Club::nivel(string fan){
		return _registro.consulta(fan);
	}
	
	void Club::borraRad(int max){
		while( !_fanatismo.esVacio() && _fanatismo.min().nivel >= max){
			Pares radical = _fanatismo.min();
			_registro.borra(radical.fan);
			_fanatismo.quitaMin();
		}
	} 
	
	void Club::mostrar(){
		_registro.escribe();
	}
	

#endif