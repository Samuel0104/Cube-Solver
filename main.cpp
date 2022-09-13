#include "cube.hpp"
#include "solver.hpp"

int main(){
	Cube c; // The cube is created
	std::cout << "Rubik++" << std::endl;
	while (true){
		// Program's main menu
		char command = ' ';
		while (toupper(command) != 'E' && toupper(command) != 'Q'){
			std::cout << "\nEnter a command:\n"
			<< "E -- Execute program\n"
			<< "Q -- Exit\n";
			std::cin >> command;
		}
		if (toupper(command) == 'Q')
			break;
		
		// Selection of the mixing method to scramble the cube
		std::string choice = "";
		while (choice != "1" && choice != "2"){
			std::cout << "\nChoose a mixing method:\n"
			<< "  1. Text file\n"
			<< "  2. Random scramble\n";
			std::cin >> choice;
		}
		
		std::string scramble = "";
		if (choice == "1")
			scramble = c.mix();
		else
			scramble = c.scramble();
			
		std::cout << "\nScramble: " << scramble << std::endl; // The used scramble is printed
		
		// Selection of the method to solve the cube
		std::string method = "";
		while (method != "1" && method != "2"){
			std::cout << "\nChoose a solving method:\n"
			<< "  1. Layer by layer\n"
			<< "  2. Whole cube\n";
			std::cin >> method;
		}
		
//------------------------------------------Cube Solver-----------------------------------------//
		Solver s(c); // The solver is initialized
		std::cout << "\nCubo desarmado:\n" << std::endl;
		c.display(); // The scrambled cube is printed
	
		if (method == "1"){
			s.firstLayer(); // The first layer is solved
			std::cout << "\nPrimera capa:\n" << std::endl;
			c.display(); // The cube is printed with the first layer solved
		
			s.lastLayer(); // The second layer is solved
			std::cout << "\nSegunda capa (cubo armado):\n" << std::endl;
			c.display(); // The solved cube is printed
			s.printSolution(); // The list and number of moves are displayed
		}
		else {
			s.wholeCube(); // The whole cube is solved
			std::cout << "\nCubo armado:\n" << std::endl;
			c.display(); // The solved cube is printed
			s.printSolution(); // The list and number of moves are displayed
		}
//----------------------------------------------------------------------------------------------//
	}
	return 0;
}
