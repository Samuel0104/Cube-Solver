#include "solver.h"

// Constructor
Solver::Solver(Cube& c){
	rubik = &c;
	faceRestrict = '-';
}


void Solver::makeMove(char m){
	rubik->rotate(m);
	solution.push_back(m); // Se agrega el ultimo movimiento a la solucion
}


void Solver::retractMove(){
	char m = solution.back();
	rubik->rotate(isupper(m) ? tolower(m):toupper(m));
	solution.pop_back(); // Se elimina el ultimo movimiento de la solucion
}


/*  Se juntan dos piezas de la parte inferior del cubo
	haciendo una busqueda recursiva de los movimientos.
*/
bool Solver::pair(unsigned depth = 4){
//--------------------------------Casos base para el backtracking-------------------------------//
	if (rubik->getID()[20] == rubik->getLetter(5) && rubik->getID()[7] == rubik->getLetter(1)){
		faceRestrict = 'F';
		return true;	
	}
	if (rubik->getID()[23] == rubik->getLetter(5) && rubik->getID()[15] == rubik->getLetter(3)){
		faceRestrict = 'R';
		return true;	
	}
	if (depth == 0)
		return false;
//----------------------------------------------------------------------------------------------//

	for (unsigned i = 0; i < NUM_MOVES; ++i){
//-----Condiciones usadas para simplificar la cantidad de casos revisados en el backtracking----//
		bool cond1 = solution.empty();
		bool cond2 = !cond1 && toupper(MOVES[i]) != toupper(solution.back());
		bool cond3 = !cond1 && isupper(MOVES[i]) && MOVES[i] == solution.back();
		bool cond4 = solution.size() == 1 || (solution.size() == 1 && MOVES[i] != solution[solution.size()-2]);
//----------------------------------------------------------------------------------------------//

		if (cond1 || cond2 || (cond3 && cond4)){
			makeMove(MOVES[i]);
			if (pair(depth - 1)) // Se busca una solucion desde el estado actual
				return true;
			retractMove();
		}
	}
	return false;
}


/*  Se termina de armar la parte inferior del cubo
	haciendo una busqueda recursiva. El metodo pair(depth)
	permite restringir los movimientos necesarios para
	este metodo, acortando la busqueda.
*/
bool Solver::face(unsigned depth = 11){
//--------------------------------Casos base para el backtracking-------------------------------//
	if (rubik->isFaceSolved())
		return true;
	if (depth == 0)
		return false;
//----------------------------------------------------------------------------------------------//
		
	for (unsigned i = 0; i < NUM_MOVES; ++i){
		if (toupper(MOVES[i]) != faceRestrict){
//-----Condiciones usadas para simplificar la cantidad de casos revisados en el backtracking----//
			bool cond1 = solution.empty();
			bool cond2 = !cond1 && toupper(MOVES[i]) != toupper(solution.back());
			bool cond3 = !cond1 && isupper(MOVES[i]) && MOVES[i] == solution.back();
			bool cond4 = solution.size() == 1 || (solution.size() == 1 && MOVES[i] != solution[solution.size()-2]);
//----------------------------------------------------------------------------------------------//
			
			if (cond1 || cond2 || (cond3 && cond4)){
				makeMove(MOVES[i]);
				if (face(depth - 1)) // Se busca una solucion desde el estado actual
					return true;
				retractMove();
			}
		}
	}
	return false;
}


/*  Encapsula las funciones encargadas de
	la solucion de la capa inferior.
*/
void Solver::firstLayer(){
	pair();
	face();
}


/*  Se revisan cuatro piezas en el cubo. Retorna false
	si alguna pieza de las posiciones elegidas no
	coincide con el caracter de la cara superior.
*/
bool Solver::ollHelper(int a, int b, int c, int d){
	int arr[] = {a, b, c, d};
	for (int i = 0; i < 4; ++i)
		if (rubik->getID()[arr[i]] != rubik->getLetter(0))
			return false;
	return true;
}


/* 	Se identifica cual de los ocho casos de
	oll se obtuvo en la resolucion actual.
*/
std::string Solver::getOll(){ // oll: Orientation of Last Layer
    while (true){
    	if (ollHelper(0, 1, 2, 3))
    		return "";
        if (ollHelper(2, 9, 13, 17))
            return "R U r U R U U r";
        if (ollHelper(1, 4, 8, 12))
            return "R U U r u R u r";
        if (ollHelper(1, 3, 4, 5))
            return "F R U r u f";
        if (ollHelper(8, 9, 16, 17))
            return "R R U U R U U R R";
        if (ollHelper(4, 5, 9, 16))
            return "F R U r u R U r u f";
        if (ollHelper(0, 3, 8, 13))
            return "F R u r u R U r f";
        if (ollHelper(1, 3, 8, 17))
            return "R U r u r F R f";
        makeMove('U');
    }
}


/* 	Se identifica cual de los tres casos de
	pll se obtuvo en la resolucion actual.
*/
std::string Solver::getPll(){ // pll: Permutation of Last Layer
    for (unsigned i = 0; i < 4; ++i){
        if (rubik->getID()[4] == rubik->getID()[5]){
            if (rubik->getID()[12] == rubik->getID()[13])
                return "";
            return "R U U r u R U U r F r f R";
        }
        makeMove('U');
    }
    return "R u r u F F u R U r U F F";
}


/*  Realiza los movimientos de los casos
	retornados por getOll() o getPll() y
	se agregan al vector con la solucion.
*/
void Solver::translate(std::string s){
	for (unsigned i = 0; i < s.length(); i += 2)
		makeMove(s[i]);
}


/*  Encapsula las funciones encargadas de
	la solucion de la capa superior.
*/
void Solver::lastLayer(){
	translate(getOll());
	translate(getPll());
	while (!rubik->isSolved())
		makeMove('U'); // Rotaciones adicionales
}


/*  Se imprimen en orden los pasos realizados
	para armar el cubo y la cantidad de
	movimientos utilizados.
*/
void Solver::printSolution(){
	std::cout << "\nSolucion: ";
	unsigned num = solution.size();
	for (unsigned i = 0; i < num; ++i)
		std::cout << solution[i] << " ";
	std::cout << "\nCantidad de movimientos realizados: " << num
	<< "\n\n************************\n";
}
