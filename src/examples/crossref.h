#ifndef CROSSREF_H
#define CROSSREF_H


#include <string>
#include <iostream>


#include "tabla_ordenada.h"

// siendo el tamano de datos n = numero de palabras
// O(nlogn + n)= O(nlogn) respecto al tiempo
// O(n) + O(n) + O(n) = O(n) memoria/ espacio auxiliar


class TCrossRef
{


	private :
		
		
	    TTablaOrdenada<string, TSecuenciaDinamica<int>> _tabla ; // la memoria auxiliar se pone aqui
	
	
	public :
		
		
	    void procesa(const string &linea, int numLinea)
	    {
	    	string palabra;
	    	for (int i = 0 ; i< linea.length() ; i++){
	    		char c = linea[i];
	    		if (isalpha(c) ){
	    			palabra += tolower(c);
				}
				else if ( !palabra.empty()){
					if (palabra.length() > 2){
						TSecuenciaDinamica<int> lineas; // memoria aux
						if (_tabla.esta(palabra)){
							lineas = _tabla.consulta(palabra);
							bool encontrado  = false;
							lineas.reinicia();
							while( !lineas.esFin() && !encontrado){
								if (lineas.actual() == numLinea){
									encontrado = true;
								}
								lineas.avanza();
							}
							if (!encontrado){
								lineas.inserta(numLinea);
								_tabla.inserta(palabra,lineas);
							}
						}
						else{
							lineas.inserta(numLinea);
							_tabla.inserta(palabra,lineas);
						}
					}
					palabra.clear();
				}
			}
			// caso particular para la ultima palabra
	    	if (!palabra.empty() && palabra.length()>2){
	    		TSecuenciaDinamica<int> lineas;
	    		if (_tabla.esta(palabra)){
	    			lineas = _tabla.consulta(palabra);
	    			bool encontrado = false;
	    			lineas.reinicia();
	    			while (!lineas.esFin() && !encontrado){
	    				if (lineas.actual() == numLinea){
	    					encontrado = true;
						}
						lineas.avanza();	
					}
					if (!encontrado){
						lineas.inserta(numLinea);
						_tabla.inserta(palabra,lineas);
					}
				}
				else
				lineas.inserta(numLinea);
				_tabla.inserta(palabra,lineas);
			}
	        
	    };
	
	
	    void imprimir(){
	    	TSecuenciaDinamica<string> palabras = _tabla.recorreClave();
	    	palabras.reinicia();
	    	while (!palabras.esFin()){
	    		string palabra = palabras.actual();
	    		TSecuenciaDinamica<int> lineas = _tabla.consulta(palabra);
	    		cout << palabra << " ";
	    		lineas.reinicia();
	    		while (!lineas.esFin()){
	    			cout<< lineas.actual();
	    			lineas.avanza();
	    			if (!lineas.esFin()) 
	    				cout << " ";
				}
				cout << endl;
				palabras.avanza();
			}
			cout << "----"<< endl;
		}

    
} ;


#endif