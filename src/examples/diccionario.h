#ifndef DICCIONARIO_H
#define DICCIONARIO_H


#include <string>
#include <sstream>
#include <iostream>


#include "tabla_ordenada.h"
#include "secuencia_dinamica.h"



class TDiccionario
{
	
	
	private :
		
		
	    TTablaOrdenada<string, int> tabla ; //  una tabla hash mas general
	    
	    
	    void imprimeClaves(TSecuenciaDinamica<string> &claves)
	    {
	    	for( claves.reinicia(); !claves.esFin();claves.avanza()){
	    		cout << claves.actual() << " ";
			}
			cout << endl;	        
	    }
	
	
	public :
		
		
	    TDiccionario() { }
	
	    // es una "constructora" que a partir de la linea te crea un diccionario
	    
	    
	    void procesa(const string &linea)
	    {
	    	stringstream ss(linea);
			string clave;
			int valor;
			
			while (ss >> clave >> valor){
				tabla.inserta(clave,valor);
			}	        
	    }
	
	
	    // Compara con el otro diccionario y guarda cambios
	    
	    //O(n1logn2)+O(n2logn1)= O(max(n1logn2,n2logn1))
	    
	    void compararCon(TDiccionario &otro)
	    {
	    	TSecuenciaDinamica<string> clavesActuales = tabla.recorreClave();
	    	bool hayEliminadas  = false;
	    	bool hayNuevas = false;
	    	bool hayModificadas = false;
	    	TSecuenciaDinamica<string> eliminados;
	    	TSecuenciaDinamica<string> nuevos;
	    	TSecuenciaDinamica<string> modificados;
			//O(n1logn2)
	    	for(clavesActuales.reinicia();!clavesActuales.esFin();clavesActuales.avanza()){ //O(n1) n1 numero de claves del dic 1
	    		string clave = clavesActuales.actual();
				if (!otro.tabla.esta(clave)){ //O(logn2) siendo n2 el numero de claves de dic 2
	    			hayEliminadas = true;
	    			eliminados.inserta(clave);//O(1) 
				}		
				else if (tabla.consulta(clave) != otro.tabla.consulta(clave)){ //O(logn2)
					hayModificadas = true;
					modificados.inserta(clave);//O(!)
				}
			}
			//O(n2logn1)
			TSecuenciaDinamica<string> clavesOtras = otro.tabla.recorreClave(); // O(n2)
			for(clavesOtras.reinicia();!clavesOtras.esFin();clavesOtras.avanza()){ 
				string clave = clavesOtras.actual();
				if (!tabla.esta(clave)){ //O(logn1)
					hayNuevas = true;
					nuevos.inserta(clave);//O(1)
				}
			}
			if (!hayEliminadas && !hayNuevas && !hayModificadas){
				cout << "Sin cambios" << endl;
			}
			else{
				if (hayNuevas){
					cout << "+ ";
					imprimeClaves(nuevos);
				}
				if (hayEliminadas){
					cout << "- ";
					imprimeClaves(eliminados);
				}
				if (hayModificadas){
					cout <<"* ";
					imprimeClaves(modificados);
				}
			}
			cout << "----" << endl;       
	    }
	    
} ;


#endif