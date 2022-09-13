#ifndef _cube_hpp
#define _cube_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <climits>
#include <vector>
#include "random.hpp"

const unsigned CUBE_SIZE = 2; // 2x2 cube
const unsigned NUM_FACES = 6; // Cube's six faces

/*  Moves or rotations defined for the cube:
	U: Upper face
	u: Upper face (counter-clock wise)
	F: Front face
	f: Front face (counter-clock wise)
	R: Right face
	r: Right face (counter-clock wise)
*/
const unsigned NUM_MOVES = 6;
const char MOVES[NUM_MOVES] = {'U', 'u', 'F', 'f', 'R', 'r'};

class Cube{
private:
	char*** sides; // Array with the parts of the cube
	char letters[NUM_FACES]; // Labels for the pieces of each of the six faces
	std::string ID; // Representation of the cube's current state (each character is a piece)

	// Creates the ID following the order of the labels in 'letters'
	void calcID();

//-----------------------------Methods for making the cube rotations----------------------------//
	// Methods with the letter 'p' are counter-clock wise turns
	void U();
	void Up();
	void F();
	void Fp();
	void R();
	void Rp();
//----------------------------------------------------------------------------------------------//

public:
//-----------------------------------------Constructors-----------------------------------------//
	// Initializes the solved cube. 'letters' is created with the string "ULFRBD"
	Cube();
	
	// Initializes the solved cube. 'letters' is created with the string 'faces'
	Cube(std::string faces);
//----------------------------------------------------------------------------------------------//
	
	/*  Destructor:
		Frees memory associated with the cube
	*/
	~Cube();

//-------------------------Verification of the correct position of pieces-----------------------//
	// All pieces are checked to determine if the cube is solved
	bool isSolved();
	
	// Only the first layer is checked
	bool isFaceSolved();
//----------------------------------------------------------------------------------------------//

	// Returns the ID
	std::string getID();
	
	// Returns label in position 'index' of the array 'letters'
	char getLetter(unsigned index);
	
	// Prints the cube's current state
	void display();
	
	// Takes a character and rotates the cube's face associated with that character
	void rotate(char c);
	
	// Takes a string. rotate(c) takes each character in the string
	void move(std::string s);
	
//------------------------------Mix generators to scramble the cube-----------------------------//
	// Generates a random scramble
	std::string scramble();
	
	// Reads a text file with scrambles
	std::string mix();
//----------------------------------------------------------------------------------------------//
};

#endif
