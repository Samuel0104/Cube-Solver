#ifndef _solver_hpp
#define _solver_hpp

#include <cctype>
#include "cube.hpp"

class Solver{
private:
	Cube* rubik; // Apuntador a un objeto Cube
	std::vector<char> solution;
	char faceRestrict; // Se restringen las posibles ramas del backtracking despues de armar una pareja

//---------------------Metodos encargados de hacer los movimientos del cubo---------------------//
	// Recibe un caracter y rota la cara del cubo asociada a ese caracter
	void makeMove(char m);
	
	// Deshace la ultima rotacion hecha en el cubo
	void retractMove();
//----------------------------------------------------------------------------------------------//

	// Simplifica la implementacion de la funcion getOll()
	bool ollHelper(int a, int b, int c, int d);
	
	
	void translate(std::string s);

public:
	/* Constructor:
		Recibe un objeto de clase Cube para
		apuntar a su direccion en memoria.
	*/
	Solver(Cube& c);
	
//-----------------Metodos encargados de la solucion de la totalidad del cubo-------------------//
	// Se arma todo el cubo con backtracking
	bool solve(unsigned depth);
	
	// Encapsula la anterior
	void wholeCube();
//----------------------------------------------------------------------------------------------//
	
//---------------Metodos encargados de la solucion de la capa inferior del cubo-----------------//
	// Se juntan dos piezas en su posicion correcta en la parte inferior del cubo
	bool pair(unsigned depth);
	
	// Se termina de armar la capa inferior del cubo
	bool face(unsigned depth);
	
	// Encapsula las anteriores
	void firstLayer();
//----------------------------------------------------------------------------------------------//

//---------------Metodos encargados de la solucion de la capa superior del cubo-----------------//
	// Identifica el caso de oll necesitado en la actual resolucion del cubo
	std::string getOll();
	
	// Identifica el caso de pll necesitado en la actual resolucion del cubo
    std::string getPll();
	
	// Encapsula las anterioes
	void lastLayer();
//----------------------------------------------------------------------------------------------//
	
	// Se imprimen la lista y el numero de rotaciones realizadas en el cubo
	void printSolution();
};


#endif
