#ifndef _cube_hpp
#define _cube_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <climits>
#include <vector>
#include "random.h"

const unsigned CUBE_SIZE = 2; // Cubo 2x2
const unsigned NUM_FACES = 6; // Seis caras del cubo

/*  Movimientos o rotaciones definidas para el cubo:
	U: Cara superior
	u: Cara superior (sentido antihorario)
	F: Cara frontal
	f: Cara frontal (sentido antihorario)
	R: Cara derecha
	r: Cara derecha (sentido antihorario)
*/
const unsigned NUM_MOVES = 6;
const char MOVES[NUM_MOVES] = {'U', 'u', 'F', 'f', 'R', 'r'};

class Cube{
private:
	char*** sides; // Arreglo con las partes del cubo.
	char letters[NUM_FACES]; // Etiquetas para las piezas de cada una de las seis caras
	std::string ID; // Representacion del estado actual del cubo (cada caracter es una pieza)

	// Crea el ID siguiendo el orden de las etiquetas de letters
	void calcID();

//----------------------Metodos encargados de hacer las rotaciones del cubo---------------------//
	// Los metodos con la letra 'p' son giros en sentido antihorario
	void U();
	void Up();
	void F();
	void Fp();
	void R();
	void Rp();
//----------------------------------------------------------------------------------------------//

public:
//-----------------------------------------Constructores----------------------------------------//
	// Inicializa el cubo armado. letters se crea con la cadena "ULFRBD"
	Cube();
	
	// Inicializa el cubo armado. letters se crea con la cadena faces
	Cube(std::string faces);
//----------------------------------------------------------------------------------------------//
	
	/*  Destructor:
		Libera la memoria asociada al cubo.
	*/
	~Cube();

//-------------------------Verificacion de la posicion correcta de piezas-----------------------//
	// Se verifican todas las piezas para determinar que el cubo esta armado
	bool isSolved();
	
	// Solo se verifica la primera capa
	bool isFaceSolved();
//----------------------------------------------------------------------------------------------//

	// Retorna el ID
	std::string getID();
	
	// Retorna la etiqueta en la posicion index del arreglo letters
	char getLetter(unsigned index);
	
	// Imprime el estado actual del cubo
	void display();
	
	// Recibe un caracter y rota la cara del cubo asociada a ese caracter
	void rotate(char c);
	
	// Recibe una cadena de caracteres, los cuales se pasan a rotate(c)
	void move(std::string s);
	
//-------------------------Generadores de mezclas para desarmar el cubo-------------------------//
	// Genera una mezcla aleatoria
	std::string scramble();
	
	// Lee un archivo de texto con mezclas
	std::string mix();
//----------------------------------------------------------------------------------------------//
};

#endif
