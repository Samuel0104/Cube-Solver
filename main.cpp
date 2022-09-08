#include "cube.h"
#include "solver.h"

int main(){
	Cube c; // Se crea el cubo
	std::cout << "Rubik++" << std::endl;
	while (true){
		// Menu principal del programa
		char command = ' ';
		while (toupper(command) != 'E' && toupper(command) != 'Q'){
			std::cout << "\nIngrese un comando:\n"
			<< "E -- Ejecutar programa\n"
			<< "Q -- Salir\n";
			std::cin >> command;
		}
		if (toupper(command) == 'Q')
			break;
		
		// Seleccion del metodo de mezcla para desarmar el cubo
		std::string choice = "";
		while (choice != "1" && choice != "2"){
			std::cout << "\nEscoja un metodo de mezcla:\n"
			<< "  1. Archivo de texto\n"
			<< "  2. Mezcla aleatoria\n";
			std::cin >> choice;
		}
		
		std::string scramble = "";
		if (choice == "1")
			scramble = c.mix();
		else
			scramble = c.scramble();
			
		std::cout << "\nMezcla: " << scramble << std::endl; // Se imprime la mezcla utilizada
		
//-------------------------------------Solucionador del cubo------------------------------------//
		Solver s(c); // Se construye el solucionador
		std::cout << "\nCubo desarmado:\n" << std::endl;
		c.display(); // Se imprime el cubo desarmado
	
		s.firstLayer(); // Se arma la primera capa
		std::cout << "\nPrimera capa:\n" << std::endl;
		c.display(); // Se imprime el cubo con la capa inferior armada
	
		s.lastLayer(); // Se arma la segunda capa
		std::cout << "\nSegunda capa (cubo armado):\n" << std::endl;
		c.display(); // Se imprime el cubo armado
		s.printSolution(); // Se muestran la lista y el numero de movimientos usados
//----------------------------------------------------------------------------------------------//
	}
	return 0;
}