#include <iostream>
#include "club.h"

using namespace std;

int main(int argc, char * const argv[]) {
    Club miClub;

    cout << "--- Insertamos Fans ---" << endl;
    miClub.insertar("Rafa", 1000);   
    miClub.insertar("Lechuga", 20);  
    miClub.insertar("Jorge", 80);  
    miClub.insertar("Princesa", 50); 
    miClub.insertar("Anton", 5);  
    
    cout << endl << endl<< "EL CLUB DE FANS DE ALBERTO ES:"<< endl;
    miClub.mostrar();
    cout << endl;

    cout << "Nivel de Rafa : " << miClub.nivel("Rafa") << endl;
    cout << "Nivel de Princesa: " << miClub.nivel("Princesa") << endl;

    cout << "Se eliminaran fans con nivel >= 60." << endl;
    
    miClub.borraRad(60);
    
    cout << endl << "Despues de fumigar a los ultras del frente Atleti el club queda:"<< endl;

	miClub.mostrar();

    return 0;
}